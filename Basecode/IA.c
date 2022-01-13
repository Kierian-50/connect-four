#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

Partie* copierPartie(Partie* partie){
    return NULL;
}

/**
 * Attention ! Ne fonctionne pour checker les pions du joueur courant car la case étant vide je me base
 * sur le joueur courant pour connaitre la couleur du pion qui sera joué sur la case vide.
 * @param partie
 * @param ligne
 * @param colonne
 * @return
 */
int evaluationCase(Partie* partie, int ligne, int colonne){

    int nb_pawn = 0;
    int x = ligne;
    int y = colonne;
    int opponent = partie->tour == 1 ? J2 : J1;

    printf("\nLe joueur %d est mon adversaire ! ", opponent);
    printf("\nLe joueur courant est %d", partie->tour);
    printf("\nLa case a cote est de %d\n", partie->plateau[5][1]);

    // ==============================
    // Align four pawns
    // ==============================

    // ------------------
    // Check horizontally
    // ------------------

    while (partie->tour == partie->plateau[x][y+1] &&
           y+1 >= 0 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        y++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (partie->tour == partie->plateau[x][y-1] &&
           y-1 >= 0 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        y--;
        nb_pawn++;
    }

    // Analyze
    if (nb_pawn >= 3) {
        return 1000;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ------------------
    // Check vertically
    // ------------------

    while (partie->tour == partie->plateau[x+1][y] && x+1 >= 0 && x+1 <= 5 && nb_pawn < 3) {
        x++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (partie->tour == partie->plateau[x-1][y] && x-1 >= 0 && x-1 <= 5 && nb_pawn < 3) {
        x--;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 1000;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ------------------
    // Check diagonally
    // ------------------
    // x++ y++
    while (partie->tour == partie->plateau[x+1][y+1] &&
           x+1 >= 0 &&
           y+1 >= 0 &&
           x+1 <= 5 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        x++;
        y++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (partie->tour == partie->plateau[x-1][y-1] &&
           x-1 >= 0 &&
           y-1 >= 0 &&
           x-1 <= 5 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        x--;
        y--;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 1000;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // y-- x++
    while (partie->tour == partie->plateau[x+1][y-1] &&
           x+1 >= 0 &&
           y-1 >= 0 &&
           x+1 <= 5 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        x++;
        y--;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (partie->tour == partie->plateau[x-1][y+1] &&
           x-1 >= 0 &&
           y+1 >= 0 &&
           x-1 <= 5 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        x--;
        y++;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 1000;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ===========================
    // Avoid four opponent pawns
    // ===========================

    // ------------------
    // Check horizontally
    // ------------------

    while (opponent == partie->plateau[x][y+1] &&
           y+1 >= 0 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        y++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (opponent == partie->plateau[x][y-1] &&
           y-1 >= 0 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        y--;
        nb_pawn++;
    }

    // Analyze
    if (nb_pawn >= 3) {
        return 900;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ------------------
    // Check vertically
    // ------------------

    while (opponent == partie->plateau[x+1][y] && x+1 >= 0 && x+1 <= 5 && nb_pawn < 3) {
        x++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (opponent == partie->plateau[x-1][y] && x-1 >= 0 && x-1 <= 5 && nb_pawn < 3) {
        x--;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 900;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ------------------
    // Check diagonally
    // ------------------
    // x++ y++
    while (opponent == partie->plateau[x+1][y+1] &&
           x+1 >= 0 &&
           y+1 >= 0 &&
           x+1 <= 5 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        x++;
        y++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (opponent == partie->plateau[x-1][y-1] &&
           x-1 >= 0 &&
           y-1 >= 0 &&
           x-1 <= 5 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        x--;
        y--;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 900;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // y-- x++
    while (opponent == partie->plateau[x+1][y-1] &&
           x+1 >= 0 &&
           y-1 >= 0 &&
           x+1 <= 5 &&
           y-1 <= 6 &&
           nb_pawn < 3) {
        x++;
        y--;
        nb_pawn++;
    }

    x = ligne;
    y = colonne;

    while (opponent == partie->plateau[x-1][y+1] &&
           x-1 >= 0 &&
           y+1 >= 0 &&
           x-1 <= 5 &&
           y+1 <= 6 &&
           nb_pawn < 3) {
        x--;
        y++;
        nb_pawn++;
    }

    // Analyse
    if (nb_pawn >= 3) {
        return 900;
    } else {
        nb_pawn = 0;
        x = ligne;
        y = colonne;
    }

    // ===================
    // Best choice
    // ===================

    // horizontally // TODO

    return 0;
}

int evaluation(Partie* partie){
    return 0;
}

Arbre* minmax(Partie* partie, int profondeur, int IA){
    return NULL;
}

void detruireArbre(Arbre* arbre){
    
}