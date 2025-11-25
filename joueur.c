#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "joueur.h"
#include "entree.h"
#include "carte.h"

void initialiser_joueur(Joueur* j, const char* nom, int estHumain)
{
    // Copie sécurisée du nom dans la structure et terminaison par '\0'
    strncpy(j->nom, nom, sizeof j->nom - 1);
    j->nom[sizeof j->nom - 1] = '\0';

    // Initialise le nombre de cartes à 0 et définit le type de joueur
    j->nb_cartes = 0;
    j->estHumain = estHumain;
}

void ajouter_carte_main(Joueur* j, Carte c) {
    // Ajoute la carte à la main si la main n'est pas pleine
    if (j->nb_cartes < (int)(sizeof j->main / sizeof j->main[0])) {
        j->main[j->nb_cartes++] = c;
    }
    else {
        // Main pleine, message d'avertissement
        printf("Attention : main pleine pour %s, carte ignoree.\n", j->nom);
    }
}

void retirer_carte_main(Joueur* j, int index) {
    // Vérifie que l'index est valide
    if (index < 0 || index >= j->nb_cartes) return;

    // Décale toutes les cartes après l'index vers la gauche
    for (int i = index; i < j->nb_cartes - 1; i++)
        j->main[i] = j->main[i + 1];

    // Réduit le nombre de cartes
    j->nb_cartes--;
}

void afficher_main(const Joueur* j) {
    printf("\nMain de %s (%d cartes) :\n", j->nom, j->nb_cartes);
    for (int i = 0; i < j->nb_cartes; i++) {
        // Affiche les indices de 1 à N pour que l'utilisateur choisisse facilement
        printf("[%d] ", i + 1);
        afficher_carte(j->main[i]);
    }
}

int choisir_carte(Joueur* j, Carte carte_dessus) {
    afficher_main(j);

    if (j->estHumain) {
        // Humain : 0 pour piocher, 1..N pour jouer une carte
        printf("Choisissez une carte (0 pour piocher) : ");
        int choix = demander_entier(0, j->nb_cartes);
        if (choix == 0) return -1; // -1 indique qu'on pioche
        return choix - 1;           // retourne l'index réel de la carte
    }

    // bot : joue la première carte possible
    for (int i = 0; i < j->nb_cartes; i++) {
        if (carte_peut_etre_jouee(j->main[i], carte_dessus))
            return i;
    }

    // Pas de carte jouable
    return -1;
}

int verifier_uno(Joueur* j, const char* saisie) {
    // Vérifie si le joueur a une seule carte et a dit "UNO"
    return j->nb_cartes == 1 && strcmp(saisie, "UNO") == 0;
}

int main_vide(Joueur* j) {
    // Retourne 1 si la main est vide, 0 sinon
    return j->nb_cartes == 0;
}