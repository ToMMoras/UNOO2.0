#pragma once

#include "carte.h"
#include "paquet.h"
#include "joueur.h"


typedef struct
{
    Paquet pioche;
    Paquet defausse;
    Joueur joueurs[4];
    int nb_joueurs;
    int joueur_actuel;
    int sens;
    Carte carte_dessus;
} Partie;


void initialiser_partie(Partie* p, int nb_joueurs);
void distribuer_cartes(Partie* p, int cartes_par_joueur);
void boucle_jeu(Partie* p);                
int partie_terminee(Partie* p);
int joueur_suivant(Partie* p);
void passer_au_suivant(Partie* p);
void afficher_plateau(const Partie* p);      
