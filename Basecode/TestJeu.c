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

void testCalculerEtat() { // TODO use if and correct limit case with full board

    printf("testCalculerEtat");
    printf("Test cas vertical de J1 gagnant après quatre coup\n");

    Partie gameVertical;

    gameVertical.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameVertical.plateau[i][j] = VIDE;
        }
    }
    afficher(&gameVertical);
    printf("Etat de la game : %d `\n", calculerEtat(&gameVertical));
    gameVertical.plateau[0][0] = J1;
    afficher(&gameVertical);
    gameVertical.plateau[0][1] = J1;
    afficher(&gameVertical);
    gameVertical.plateau[0][2] = J1;
    afficher(&gameVertical);
    gameVertical.plateau[0][3] = J1;
    afficher(&gameVertical);

    printf("Etat de la game : %d \n", calculerEtat(&gameVertical));

    printf("------------------------------------------------\n");

    printf("Test cas horizontal de J2 gagnant après quatre coup\n");

    Partie gameHorizontal;

    gameVertical.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameHorizontal.plateau[i][j] = VIDE;
        }
    }
    afficher(&gameHorizontal);
    printf("Etat de la game : %d `\n", calculerEtat(&gameHorizontal));
    gameHorizontal.plateau[0][0] = J2;
    afficher(&gameHorizontal);
    gameHorizontal.plateau[1][0] = J2;
    afficher(&gameHorizontal);
    gameHorizontal.plateau[2][0] = J2;
    afficher(&gameHorizontal);
    gameHorizontal.plateau[3][0] = J2;
    afficher(&gameHorizontal);

    printf("Etat de la game : %d \n", calculerEtat(&gameHorizontal));

    printf("------------------------------------------------\n");

    printf("Test cas diagonal de J2 gagnant après quatre coup\n");

    Partie gameDiagonal;

    gameDiagonal.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameDiagonal.plateau[i][j] = VIDE;
        }
    }
    afficher(&gameDiagonal);
    printf("Etat de la game : %d `\n", calculerEtat(&gameDiagonal));
    gameDiagonal.plateau[0][0] = J2;
    afficher(&gameDiagonal);
    gameDiagonal.plateau[1][1] = J2;
    afficher(&gameDiagonal);
    gameDiagonal.plateau[2][2] = J2;
    afficher(&gameDiagonal);
    gameDiagonal.plateau[3][3] = J2;
    afficher(&gameDiagonal);
    gameDiagonal.plateau[4][4] = J2;
    afficher(&gameDiagonal);

    printf("Etat de la game : %d \n", calculerEtat(&gameDiagonal));

    printf("------------------------------------------------\n");

    printf("Test cas tableau plein\n");

    Partie gameFull;

    gameFull.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            if (i % 2 == 0){
                if(j % 2 == 0) {
                    gameFull.plateau[i][j] = J2;
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J2;
                    }
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J2;
                    }
                } else {
                    gameFull.plateau[i][j] = J1;
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J1;
                    }
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J1;
                    }
                }
            } else {
                if(j % 2 == 0) {
                    gameFull.plateau[i][j] = J1;
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J1;
                    }
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J1;
                    }
                } else {
                    gameFull.plateau[i][j] = J2;
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J2;
                    }
                    j++;
                    if (i < 6 && j < 7){
                        gameFull.plateau[i][j] = J2;
                    }
                }
            }
        }
    }
    afficher(&gameFull);

    printf("Etat de la game : %d \n", calculerEtat(&gameFull));

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