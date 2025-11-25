#pragma once
#include "carte.h"

typedef struct {
    Carte cartes[108];
    int nb_cartes;
} Paquet;

void initialiser_paquet(Paquet* p);
Carte tirer_carte(Paquet* p);
void melanger_paquet(Paquet* p);
