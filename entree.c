#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "entree.h"

int demander_entier(int min, int max) {
    int x;
    int ok = 0;

    // Boucle jusqu'à ce que l'utilisateur saisisse un entier valide
    while (!ok) {
        printf("> ");
        // scanf retourne 1 si un entier a été lu correctement
        if (scanf("%d", &x) == 1 && x >= min && x <= max)
            ok = 1; // saisie valide
        else
            printf("Entree invalide\n");

        // Vide le buffer pour éviter les caractères résiduels
        while (getchar() != '\n');
    }

    return x; // retourne l'entier valide
}

void demander_chaine(char* buffer, int taille) {
    // Lit une chaîne de caractères depuis l'entrée standard
    fgets(buffer, taille, stdin);

    // Supprime le '\n' final éventuel ajouté par fgets
    buffer[strcspn(buffer, "\n")] = '\0';
}

