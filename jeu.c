#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "jeu.h"
#include "paquet.h"
#include "joueur.h"
#include "entree.h"
#include "utils.h"
#include "carte.h"
#include "effets.h"

void initialiser_partie(Partie* p, int nb_joueurs)
{
    if (nb_joueurs < 2) nb_joueurs = 2;
    if (nb_joueurs > 4) nb_joueurs = 4;

    init_aleatoire();

    initialiser_paquet(&p->pioche);
    melanger_paquet(&p->pioche);

    p->defausse.nb_cartes = 0;

    p->nb_joueurs = nb_joueurs;
    p->joueur_actuel = 0;
    p->sens = 1;

    for (int i = 0; i < p->nb_joueurs; i++) {
        p->joueurs[i].nb_cartes = 0;
        p->joueurs[i].estHumain = 0;
        p->joueurs[i].nom[0] = '\0';
    }

    // Première carte sur la table
    p->carte_dessus = tirer_carte(&p->pioche);
    p->defausse.cartes[p->defausse.nb_cartes++] = p->carte_dessus;
}

void distribuer_cartes(Partie* p, int cartes_par_joueur)
{
    for (int r = 0; r < cartes_par_joueur; r++) {
        for (int i = 0; i < p->nb_joueurs; i++) {
            Carte c = tirer_carte(&p->pioche);
            ajouter_carte_main(&p->joueurs[i], c);
        }
    }
}

int partie_terminee(Partie* p)
{
    for (int i = 0; i < p->nb_joueurs; i++) {
        if (main_vide(&p->joueurs[i])) return 1;
    }
    return 0;
}

int joueur_suivant(Partie* p)
{
    int next = p->joueur_actuel + p->sens;
    if (next < 0) next += p->nb_joueurs;
    if (next >= p->nb_joueurs) next -= p->nb_joueurs;
    return next;
}

void passer_au_suivant(Partie* p)
{
    p->joueur_actuel = joueur_suivant(p);
}

void afficher_plateau(const Partie* p)
{
    printf("\n=== Plateau ===\n");
    printf("Carte dessus : ");
    afficher_carte(p->carte_dessus);
    printf("Pioche: %d cartes | Défausse: %d cartes\n", p->pioche.nb_cartes, p->defausse.nb_cartes);
    for (int i = 0; i < p->nb_joueurs; i++) {
        printf("%s - %d cartes%s\n", p->joueurs[i].nom[0] ? p->joueurs[i].nom : "Joueur", p->joueurs[i].nb_cartes,
            p->joueurs[i].estHumain ? " (humain)" : "");
        if (p->joueurs[i].estHumain) {
            afficher_main(&p->joueurs[i]);
        }
    }
    printf("Joueur actuel : %s\n", p->joueurs[p->joueur_actuel].nom);
    printf("===============\n");
}

void boucle_jeu(Partie* p)
{
    while (!partie_terminee(p)) {
        afficher_plateau(p);

        Joueur* j = &p->joueurs[p->joueur_actuel];

        int choix = choisir_carte(j, p->carte_dessus);

        if (choix == -1) {
            Carte c = tirer_carte(&p->pioche);
            ajouter_carte_main(j, c);
            printf("%s a pioché une carte.\n", j->nom);
            passer_au_suivant(p);
        } else {
            if (choix < 0 || choix >= j->nb_cartes || !carte_peut_etre_jouee(j->main[choix], p->carte_dessus)) {
                printf("Carte non jouable ou index invalide — vous piochez.\n");
                Carte c = tirer_carte(&p->pioche);
                ajouter_carte_main(j, c);
                passer_au_suivant(p);
            } else {
                p->carte_dessus = j->main[choix];
                retirer_carte_main(j, choix);
                printf("%s a joué : ", j->nom);
                afficher_carte(p->carte_dessus);

                int effet = appliquer_effet(p, p->joueur_actuel, p->carte_dessus);

                if (j->estHumain && j->nb_cartes == 1) {
                    printf("Vous avez une carte ! Tapez 'UNO' : ");
                    char buffer[10];
                    demander_chaine(buffer, 10);
                    if (!verifier_uno(j, buffer)) {
                        printf("Vous n'avez pas dit UNO correctement ! Vous piochez 2 cartes.\n");
                        ajouter_carte_main(j, tirer_carte(&p->pioche));
                        ajouter_carte_main(j, tirer_carte(&p->pioche));
                    }
                }

                if (!effet) {
                    passer_au_suivant(p);
                }
            }
        }

        for (int i = 0; i < p->nb_joueurs; i++) {
            if (!p->joueurs[i].estHumain) {
                printf("%s a %d cartes.\n", p->joueurs[i].nom, p->joueurs[i].nb_cartes);
            }
        }

        printf("Appuyez sur entrée pour continuer...\n");
        getchar();
    }

    printf("Partie terminée !\n");
}
