#pragma once
#include "carte.h"
#include "joueur.h"
#include "jeu.h"

int appliquer_effet(Partie* p, int joueur_index, Carte carte_jouee);
void effet_plus2(Partie* p);
void effet_plus4(Partie* p, int joueur_index);
void effet_inversion(Partie* p);
void effet_passer(Partie* p);
void effet_joker(Partie* p, int joueur_index);
