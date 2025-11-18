#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "paquet.h"
#include "utils.h"

void initialiser_paquet(Paquet* p) {
    // TODO : remplir le paquet avec toutes les cartes
    p->nb_cartes = 108; // placeholder
}

void melanger_paquet(Paquet* p) {
    for (int i = 0; i < p->nb_cartes; i++) {
        int j = nombre_aleatoire(0, p->nb_cartes - 1);
        Carte tmp = p->cartes[i];
        p->cartes[i] = p->cartes[j];
        p->cartes[j] = tmp;
    }
}

Carte tirer_carte(Paquet* p) {
    if (p->nb_cartes <= 0) {
        Carte vide = { 0, NOIR };
        return vide;
    }
    p->nb_cartes--;
    return p->cartes[p->nb_cartes];
}
