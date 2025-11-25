#pragma once

#include "carte.h"
#include "paquet.h"

// Structure représentant un joueur
typedef struct {
    char nom[20];       
    Carte main[108];    
    int nb_cartes;      // nombre actuel de cartes en main
    int estHumain;      // 1 si joueur humain, 0 si bot
} Joueur;

// Initialise un joueur avec un nom et son type (humain ou bot)
void initialiser_joueur(Joueur* j, const char* nom, int estHumain);

// Ajoute une carte à la main du joueur si possible
void ajouter_carte_main(Joueur* j, Carte c);

// Retire une carte à un index donné dans la main du joueur
void retirer_carte_main(Joueur* j, int index);

// Affiche toutes les cartes de la main du joueur
void afficher_main(const Joueur* j);

// Demande au joueur (humain ou IA) de choisir une carte jouable
int choisir_carte(Joueur* j, Carte carte_dessus);

// Vérifie si le joueur a dit "UNO" correctement
int verifier_uno(Joueur* j, const char* saisie);

// Retourne 1 si la main du joueur est vide, 0 sinon
int main_vide(Joueur* j);
