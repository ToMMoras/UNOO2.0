#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "carte.h"


void afficher_carte(Carte c)
{
    // Affiche le type de la carte selon le sujet : +2, +4, Joker, Inversion, Passer, ou valeur normale
    switch (c.type)
    {
    case TYPE_NORMAL:
        printf("%d ", c.valeur); // carte normale affiche sa valeur
        break;
    case TYPE_PLUS2:
        printf("+2 ");           // carte +2
        break;
    case TYPE_PLUS4:
        printf("+4 ");           // carte +4
        break;
    case TYPE_JOKER:
        printf("Joker ");        // Joker
        break;
    case TYPE_INVERSION:
        printf("Inversion ");    // Inversion
        break;
    case TYPE_PASSER:
        printf("Passer ");       // Passer
        break;
    }

    // Affiche la couleur de la carte : Rouge, Jaune, Bleu, Vert, Noir
    const char* col = "?";
    switch (c.couleur)
    {
    case ROUGE: col = "Rouge"; break;
    case JAUNE: col = "Jaune"; break;
    case BLEU:  col = "Bleu"; break;
    case VERT:  col = "Vert"; break;
    case NOIR:  col = "Noir"; break; // pour les jokers et +4
    }

    printf("%s\n", col); // affiche le type + couleur
}

// Verifie si une carte peut etre jouee sur la carte du dessus
int carte_peut_etre_jouee(Carte c, Carte dessus)
{
    if (c.couleur == dessus.couleur) return 1; // meme couleur
    if (c.type == dessus.type) return 1;       // meme type (ex: +2 sur +2)
    if (c.type == TYPE_JOKER || c.type == TYPE_PLUS4) return 1; // Joker ou +4 jouable toujours
    if (c.type == TYPE_NORMAL && dessus.type == TYPE_NORMAL && c.valeur == dessus.valeur) return 1; // meme valeur
    return 0; // sinon non jouable
}
