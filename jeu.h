#pragma once

#include "carte.h"
#include "paquet.h"
#include "joueur.h"

// Structure représentant une partie d'UNO
typedef struct
{
    Paquet pioche;        
    Paquet defausse;      
    Joueur joueurs[4];    // tableau des joueurs (max 4)
    int nb_joueurs;       
    int joueur_actuel;    
    int sens;             
    Carte carte_dessus;   
} Partie;

// Initialise la partie : pioche, défausse, joueurs et première carte
void initialiser_partie(Partie* p, int nb_joueurs);

// Distribue un nombre donné de cartes à chaque joueur
void distribuer_cartes(Partie* p, int cartes_par_joueur);

// Boucle principale du jeu : tours des joueurs jusqu'à la fin
void boucle_jeu(Partie* p);

// Vérifie si un joueur a fini sa main et donc si la partie est terminée
int partie_terminee(Partie* p);

// Renvoie l'index du joueur suivant en tenant compte du sens du jeu
int joueur_suivant(Partie* p);

// Passe au joueur suivant
void passer_au_suivant(Partie* p);

// Affiche l'état complet du plateau : cartes, joueurs et pioche/défausse
void afficher_plateau(const Partie* p);

/* Tire une carte en gérant le re-remplissage depuis la défausse si nécessaire */
Carte tirer_carte_partie(Partie* p);
