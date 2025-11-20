#pragma once

#include "carte.h"
#include "paquet.h"

// ===========================================================
// Module : joueur
// Description : Gestion des joueurs (main, choix carte, UNO…)
// ===========================================================

typedef struct {
    char nom[20];
    Carte main[108];
    int nb_cartes;
    int estHumain;   // 1 = humain, 0 = IA
} Joueur;

// Initialisation du joueur
void initialiser_joueur(Joueur* j, const char* nom, int estHumain);

// Gestion des cartes en main
void ajouter_carte_main(Joueur* j, Carte c);
void retirer_carte_main(Joueur* j, int index);

// Affichage
void afficher_main(const Joueur* j);

// Choix d'une carte (humain ou IA)
int choisir_carte(Joueur* j, Carte carte_dessus);

// Vérifie si le joueur a dit UNO
int verifier_uno(Joueur* j, const char* saisie);

// La main est-elle vide ?
int main_vide(Joueur* j);