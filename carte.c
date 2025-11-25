#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "carte.h"


void afficher_carte(Carte c)
{
    // Types conformes à l'adaptation du sujet : "+2", "+4", "JJ", "RV", "PS" ou valeur
    switch (c.type)
    {
    case TYPE_NORMAL:
        printf("%d ", c.valeur);
        break;
    case TYPE_PLUS2:
        printf("+2 ");
        break;
    case TYPE_PLUS4:
        printf("+4 ");
        break;
    case TYPE_JOKER:
        printf("JJ ");
        break;
    case TYPE_INVERSION:
        printf("RV ");
        break;
    case TYPE_PASSER:
        printf("PS ");
        break;
    }

    const char* col = "?";
    switch (c.couleur)
    {
    case ROUGE: col = "R"; break;
    case JAUNE: col = "J"; break;
    case BLEU:  col = "B"; break;
    case VERT:  col = "V"; break;
    case NOIR:  col = "N"; break;
    }

    printf("%s\n", col);
}

// Vérifie si une carte peut être jouée
int carte_peut_etre_jouee(Carte c, Carte dessus)
{
    if (c.couleur == dessus.couleur) return 1;
    if (c.type == dessus.type) return 1;
    if (c.type == TYPE_JOKER || c.type == TYPE_PLUS4) return 1;
    if (c.type == TYPE_NORMAL && dessus.type == TYPE_NORMAL && c.valeur == dessus.valeur) return 1;
    return 0;
}
