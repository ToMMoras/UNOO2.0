#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "joueur.h"
#include "entree.h"
#include "carte.h"

void initialiser_joueur(Joueur* j, const char* nom, int estHumain)
{
    strncpy(j->nom, nom, sizeof j->nom - 1);
    j->nom[sizeof j->nom - 1] = '\0';
    j->nb_cartes = 0;
    j->estHumain = estHumain;
}

void ajouter_carte_main(Joueur* j, Carte c) {
    if (j->nb_cartes < (int)(sizeof j->main / sizeof j->main[0])) {
        j->main[j->nb_cartes++] = c;
    } else {
        // main pleine — ignorer ou loguer
        printf("Attention : main pleine pour %s, carte ignorée.\n", j->nom);
    }
}

void retirer_carte_main(Joueur* j, int index) {
    if (index < 0 || index >= j->nb_cartes) return;
    for (int i = index; i < j->nb_cartes - 1; i++)
        j->main[i] = j->main[i + 1];
    j->nb_cartes--;
}

void afficher_main(const Joueur* j) {
    printf("\nMain de %s (%d cartes) :\n", j->nom, j->nb_cartes);
    for (int i = 0; i < j->nb_cartes; i++) {
        // afficher indices 1..N (conforme au sujet)
        printf("[%d] ", i + 1);
        afficher_carte(j->main[i]);
    }
}

int choisir_carte(Joueur* j, Carte carte_dessus) {
    afficher_main(j);
    if (j->estHumain) {
        // 0 pour piocher, 1..N pour cartes affichées
        printf("Choisissez une carte (0 pour piocher) : ");
        int choix = demander_entier(0, j->nb_cartes);
        if (choix == 0) return -1;
        return choix - 1;
    }
    for (int i = 0; i < j->nb_cartes; i++) {
        if (carte_peut_etre_jouee(j->main[i], carte_dessus))
            return i;
    }
    return -1;
}

int verifier_uno(Joueur* j, const char* saisie) {
    return j->nb_cartes == 1 && strcmp(saisie, "UNO") == 0;
}

int main_vide(Joueur* j) {
    return j->nb_cartes == 0;
}
