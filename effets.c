#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "effets.h"
#include "paquet.h"
#include "entree.h"
#include "joueur.h"
#include "jeu.h"
#include "utils.h"

// Fonction principale qui applique l'effet d'une carte jouée
// Retourne 1 si le joueur courant change directement (ex: +2, +4, Passer)
// Retourne 0 si le joueur suivant doit jouer normalement (ex: Joker, Inversion)

int appliquer_effet(Partie* p, int joueur_index, Carte c)
{
    switch (c.type)
    {
    case TYPE_PLUS2:
        effet_plus2(p);  // Le joueur suivant pioche 2 cartes
        return 1;
    case TYPE_PLUS4:
        effet_plus4(p, joueur_index); // Le joueur suivant pioche 4 cartes et couleur choisie
        return 1;
    case TYPE_PASSER:
        effet_passer(p); // Le joueur suivant est passé
        return 1;
    case TYPE_INVERSION:
        effet_inversion(p); // Inversion du sens de jeu
        return 0;
    case TYPE_JOKER:
        effet_joker(p, joueur_index); // Changement de couleur sans pénalité
        return 0;
    default:
        return 0; // Carte normale, aucun effet spécial
    }
}

// +2 : le joueur suivant pioche 2 cartes et passe son tour
void effet_plus2(Partie* p) {
    int cible = joueur_suivant(p); // identifier le joueur suivant
    printf("%s pioche 2 cartes !\n", p->joueurs[cible].nom);

    for (int i = 0; i < 2; i++)
        ajouter_carte_main(&p->joueurs[cible], tirer_carte_partie(p)); // pioche

    p->joueur_actuel = cible; // sauter le joueur courant
    passer_au_suivant(p);     // passer au joueur suivant
}

// +4 : le joueur suivant pioche 4 cartes et le joueur courant choisit la couleur
void effet_plus4(Partie* p, int joueur_index) {
    int cible = joueur_suivant(p);
    printf("%s pioche 4 cartes !\n", p->joueurs[cible].nom);

    // Pioche de 4 cartes pour le joueur cible
    for (int i = 0; i < 4; i++)
        ajouter_carte_main(&p->joueurs[cible], tirer_carte_partie(p));

    // Choix de couleur
    if (p->joueurs[joueur_index].estHumain) {
        // Si humain, demander une couleur
        printf("Choisissez une couleur (Rouge Jaune Bleu Vert) : ");
        char couleur[5];
        demander_chaine(couleur, 5);

        switch (couleur[0]) {
        case 'R': case 'r': p->carte_dessus.couleur = ROUGE; break;
        case 'J': case 'j': p->carte_dessus.couleur = JAUNE; break;
        case 'B': case 'b': p->carte_dessus.couleur = BLEU; break;
        case 'V': case 'v': p->carte_dessus.couleur = VERT; break;
        default: break; // aucune couleur valide saisie
        }
    }
    else {
        // Bot choisit une couleur aléatoire
        int r = nombre_aleatoire(0, 3);
        switch (r) {
        case 0: p->carte_dessus.couleur = ROUGE; printf("Bot choisit Rouge\n"); break;
        case 1: p->carte_dessus.couleur = JAUNE; printf("Bot choisit Jaune\n"); break;
        case 2: p->carte_dessus.couleur = BLEU;  printf("Bot choisit Bleu\n"); break;
        case 3: p->carte_dessus.couleur = VERT;  printf("Bot choisit Vert\n"); break;
        }
    }

    p->joueur_actuel = cible; // le joueur suivant devient le joueur courant
    passer_au_suivant(p);     // passer au joueur après le cible
}

// Inversion : inverse le sens de jeu
void effet_inversion(Partie* p) {
    p->sens *= -1; // inversion du sens
    printf("Sens inverse !\n");
}

// Passer : le joueur suivant est passé
void effet_passer(Partie* p) {
    int cible = joueur_suivant(p);
    printf("%s est passe !\n", p->joueurs[cible].nom);
    p->joueur_actuel = cible; // sauter le joueur cible
    passer_au_suivant(p);     // passer au joueur suivant
}

// Joker : permet au joueur courant de choisir une couleur
void effet_joker(Partie* p, int joueur_index) {
    if (p->joueurs[joueur_index].estHumain) {
        // Humain choisit la couleur
        printf("Choisissez une couleur (Rouge Jaune Bleu Vert) : ");
        char couleur[5];
        demander_chaine(couleur, 5);
        switch (couleur[0]) {
        case 'R': case 'r': p->carte_dessus.couleur = ROUGE; break;
        case 'J': case 'j': p->carte_dessus.couleur = JAUNE; break;
        case 'B': case 'b': p->carte_dessus.couleur = BLEU; break;
        case 'V': case 'v': p->carte_dessus.couleur = VERT; break;
        default: break;
        }
    }
    else {
        // Bot choisit couleur aléatoirement
        int r = nombre_aleatoire(0, 3);
        switch (r) {
        case 0: p->carte_dessus.couleur = ROUGE; printf("Bot choisit Rouge\n"); break;
        case 1: p->carte_dessus.couleur = JAUNE; printf("Bot choisit Jaune\n"); break;
        case 2: p->carte_dessus.couleur = BLEU;  printf("Bot choisit Bleu\n"); break;
        case 3: p->carte_dessus.couleur = VERT;  printf("Bot choisit Vert\n"); break;
        }
    }
}
