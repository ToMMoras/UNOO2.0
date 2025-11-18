#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "carte.h"

void afficher_carte(Carte c) {
    const char* couleurs[] = { "R", "J", "B", "V", "N" };
    const char* types[] = { "0","1","2","3","4","5","6","7","8","9","+2","RV","PS","JJ","+4" };
    printf("%s%s", types[c.type], couleurs[c.couleur]);
}

int carte_jouable(Carte c, Carte dessus) {
    return c.couleur == dessus.couleur || c.type == dessus.type || c.couleur == NOIR;
}
