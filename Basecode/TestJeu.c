#include "Jeu.h"
#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * This method allows to test the display board method's (Afficher). The test isn't automated.
 * Cette méthode permet de tester la méthode d'affichage du tableau de jeu via la méthode afficher. Le test n'est pas
 * automatisé.
 */
void testAfficher() {

    printf("===================================\n");
    printf("testAfficher\n");
    printf("===================================\n\n");

    // init game to test
    Partie emptyGame;

    emptyGame.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            emptyGame.plateau[i][j] = VIDE;
        }
    }

    printf("Affichage d'un tableau vide : \n");
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

    printf("Affichage d'un tableau de jeu aléatoire : \n");
    afficher(&realGame);
    printf("\nFin du test d'Afficher\n");
    printf("\n---------------------------------\n");

}

/**
 * This method allows to test the method which placed a pawn in a column of the board. This test is automated.
 * Cette méthode permet de tester la méthode de placement de pions dans une colonne d'une tableau. Ce test est
 * automatisé.
 */
void testJouerCoup() {

    printf("===================================\n");
    printf("testJouerCoup\n");
    printf("===================================\n\n");

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

    printf("Test d'un coup sur une colonne pleine :\n");
    jouerCoup(&partie3, 2);
    jouerCoup(&partie3, 2);
    jouerCoup(&partie3, 2);

    if (jouerCoup(&partie3, 2) == 0) printf("Le coup joué n'a pas été retenu car il est invalide.\n");
    else printf("Le coup joué est invalide mais a été retenu.\n");
    afficher(&partie3);
    printf("\n---------------------------------\n");


}

/**
 * This method allows to test the method which calculate the state of the game. This test is automated.
 * Cette methode permet de tester la méthode qui calcule l'état d'une partie. Le test est automatisé.
 */
void testCalculerEtat() {

    printf("===================================\n");
    printf("testCalculerEtat\n");
    printf("===================================\n\n");
    printf("Test cas vertical de J2 gagnant après quatre coups\n\n");

    Partie gameVertical;

    gameVertical.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameVertical.plateau[i][j] = VIDE;
        }
    }
    if (calculerEtat(&gameVertical) == 0) printf("Test vertical en cours : OK\n");
    else {
        printf("Test vertical en cours : ERREUR\n");
        afficher(&gameVertical);
    }

    gameVertical.plateau[0][0] = J2;
    gameVertical.plateau[0][1] = J2;
    gameVertical.plateau[0][2] = J2;

    if (calculerEtat(&gameVertical) == 0) printf("Test vertical en cours : OK\n");
    else {
        printf("Test vertical en cours : ERREUR\n");
        afficher(&gameVertical);
    }

    gameVertical.plateau[0][3] = J2;

    // Victory of J2
    if (calculerEtat(&gameVertical) == 2) printf("Test vertical, victoire J2 : OK\n");
    else {
        printf("Test vertical, victoire J2 : ERREUR\n");
        afficher(&gameVertical);
    }

    printf("\n------------------------------------------------\n\n");
    printf("Test cas horizontal de J1 gagnant après cinq coups\n");

    Partie gameHorizontal;

    gameHorizontal.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameHorizontal.plateau[i][j] = VIDE;
        }
    }

    if (calculerEtat(&gameHorizontal) == 0) printf("Test horizontale en cours : OK\n");
    else {
        printf("Test horizontale en cours : ERREUR\n");
        afficher(&gameHorizontal);
    }

    gameHorizontal.plateau[0][0] = J1;
    gameHorizontal.plateau[1][0] = J1;
    gameHorizontal.plateau[2][0] = J1;
    gameHorizontal.plateau[4][0] = J1;

    if (calculerEtat(&gameHorizontal) == 0) printf("Test horizontale en cours : OK\n");
    else {
        printf("Test horizontale en cours : ERREUR\n");
        afficher(&gameHorizontal);
    }

    gameHorizontal.plateau[3][0] = J1;

    if (calculerEtat(&gameHorizontal) == 1) printf("Test horizontale, Victoire J1 : OK\n");
    else {
        printf("Test horizontale, Victoire J1 : ERREUR\n");
        afficher(&gameHorizontal);
    }

    printf("\n----------------------------------\n\n");
    printf("Test cas diagonal de J2 gagnant après quatre coups\n");

    Partie gameDiag;

    gameDiag.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameDiag.plateau[i][j] = VIDE;
        }
    }

    if (calculerEtat(&gameDiag) == 0) printf("Test diagonal en cours : OK\n");
    else {
        printf("Test diagonal en cours : ERREUR\n");
        afficher(&gameDiag);
    }

    gameDiag.plateau[0][0] = J1;
    gameDiag.plateau[1][1] = J1;
    gameDiag.plateau[2][2] = J1;

    if (calculerEtat(&gameDiag) == 0) printf("Test diagonal en cours : OK\n");
    else {
        printf("Test diagonal en cours : ERREUR\n");
        afficher(&gameDiag);
    }

    gameDiag.plateau[3][3] = J1;

    if (calculerEtat(&gameDiag) == 1) printf("Test diagonal, Victoire J1 : OK\n");
    else {
        printf("Test diagonal, Victoire J1 : ERREUR\n");
        afficher(&gameDiag);
    }

    printf("\n------------------------------------------------\n\n");
    printf("Test cas diagonal de J1 gagnant après quatre coups\n");

    Partie gameBugDiag;

    gameBugDiag.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameBugDiag.plateau[i][j] = VIDE;
        }
    }

    if (calculerEtat(&gameBugDiag) == 0) printf("Test diagonal en cours : OK\n");
    else {
        printf("Test diagonal en cours : ERREUR\n");
        afficher(&gameBugDiag);
    }

    gameBugDiag.plateau[5][0] = J1;
    gameBugDiag.plateau[4][1] = J1;
    gameBugDiag.plateau[3][2] = J1;

    if (calculerEtat(&gameBugDiag) == 0) printf("Test diagonal en cours : OK\n");
    else {
        printf("Test diagonal en cours : ERREUR\n");
        afficher(&gameBugDiag);
    }

    gameBugDiag.plateau[2][3] = J1;

    if (calculerEtat(&gameBugDiag) == 1) printf("Test diagonal, Victoire J1 : OK\n");
    else {
        printf("Test diagonal, Victoire J1 : ERREUR\n");
        afficher(&gameBugDiag);
    }


    printf("\n----------------------------------\n\n");
    printf("Test cas vertical de J2 gagnant contre J1\n");

    Partie gameBug;

    gameDiag.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            gameBug.plateau[i][j] = VIDE;
        }
    }

    if (calculerEtat(&gameBug) == 0) printf("Test vertical 2 en cours : OK\n");
    else {
        printf("Test vertical 2 en cours : ERREUR\n");
        afficher(&gameBug);
    }

    gameBug.plateau[5][0] = J2;
    gameBug.plateau[5][1] = J1;
    gameBug.plateau[4][0] = J2;
    gameBug.plateau[4][1] = J1;
    gameBug.plateau[3][0] = J2;
    gameBug.plateau[3][1] = J1;

    if (calculerEtat(&gameBug) == 0) printf("Test vertical 2 en cours : OK\n");
    else {
        printf("Test vertical 2 en cours : ERREUR\n");
        afficher(&gameBug);
    }

    gameBug.plateau[2][0] = J2;

    if (calculerEtat(&gameBug) == 2) printf("Test vertical 2, Victoire J2 : OK\n");
    else {
        printf("Test vertical 2, Victoire J2: ERREUR\n");
        afficher(&gameBug);
    }

    printf("\n----------------------------------\n\n");
    printf("Test cas égalité\n");

    Partie gameFull;

    gameFull.tour = 0;
    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            if (i % 2 == 0){
                if(j % 2 == 0) {
                    gameFull.plateau[i][j] = J2;
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J2;
                    }
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J2;
                    }
                } else {
                    gameFull.plateau[i][j] = J1;
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J1;
                    }
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J1;
                    }
                }
            } else {
                if(j % 2 == 0) {
                    gameFull.plateau[i][j] = J1;
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J1;
                    }
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J1;
                    }
                } else {
                    gameFull.plateau[i][j] = J2;
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J2;
                    }
                    j++;
                    if (i < 5 && j < 6){
                        gameFull.plateau[i][j] = J2;
                    }
                }
            }
        }
    }
    gameFull.plateau[5][1] = J1;
    gameFull.plateau[5][2] = J1;
    gameFull.plateau[5][4] = J2;
    gameFull.plateau[5][5] = J2;


    if (calculerEtat(&gameFull) == 3) printf("Test egalite : OK\n");
    else {
        printf("Test egalite: ERREUR\n");
        afficher(&gameFull);
    }

}

/**
 * This method allows to test the method which is able to calculate the possibilities from a square. This test is
 * automated. I took an example that we did during the lesson.
 * Cette méthode permet de tester la méthode qui est capable de calculer les possibilités depuis une case. Ce test est
 * automatisé. J'ai pris un exemple que nous avons fait dans le cours.
 *
 * [ ][ ][ ][ ][ ][ ][ ]
 * [ ][ ][ ][ ][ ][ ][ ]
 * [ ][ ][ ][ ][ ][ ][ ]
 * [ ][ ][ ][ ][ ][ ][ ]
 * [ ][ ][X][ ][ ][ ][ ]
 * [X][O][O][ ][ ][ ][ ]
 *
 */
void testEvaluationCase() {

    printf("===================================\n");
    printf("testEvaluationCase\n");
    printf("===================================\n\n");
    printf("Test cas vertical de J2 gagnant après quatre coups\n\n");

    Partie partie;

    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            partie.plateau[i][j] = VIDE;
        }
    }

    partie.plateau[5][1] = J1;
    partie.plateau[5][2] = J1;
    partie.plateau[4][2] = J2;
    partie.plateau[5][0] = J2;

    afficher(&partie);

    partie.tour = J2;
    printf("\nCalcule des pions de J2 : \n");

    if (evaluationCase(&partie, 5, 0) == 2) printf("Pion (5,0) : OK\n");
    else printf("Pion (5,0) : ERREUR\n");

    if (evaluationCase(&partie, 4, 2) == 6) printf("Pion (4,2) : OK\n");
    else printf("Pion (4,2) : ERREUR\n");

    partie.tour = J1;
    printf("\nCalcule des pions de J1 : \n");

    if (evaluationCase(&partie, 5, 1) == 2) printf("Pion (5,1) : OK\n");
    else printf("Pion (5,1) : ERREUR\n");

    if (evaluationCase(&partie, 5, 2) == 3) printf("Pion (5,2) : OK\n");
    else printf("Pion (5,2) : ERREUR\n");

    partie.tour = J2;
    printf("\nCalcul des cases vides vu par J2 : \n");

    if (evaluationCase(&partie, 5, 3) == 4) printf("Case (5,3) : OK\n");
    else printf("Case (5,3) : ERREUR\n");

    if (evaluationCase(&partie, 4, 1) == 5) printf("Case (5,3) : OK\n");
    else printf("Case (5,3) : ERREUR\n");

    if (evaluationCase(&partie, 4, 0) == 4) printf("Case (4,0) : OK\n");
    else printf("Case (4,0) : ERREUR\n");

    if (evaluationCase(&partie, 4, 3) == 9) printf("Case (4,3) : OK\n");
    else printf("Case (4,3) : ERREUR\n");

    if (evaluationCase(&partie, 3, 3) == 12) printf("Case (3,3) : OK\n");
    else printf("Case (3,3) : ERREUR\n");

    if (evaluationCase(&partie, 2, 3) == 13) printf("Case (2,3) : OK\n");
    else printf("Case (2,3) : ERREUR\n");

    if (evaluationCase(&partie, 4, 4) == 8) printf("Case (4,4) : OK\n");
    else printf("Case (4,4) : ERREUR\n");

    if (evaluationCase(&partie, 5, 5) == 3) printf("Case (5,5) : OK\n");
    else printf("Case (5,5) : ERREUR\n");

    if (evaluationCase(&partie, 0, 4) == 5) printf("Case (0,4) : OK\n");
    else printf("Case (0,4) : ERREUR\n");

    printf("\n\nAdd a J1 pawn in (5,3) to test the possibility of win\n\n");

    partie.plateau[5][3] = J1;

    afficher(&partie);
    printf("\n");

    // For J2, he've to avoid the win of the opponent.
    // Pour J2, il a à éviter la victoire de l'adversaire.
    if (evaluationCase(&partie, 5, 4) == 900) printf("J2 : Case (5,4) : OK\n");
    else printf("J2 : Case (5,4) : ERREUR\n");

    partie.tour = J1;
    // For J1, he've to win
    // Pour J1, il a gagné
    if (evaluationCase(&partie, 5, 4) == 1000) printf("J1 : Case (5,4) : OK\n");
    else printf("J2 : Case (5,4) : ERREUR\n");

}

/**
 * This method allows to test the method which is able to evaluate a game. The test is automated.
 * Cette méthode permet de tester la méthode qui permet d'évaluer une partie. Le test est automatisé.
 */
void testEvaluation() {

    printf("===================================\n");
    printf("testEvaluation\n");
    printf("===================================\n\n");

    Partie firstGame;

    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            firstGame.plateau[i][j] = VIDE;
        }
    }

    firstGame.plateau[5][1] = J1;
    firstGame.plateau[5][2] = J1;
    firstGame.plateau[4][2] = J2;
    firstGame.plateau[5][0] = J2;

    afficher(&firstGame);

    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][X][ ][ ][ ][ ]
    // [X][O][O][ ][ ][ ][ ]
    // => 3 for J2

    firstGame.tour = J2;

    if (evaluation(&firstGame) == 3) printf("Evaluation de la première partie : OK\n\n");
    else printf("Evaluation de la première partie : ERREUR\n\n");


    Partie secondGame;

    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            secondGame.plateau[i][j] = VIDE;
        }
    }

    secondGame.plateau[5][1] = J1;
    secondGame.plateau[5][2] = J1;
    secondGame.plateau[4][2] = J2;
    secondGame.plateau[5][3] = J2;

    afficher(&secondGame);

    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][ ][ ][ ][ ][ ]
    // [ ][ ][X][ ][ ][ ][ ]
    // [ ][O][O][X][ ][ ][ ]
    // => 8 for J2

    secondGame.tour = J2;

    if (evaluation(&secondGame) == 8) printf("\nEvaluation de la seconde partie : OK\n");
    else printf("\nEvaluation de la seconde partie : ERREUR\n");
}

void testMinMax() {
    Partie firstGame;
    firstGame.tour = J2;

    for (int i=0; i<6; i++){
        for (int j=0; j<7; j++){
            firstGame.plateau[i][j] = VIDE;
        }
    }

    firstGame.plateau[5][1] = J1;
    firstGame.plateau[5][2] = J1;
    firstGame.plateau[4][2] = J2;
    firstGame.plateau[5][0] = J2;

    afficher(&firstGame);

    Arbre* arbre = minmax(&firstGame, 5, 1);

    afficher(arbre->partie);
    printf("\n%d\n", arbre->score);

//    for (int i=0; i<7; i++) {
//        printf("%d", arbre->enfants[i]->score);
//    }
//    detruireArbre(arbre);
}