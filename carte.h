#pragma once

// Couleurs possibles des cartes
typedef enum {
    ROUGE,
    JAUNE,
    BLEU,
    VERT,
    NOIR   // pour les jokers et +4
} Couleur;

// Types de cartes possibles
typedef enum {
    TYPE_NORMAL,     // carte normale avec valeur 0-9
    TYPE_PLUS2,      // carte +2
    TYPE_PLUS4,      // carte +4
    TYPE_JOKER,      // carte joker
    TYPE_INVERSION,  // carte inversion de sens
    TYPE_PASSER      // carte passer le tour
} TypeCarte;

// Structure représentant une carte
typedef struct {
    TypeCarte type;   // type de la carte
    Couleur couleur;  // couleur de la carte
    int valeur;       // valeur pour les cartes normales (0-9), -1 pour autres
} Carte;

void afficher_carte(Carte c);

int carte_peut_etre_jouee(Carte c, Carte dessus);
