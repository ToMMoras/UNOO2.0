#pragma once

#include "carte.h"
#include "paquet.h"

typedef struct {
    char nom[20];
    Carte main[108];
    int nb_cartes;
    int estHumain;  
} Joueur;

void initialiser_joueur(Joueur* j, const char* nom, int estHumain);
void ajouter_carte_main(Joueur* j, Carte c);
void retirer_carte_main(Joueur* j, int index);
void afficher_main(const Joueur* j);
int choisir_carte(Joueur* j, Carte carte_dessus);
int verifier_uno(Joueur* j, const char* saisie);
int main_vide(Joueur* j);
