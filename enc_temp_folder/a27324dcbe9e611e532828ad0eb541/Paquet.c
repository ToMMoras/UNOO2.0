#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "paquet.h"
#include "utils.h"
#include "joueur.h"  

void initialiser_paquet(Paquet* p) {
    int idx = 0;
    Couleur couleurs[] = { ROUGE, JAUNE, BLEU, VERT };

    for (int c = 0; c < 4; c++) {
        p->cartes[idx++] = (Carte){ TYPE_NORMAL, couleurs[c], 0 };
        for (int v = 1; v <= 9; v++) {
            p->cartes[idx++] = (Carte){ TYPE_NORMAL, couleurs[c], v };
            p->cartes[idx++] = (Carte){ TYPE_NORMAL, couleurs[c], v };
        }
        for (int e = 0; e < 2; e++) {
            p->cartes[idx++] = (Carte){ TYPE_PLUS2, couleurs[c], -1 };
            p->cartes[idx++] = (Carte){ TYPE_INVERSION, couleurs[c], -1 };
            p->cartes[idx++] = (Carte){ TYPE_PASSER, couleurs[c], -1 };
        }
    }

    for (int i = 0; i < 4; i++) {
        p->cartes[idx++] = (Carte){ TYPE_JOKER, NOIR, -1 };
        p->cartes[idx++] = (Carte){ TYPE_PLUS4, NOIR, -1 };
    }

    p->nb_cartes = idx;
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
        Carte vide = { TYPE_NORMAL, NOIR, -1 };
        return vide;
    }
    p->nb_cartes--;
    return p->cartes[p->nb_cartes];
}
