#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

void init_aleatoire(void) {
    srand((unsigned int)time(NULL));
}

int nombre_aleatoire(int min, int max) {
    if (min == max) return min;
    if (min > max) {
        int tmp = min;
        min = max;
        max = tmp;
    }

    unsigned int range = (unsigned int)(max - min) + 1u;
    return (int)((unsigned int)rand() % range) + min;
}
