#pragma once
#include "carte.h"

// Structure représentant un paquet de cartes UNO
typedef struct {
    Carte cartes[108]; // tableau contenant toutes les cartes du paquet
    int nb_cartes;     // nombre de cartes actuellement dans le paquet
} Paquet;

// Initialise un paquet complet avec toutes les cartes selon les règles de l'UNO
void initialiser_paquet(Paquet* p);

// Tire la carte du haut du paquet (ou retourne une carte "vide" si le paquet est vide)
Carte tirer_carte(Paquet* p);

// Mélange aléatoirement les cartes du paquet
void melanger_paquet(Paquet* p);
