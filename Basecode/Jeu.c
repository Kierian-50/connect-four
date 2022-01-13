#include "Jeu.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Allows to display current game
 * @param partie - game to display
 */
void afficher(Partie* partie) {
    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){
            printf("[");
            if (partie->plateau[i][ii] == VIDE){
                printf(" ");
            } else if (partie->plateau[i][ii] == J1) {
                printf("O");
            } else if (partie->plateau[i][ii] == J2) {
                printf("X");
            }
            printf("]");
        }
        printf("\n");
    }
    printf(" ");
    for (int i=0; i<7; i++){
        printf("%d  ", i + 1);
    }
    printf("\n");
}

/**
 * ALlows to play a move in a specific column.
 * @param partie - game on which we must place the move
 * @param colonne - column of the game in which move is placed
 * @return 0 if column is invalid or 1
 */
int jouerCoup(Partie* partie, int colonne) {
    int ret = 0;
    if (colonne >= 1 && colonne <= 7) {
        colonne = colonne - 1;
        for (int i = 0; i < 6; i++) {
            int stop = 0;
            if (partie->plateau[i][colonne] == J1 || partie->plateau[i][colonne] == J2) {
                // If the column is not already filled (i.e. the first row of this column already contains a counter)
                if (i != 0) {
                    partie->plateau[i - 1][colonne] = partie->tour == 1 ? J1 : J2;
                }
                stop = 1;
            } else if (i == 5) {
                partie->plateau[i][colonne] = partie->tour == 1 ? J1 : J2;
                stop = 1;
            }
            if (stop) break;
        }
        ret = 1;
    }
    return ret;
}

/**
 * Allows to check the state of the game (win, lose and egality)
 * @param partie game t
 * @return
 */

//Etat calculerEtat(Partie* partie) {
//    int ret = EN_COURS;
//
//    int joueurActuel = partie->tour == 1 ? J1 : J2;
//
//    for (int i = 0; i < 6; i++) {
//        for (int j = 0; j < 7; j++) {
//            if (j + 4 < 7 && joueurActuel == partie->plateau[i][j + 1] && joueurActuel == partie->plateau[i][j + 2] && joueurActuel == partie->plateau[i][j + 3] && joueurActuel == partie->plateau[i][j + 4]) {
//                ret = joueurActuel == J1 ? VICTOIRE_J1 : VICTOIRE_J2;
//            } else if (i + 4 < 6) {
//                if (joueurActuel == partie->plateau[i + 1][j] && joueurActuel == partie->plateau[i + 2][j] && joueurActuel == partie->plateau[i + 3][j] && joueurActuel == partie->plateau[i + 4][j]) {
//                    ret = joueurActuel == J1 ? VICTOIRE_J1 : VICTOIRE_J2;
//                } else if (j + 4 < 7 && joueurActuel == partie->plateau[i + 1][j + 1] && joueurActuel == partie->plateau[i + 2][j + 2] && joueurActuel == partie->plateau[i + 3][j + 3] && joueurActuel == partie->plateau[i + 4][j + 4]) {
//                    ret = joueurActuel == J1 ? VICTOIRE_J1 : VICTOIRE_J2;
//                } else if (j - 4 >= 0 && joueurActuel == partie->plateau[i + 1][j - 1] && joueurActuel == partie->plateau[i + 2][j - 2] && joueurActuel == partie->plateau[i + 3][j - 3] && joueurActuel == partie->plateau[i + 4][j - 4]) {
//                    ret = joueurActuel == J1 ? VICTOIRE_J1 : VICTOIRE_J2;
//                }
//
//            }
//            if (ret != EN_COURS) break;
//        }
//        if (ret != EN_COURS) break;
//    }
//
//    return ret;
//}

Etat calculerEtat(Partie* partie) {

    int isBoardFull = 0; // 0 = True ; 1 = False

    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){

            if (partie->plateau[i][ii] != VIDE) {

                int nb_pawn = 1;
                int x = i;
                int y = ii;

                // Check horizontally

                while (partie->plateau[i][ii] == partie->plateau[x][y+1] && y+1 >= 0 && y+1 <= 6 && nb_pawn < 4) {
                    y++;
                    nb_pawn++;
                }

                x = i;
                y = ii;

                while (partie->plateau[i][ii] == partie->plateau[x][y-1] && y-1 >= 0 && y-1 <= 6 && nb_pawn < 4) {
                    y--;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == 1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == 2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }

                // Check vertically

                while (partie->plateau[i][ii] == partie->plateau[x+1][y] && x+1 >= 0 && x+1 <= 5 && nb_pawn < 4) {
                    x++;
                    nb_pawn++;
                }

                x = i;
                y = ii;

                while (partie->plateau[i][ii] == partie->plateau[x-1][y] && x-1 >= 0 && x-1 <= 5 && nb_pawn < 4) {
                    x--;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == 1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == 2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }

                // Check diagonally x++ y++

                while (partie->plateau[i][ii] == partie->plateau[x+1][y+1] && x+1 >= 0 && y+1 >= 0 && x+1 <= 5 && y+1 <= 6 && nb_pawn < 4) {
                    x++;
                    y++;
                    nb_pawn++;
                }

                x = i;
                y = ii;


                while (partie->plateau[i][ii] == partie->plateau[x-1][y-1] && x-1 >= 0 && y-1 >= 0 && x-1 <= 5 && y-1 <= 6 && nb_pawn < 4) {
                    x--;
                    y--;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == 1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == 2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }

                // Check y-- x++

                while (partie->plateau[i][ii] == partie->plateau[x+1][y-1] && x+1 >= 0 && y-1 >= 0 && x+1 <= 5 && y-1 <= 6 && nb_pawn < 4) {
                    x++;
                    y--;
                    nb_pawn++;
                }

                x = i;
                y = ii;

                while (partie->plateau[i][ii] == partie->plateau[x-1][y+1] && x-1 >= 0 && y+1 >= 0 && x-1 <= 5 && y+1 <= 6 && nb_pawn < 4) {
                    x--;
                    y++;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == 1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == 2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }
            } else {
                isBoardFull = 1;
            }

        }
    }

    if (isBoardFull == 0) {
        return EGALITE;
    } else {
        return EN_COURS;
    }

}

int bouclePrincipale(Partie* partie) {
    Etat etat = calculerEtat(partie);
    while (etat == EN_COURS) {
        int selection;
        printf("Choisissez la colonne dans laquelle vous souhaitez insérer votre jeton : ");
        scanf("%d", &selection);
        int coup = 1;
        do {
            if (coup == 0) {
                printf("Veuillez choisir une colonne non remplie entre 1 et 7 : ");
                scanf("%d", &selection);
            }
            coup = jouerCoup(partie, selection);
            if (coup) afficher(partie);
        } while (coup != 1);
        etat = calculerEtat(partie);
        if (etat == EN_COURS) partie->tour = 2 - partie->tour + 1;
    }
    if (etat != EGALITE) printf("Gagnant :\n%s", etat == 1 ? "J1" : "J2");
    else printf("Égalité !");
    //printf("%s", strcat("%s a gagné la partie !", partie->tour == 1 ? "J1" : "J2"));
    return 0;
}