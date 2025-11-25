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

// Tire une carte en s'assurant que la pioche est remplie depuis la defausse si vide
Carte tirer_carte_partie(Partie* p) {
    if (p->pioche.nb_cartes <= 0) {
        if (p->defausse.nb_cartes <= 1) {
            Carte vide = { TYPE_NORMAL, NOIR, -1 };
            return vide;
        }
        // Deplace toutes les cartes de la defausse sauf la derniere (top) vers la pioche
        int j = 0;
        Carte top = p->defausse.cartes[p->defausse.nb_cartes - 1];
        for (int i = 0; i < p->defausse.nb_cartes - 1; ++i) {
            p->pioche.cartes[j++] = p->defausse.cartes[i];
        }
        p->pioche.nb_cartes = j;
        p->defausse.nb_cartes = 0;
        p->defausse.cartes[p->defausse.nb_cartes++] = top;
        melanger_paquet(&p->pioche);
    }
    return tirer_carte(&p->pioche);
}

void initialiser_partie(Partie* p, int nb_joueurs)
{
    // Limite le nombre de joueurs entre 2 et 4
    if (nb_joueurs < 2) nb_joueurs = 2;
    if (nb_joueurs > 4) nb_joueurs = 4;

    init_aleatoire(); // initialise le generateur de nombres aleatoires

    initialiser_paquet(&p->pioche); // cree le paquet complet
    melanger_paquet(&p->pioche);    // melange le paquet

    p->defausse.nb_cartes = 0; // defausse vide au depart

    p->nb_joueurs = nb_joueurs;
    p->joueur_actuel = 0; // le joueur 0 commence
    p->sens = 1;           // sens du jeu : 1 = normal, -1 = inverse

    // Initialisation des joueurs
    for (int i = 0; i < p->nb_joueurs; i++) {
        p->joueurs[i].nb_cartes = 0;
        p->joueurs[i].estHumain = 0;
        p->joueurs[i].nom[0] = '\0';
    }

    // Premiere carte sur la table (debut de la defausse)
    p->carte_dessus = tirer_carte_partie(p);
    if (p->defausse.nb_cartes < (int)(sizeof p->defausse.cartes / sizeof p->defausse.cartes[0]))
        p->defausse.cartes[p->defausse.nb_cartes++] = p->carte_dessus;
}

void distribuer_cartes(Partie* p, int cartes_par_joueur)
{
    // Distribue "cartes_par_joueur" cartes a chaque joueur
    for (int r = 0; r < cartes_par_joueur; r++) {
        for (int i = 0; i < p->nb_joueurs; i++) {
            Carte c = tirer_carte_partie(p);
            ajouter_carte_main(&p->joueurs[i], c);
        }
    }
}

int partie_terminee(Partie* p)
{
    // La partie est terminee si un joueur n'a plus de cartes
    for (int i = 0; i < p->nb_joueurs; i++) {
        if (main_vide(&p->joueurs[i])) return 1;
    }
    return 0;
}

int joueur_suivant(Partie* p)
{
    // Calcule l'index du joueur suivant selon le sens du jeu
    int next = p->joueur_actuel + p->sens;
    if (next < 0) next += p->nb_joueurs;
    if (next >= p->nb_joueurs) next -= p->nb_joueurs;
    return next;
}

void passer_au_suivant(Partie* p)
{
    p->joueur_actuel = joueur_suivant(p); // met a jour le joueur actuel
}

void afficher_plateau(const Partie* p)
{
    printf("\n Plateau \n");
    printf("Carte dessus : ");
    afficher_carte(p->carte_dessus); // affiche la carte du dessus
    printf("Pioche: %d cartes | Defausse: %d cartes\n", p->pioche.nb_cartes, p->defausse.nb_cartes);

    // Affiche le nombre de cartes de chaque joueur
    for (int i = 0; i < p->nb_joueurs; i++) {
        printf("%s - %d cartes%s\n", p->joueurs[i].nom[0] ? p->joueurs[i].nom : "Joueur", p->joueurs[i].nb_cartes,
            p->joueurs[i].estHumain ? " (humain)" : "");
        if (p->joueurs[i].estHumain) {
            afficher_main(&p->joueurs[i]); // affiche la main du joueur humain
        }
    }
    printf("Joueur actuel : %s\n", p->joueurs[p->joueur_actuel].nom);
    printf("\n");
}

void boucle_jeu(Partie* p)
{
    while (!partie_terminee(p)) { // boucle jusqu'a ce qu'un joueur ait fini
        afficher_plateau(p);

        Joueur* j = &p->joueurs[p->joueur_actuel]; // joueur courant
        int choix = choisir_carte(j, p->carte_dessus); // humain ou bot

        if (choix == -1) {
            // Le joueur pioche
            Carte c = tirer_carte_partie(p);
            ajouter_carte_main(j, c);
            printf("%s a pioche une carte.\n", j->nom);
            passer_au_suivant(p);
        }
        else {
            // Verifie que la carte jouee est valide
            if (choix < 0 || choix >= j->nb_cartes) {
                printf("Index invalide - vous piochez.\n");
                Carte c = tirer_carte_partie(p);
                ajouter_carte_main(j, c);
                passer_au_suivant(p);
            }
            else {
                Carte played = j->main[choix];

                if (!carte_peut_etre_jouee(played, p->carte_dessus)) {
                    printf("Carte non jouable - vous piochez.\n");
                    Carte c = tirer_carte_partie(p);
                    ajouter_carte_main(j, c);
                    passer_au_suivant(p);
                }
                else if (played.type == TYPE_PLUS4) {
                    // +4 sans bluff : la cible pioche 4 et passe son tour 

                    // Retirer la carte jouee et la mettre sur la defausse 
                    retirer_carte_main(j, choix);
                    p->carte_dessus = played;
                    if (p->defausse.nb_cartes < (int)(sizeof p->defausse.cartes / sizeof p->defausse.cartes[0]))
                        p->defausse.cartes[p->defausse.nb_cartes++] = p->carte_dessus;

                    // Le joueur qui a pose choisit la couleur 
                    char couleur[8] = "";
                    if (j->estHumain) {
                        printf("Choisissez une couleur (Rouge Jaune Bleu Vert) : ");
                        demander_chaine(couleur, sizeof couleur);
                    } else {
                        int r = nombre_aleatoire(0, 3);
                        switch (r) {
                        case 0: strcpy(couleur, "Rouge"); break;
                        case 1: strcpy(couleur, "Jaune"); break;
                        case 2: strcpy(couleur, "Bleu"); break;
                        case 3: strcpy(couleur, "Vert"); break;
                        }
                        printf("Bot choisit couleur %s\n", couleur);
                    }
                    switch (couleur[0]) {
                    case 'R': case 'r': p->carte_dessus.couleur = ROUGE; break;
                    case 'J': case 'j': p->carte_dessus.couleur = JAUNE; break;
                    case 'B': case 'b': p->carte_dessus.couleur = BLEU; break;
                    case 'V': case 'v': p->carte_dessus.couleur = VERT; break;
                    default: break;
                    }

                    // Cible du +4 
                    int cible = joueur_suivant(p);

                    // Pas de bluff : la cible pioche 4 et passe son tour
                    printf("%s pioche 4 cartes.\n", p->joueurs[cible].nom);
                    for (int k = 0; k < 4; k++) ajouter_carte_main(&p->joueurs[cible], tirer_carte_partie(p));
                    p->joueur_actuel = (cible + p->sens + p->nb_joueurs) % p->nb_joueurs;

                    // UNO pour le joueur qui a pose (apres retrait)
                    if (j->estHumain) {
                        printf("Tapez 'UNO' si approprie (ou appuyez sur entree) : ");
                        char buffer[10];
                        demander_chaine(buffer, 10);
                        if (strcmp(buffer, "UNO") == 0) {
                            if (j->nb_cartes != 1) {
                                printf("Faux UNO ! Vous piochez 2 cartes.\n");
                                ajouter_carte_main(j, tirer_carte_partie(p));
                                ajouter_carte_main(j, tirer_carte_partie(p));
                            }
                        } else {
                            if (j->nb_cartes == 1) {
                                printf("Vous avez oublie de crier UNO ! Vous piochez 2 cartes.\n");
                                ajouter_carte_main(j, tirer_carte_partie(p));
                                ajouter_carte_main(j, tirer_carte_partie(p));
                            }
                        }
                    }
                }
                else {
                    // Carte normale ou autre effet gere par appliquer_effet 
                    retirer_carte_main(j, choix);
                    p->carte_dessus = played;
                    if (p->defausse.nb_cartes < (int)(sizeof p->defausse.cartes / sizeof p->defausse.cartes[0]))
                        p->defausse.cartes[p->defausse.nb_cartes++] = p->carte_dessus;

                    printf("%s a joue : ", j->nom);
                    afficher_carte(p->carte_dessus);

                    int effet = appliquer_effet(p, p->joueur_actuel, p->carte_dessus);

                    if (j->estHumain) {
                        printf("Tapez 'UNO' si approprie (ou appuyez sur entree) : ");
                        char buffer[10];
                        demander_chaine(buffer, 10);
                        if (strcmp(buffer, "UNO") == 0) {
                            if (j->nb_cartes != 1) {
                                printf("Faux UNO ! Vous piochez 2 cartes.\n");
                                ajouter_carte_main(j, tirer_carte_partie(p));
                                ajouter_carte_main(j, tirer_carte_partie(p));
                            }
                        } else {
                            if (j->nb_cartes == 1) {
                                printf("Vous avez oublie de crier UNO ! Vous piochez 2 cartes.\n");
                                ajouter_carte_main(j, tirer_carte_partie(p));
                                ajouter_carte_main(j, tirer_carte_partie(p));
                            }
                        }
                    }

                    if (!effet) {
                        passer_au_suivant(p);
                    }
                }
            }
        }

        // Affiche le nombre de cartes du bot
        for (int i = 0; i < p->nb_joueurs; i++) {
            if (!p->joueurs[i].estHumain) {
                printf("%s a %d cartes.\n", p->joueurs[i].nom, p->joueurs[i].nb_cartes);
            }
        }

        printf("Appuyez sur entree pour continuer...\n");
        getchar(); // pause pour que le joueur puisse lire le plateau
    }

    printf("Partie terminee !\n"); // fin du jeu
}
