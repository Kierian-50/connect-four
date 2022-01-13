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

    printf("Affichage d'un vrai tableau de jeu : \n");
    afficher(&realGame);
    printf("\n---------------------------------\n");

}