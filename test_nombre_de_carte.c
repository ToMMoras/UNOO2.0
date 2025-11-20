#include <stdio.h>
#include "carte.h"
#include "paquet.h"

int main() {
    Paquet p;
    initialiser_paquet(&p);
    melanger_paquet(&p);

    printf("Nombre de cartes : %d\n", p.nb_cartes);

    for (int i = 0; i < 5; i++) {
        Carte c = tirer_carte(&p);
        printf("Carte tirée : ");
        afficher_carte(c);
        printf("\n");
    }

    printf("Cartes restantes : %d\n", p.nb_cartes);

    return 0;
}