#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "jeu.h"
#include "joueur.h"
#include "paquet.h"
#include "carte.h"
#include "entree.h"

int main()
{
    Partie partie;
    int nb_joueurs = 2; 

  
    initialiser_partie(&partie, nb_joueurs);

    char nom[20];
    printf("Entrez votre nom : ");
    demander_chaine(nom, 20);
    initialiser_joueur(&partie.joueurs[0], nom, 1);   
    initialiser_joueur(&partie.joueurs[1], "Bot", 0); 

    distribuer_cartes(&partie, 7);

    boucle_jeu(&partie);

    return 0;
}
