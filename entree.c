#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "entree.h"

int demander_entier(int min, int max) {
    int x; int ok = 0;
    while (!ok) {
        printf("> ");
        if (scanf("%d", &x) == 1 && x >= min && x <= max) ok = 1;
        else printf("Entrée invalide\n");
        while (getchar() != '\n'); 
    }
    return x;
}

void demander_chaine(char* buffer, int taille) {
    fgets(buffer, taille, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}
