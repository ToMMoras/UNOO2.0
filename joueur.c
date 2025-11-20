#include <stdio.h>
#include <string.h>
#include "joueur.h"
#include "entree.h"   // demander_entier, demander_chaine

// Initialise un joueur
void initialiser_joueur(Joueur* j, const char* nom, int estHumain)
{
    strncpy(j->nom, nom, 19);
    j->nom[19] = '\0';

    j->nb_cartes = 0;
    j->estHumain = estHumain;
}

// Ajoute une carte à la main
void ajouter_carte_main(Joueur* j, Carte c)
{
    j->main[j->nb_cartes] = c;
    j->nb_cartes++;
}

// Retire une carte selon l’index
void retirer_carte_main(Joueur* j, int index)
{
    if (index < 0 || index >= j->nb_cartes)
        return;

    for (int i = index; i < j->nb_cartes - 1; i++)
        j->main[i] = j->main[i + 1];

    j->nb_cartes--;
}

// Affiche les cartes du joueur
void afficher_main(const Joueur* j)
{
    printf("\nMain de %s (%d cartes) :\n", j->nom, j->nb_cartes);
    for (int i = 0; i < j->nb_cartes; i++) {
        printf(" [%d] ", i);
        afficher_carte(j->main[i]);   // ← doit exister dans carte.c
    }
    printf("\n");
}

// Choix d'une carte à jouer
int choisir_carte(Joueur* j, Carte carte_dessus)
{
    afficher_main(j);

    if (j->estHumain) {
        printf("\nChoisissez une carte à jouer ou -1 pour piocher : ");
        int choix = demander_entier(-1, j->nb_cartes - 1);
        return choix;
    }

    // IA simple : jouer la première carte compatible
    for (int i = 0; i < j->nb_cartes; i++) {
        if (carte_peut_etre_jouee(j->main[i], carte_dessus)) { // doit exister dans carte.c
            return i;
        }
    }

    return -1; // IA pioche
}

// Vérifie si le joueur a crié UNO
int verifier_uno(Joueur* j, const char* saisie)
{
    if (j->nb_cartes == 1 && strcmp(saisie, "UNO") == 0)
        return 1;

    return 0;
}

// Vérifie si le joueur n’a plus de cartes
int main_vide(Joueur* j)
{
    return j->nb_cartes == 0;
}
