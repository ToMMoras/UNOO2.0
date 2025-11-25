#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Initialise le générateur de nombres aléatoires
// À appeler une seule fois au début du programme

void init_aleatoire(void);

// Renvoie un nombre aléatoire compris entre min et max inclus
// min : valeur minimale possible
// max : valeur maximale possible

int nombre_aleatoire(int min, int max);

#ifdef __cplusplus
}
#endif
