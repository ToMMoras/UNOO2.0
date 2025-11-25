#pragma once

// Demande à l'utilisateur de saisir un entier compris entre min et max (inclus)
// Boucle jusqu'à ce qu'une valeur valide soit saisie
int demander_entier(int min, int max);

// Demande à l'utilisateur de saisir une chaîne de caractères
// buffer : espace mémoire où stocker la chaîne
// taille  : taille maximale du buffer
void demander_chaine(char* buffer, int taille);
