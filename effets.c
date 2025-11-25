#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "effets.h"
#include "paquet.h"
#include "entree.h"
#include "joueur.h"
#include "jeu.h"
#include "utils.h"

int appliquer_effet(Partie* p, int joueur_index, Carte c)
{
    // Applique l'effet de la carte jouée
    // Retourne 1 si le joueur courant change directement (comme +2 ou +4), 0 sinon
    switch (c.type)
    {
    case TYPE_PLUS2:     effet_plus2(p); return 1;
    case TYPE_PLUS4:     effet_plus4(p, joueur_index); return 1;
    case TYPE_PASSER:    effet_passer(p); return 1;
    case TYPE_INVERSION: effet_inversion(p); return 0;
    case TYPE_JOKER:     effet_joker(p, joueur_index); return 0;
    default: return 0;
    }
}

void effet_plus2(Partie* p) {
    int cible = joueur_suivant(p); // joueur suivant pioche 2 cartes
    printf("%s pioche 2 cartes !\n", p->joueurs[cible].nom);
    for (int i = 0; i < 2; i++)
        ajouter_carte_main(&p->joueurs[cible], tirer_carte(&p->pioche));
    p->joueur_actuel = cible; // on saute le joueur courant
    passer_au_suivant(p);
}

void effet_plus4(Partie* p, int joueur_index) {
    int cible = joueur_suivant(p); // joueur suivant pioche 4 cartes
    printf("%s pioche 4 cartes !\n", p->joueurs[cible].nom);
    for (int i = 0; i < 4; i++)
        ajouter_carte_main(&p->joueurs[cible], tirer_carte(&p->pioche));

    // Choix de la couleur pour le joueur humain ou aléatoire pour le bot
    if (p->joueurs[joueur_index].estHumain) {
        printf("Choisissez une couleur (R J B V) : ");
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
        int r = nombre_aleatoire(0, 3); // bot choisit une couleur au hasard
        switch (r) {
        case 0: p->carte_dessus.couleur = ROUGE; printf("Bot choisit ROUGE\n"); break;
        case 1: p->carte_dessus.couleur = JAUNE; printf("Bot choisit JAUNE\n"); break;
        case 2: p->carte_dessus.couleur = BLEU; printf("Bot choisit BLEU\n"); break;
        case 3: p->carte_dessus.couleur = VERT; printf("Bot choisit VERT\n"); break;
        }
    }

    p->joueur_actuel = cible;
    passer_au_suivant(p);
}

void effet_inversion(Partie* p) {
    p->sens *= -1; // inverse le sens du jeu
    printf("Sens inversé !\n");
}

void effet_passer(Partie* p) {
    int cible = joueur_suivant(p); // joueur suivant est passé
    printf("%s est passe !\n", p->joueurs[cible].nom);
    p->joueur_actuel = cible;
    passer_au_suivant(p);
}

void effet_joker(Partie* p, int joueur_index) {
    // Choix de couleur similaire à +4
    if (p->joueurs[joueur_index].estHumain) {
        printf("Choisissez une couleur (R J B V) : ");
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
        int r = nombre_aleatoire(0, 3);
        switch (r) {
        case 0: p->carte_dessus.couleur = ROUGE; printf("Bot choisit ROUGE\n"); break;
        case 1: p->carte_dessus.couleur = JAUNE; printf("Bot choisit JAUNE\n"); break;
        case 2: p->carte_dessus.couleur = BLEU; printf("Bot choisit BLEU\n"); break;
        case 3: p->carte_dessus.couleur = VERT; printf("Bot choisit VERT\n"); break;
        }
    }
}