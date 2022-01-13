#include "Jeu.h"
#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

void testAfficher() {
    // TEST afficher
    Partie emptyGame;

    emptyGame.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            emptyGame.plateau[i][j] = VIDE;
        }
    }

    printf("Affichage du tableau vide : \n");
    afficher(&emptyGame);
    printf("\n---------------------------------\n");

    Partie J1Game;

    J1Game.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            J1Game.plateau[i][j] = J1;
        }
    }

    printf("Affichage d'un tableau de O : \n");
    afficher(&J1Game);
    printf("\n---------------------------------\n");

    Partie J2Game;

    J2Game.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            J2Game.plateau[i][j] = J2;
        }
    }

    printf("Affichage d'un tableau de X : \n");
    afficher(&J2Game);
    printf("\n---------------------------------\n");

    Partie realGame;

    realGame.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            if(i % 2 == 0) {
                realGame.plateau[i][j] = VIDE;
            } else if (j % 2 == 0) {
                realGame.plateau[i][j] = J1;
            } else {
                realGame.plateau[i][j] = J2;
            }
        }
    }

    printf("Affichage d'un tableau de jeu : \n");
    afficher(&realGame);
    printf("\n---------------------------------\n");

}

void testJouerCoup() {

    printf("Test du jeu d'un coup invalide :\n");

    Partie partie;
    partie.tour = 1;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            partie.plateau[i][j] = VIDE;
        }
    }

    int coupInvalide = jouerCoup(&partie, -2);
    if (coupInvalide == 0) printf("Le coup joué n'a pas été retenu car il est invalide.\n");
    else printf("Le coup joué est invalide mais a été retenu.\n");
    afficher(&partie);
    printf("\n---------------------------------\n");

    printf("Test du jeu d'un coup valide :\n");

    Partie partie2;
    partie2.tour = 1;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            partie2.plateau[i][j] = VIDE;
        }
    }

    int coupValide = jouerCoup(&partie2, 2);
    if (coupValide == 1) printf("Le coup joué a été retenu car il est valide.\n");
    else printf("Le coup joué est valide mais n'a pas été retenu.\n");
    afficher(&partie2);
    printf("\n---------------------------------\n");

    printf("Test de l'empilement des jetons sur une colonne :\n");

    Partie partie3;
    partie3.tour = 1;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            partie3.plateau[i][j] = VIDE;
        }
    }

    int coup1 = jouerCoup(&partie3, 2);
    int coup2 = jouerCoup(&partie3, 2);
    int coup3 = jouerCoup(&partie3, 2);
    afficher(&partie3);
    printf("\n---------------------------------\n");

}