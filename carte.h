#pragma once

typedef enum { ROUGE, JAUNE, BLEU, VERT, NOIR } Couleur;
typedef enum { N0, N1, N2, N3, N4, N5, N6, N7, N8, N9, PLUS2, INVERSION, PASSER, JOKER, PLUS4 } TypeCarte;

typedef struct {
    TypeCarte type;
    Couleur couleur;
} Carte;

void afficher_carte(Carte c);
int carte_jouable(Carte c, Carte dessus);
