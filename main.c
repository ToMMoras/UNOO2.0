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
    int nb_joueurs = 2; // Nombre de joueurs dans la partie (1 humain + 1 bot ici)

    // Initialisation de la partie : création du paquet, joueurs, etc.
    initialiser_partie(&partie, nb_joueurs);

    char nom[20];
    printf("Entrez votre nom : ");
    demander_chaine(nom, 20); // Demande le nom du joueur humain

    // Initialisation du joueur humain et du bot
    initialiser_joueur(&partie.joueurs[0], nom, 1);   // joueur humain
    initialiser_joueur(&partie.joueurs[1], "Bot", 0); // bot

    // Distribution de 7 cartes à chaque joueur
    distribuer_cartes(&partie, 7);

    // Lancement de la boucle principale du jeu (tour par tour)
    boucle_jeu(&partie);

    return 0; // Fin du programme
}

