#pragma once
#include "carte.h"
#include "joueur.h"
#include "jeu.h"

// Applique l'effet d'une carte jouée
// Retourne 1 si le tour du joueur courant change directement (ex: +2, +4, passer), 0 sinon
int appliquer_effet(Partie* p, int joueur_index, Carte carte_jouee);

// Effet +2 : le joueur suivant pioche 2 cartes et passe son tour
void effet_plus2(Partie* p);

// Effet +4 : le joueur suivant pioche 4 cartes, le joueur actif choisit une couleur
void effet_plus4(Partie* p, int joueur_index);

// Effet Inversion : inverse le sens du jeu
void effet_inversion(Partie* p);

// Effet Passer : le joueur suivant passe son tour
void effet_passer(Partie* p);

// Effet Joker : permet de choisir la couleur pour continuer le jeu
void effet_joker(Partie* p, int joueur_index);
