#pragma once

// =============================================================
// Module : carte
// Gestion des cartes UNO
// =============================================================

typedef enum {
    ROUGE,
    JAUNE,
    BLEU,
    VERT,
    NOIR
} Couleur;

typedef enum {
    TYPE_NORMAL,
    TYPE_PLUS2,
    TYPE_PLUS4,
    TYPE_JOKER,
    TYPE_INVERSION,
    TYPE_PASSER
} TypeCarte;

typedef struct {
    TypeCarte type;
    Couleur couleur;
    int valeur;    
} Carte;

void afficher_carte(Carte c);

int carte_peut_etre_jouee(Carte c, Carte dessus);
