#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entree.h"

int nombre_aleatoire(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void vider_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}