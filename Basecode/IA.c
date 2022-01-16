#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * This method allows to copy a game past in parameter, recreate it in another memory location and return it.
 * Cette méthode permet de copier une partie passée en parametre, la recréé dans un zutre emplacement mémoire et le
 * retourne.
 * @param partie - The game to copy | La partie à copier.
 * @return The copy of the game | La copie de la partie.
 */
Partie* copierPartie(Partie* partie){
    Partie* p = malloc(sizeof(Partie));
    p->tour = partie->tour;

    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){
            p->plateau[i][ii] = partie->plateau[i][ii];
        }
    }

    return p;
}

/**
 * This method is able to count the score of a square. The square can be empty or with a pawn on it.
 * Beware ! Work only to check the pawns of the current player because the square can be empty, so the code is based on
 * the current player to know the color of the pawn that can be play.
 * Cette méthode permet de compter le score d'une case. La case peut être vide ou avec un pion sur elle.
 * Attention ! Ne fonctionne que pour compter les pions du joueur courant car la case pouvant être vide,le code se base
 * sur le joueur courant pour connaitre la couleur du pion qui sera joué.
 * @param partie - The game | La partie.
 * @param ligne - The line where the square is | La case où la case est.
 * @param colonne - The column where the square is | La colonne où la case est.
 * @return 1000 : If the move cause the win of the player | Si le mouvement cause la victoire du joueur.
 *         900 : If the movement avoid the win of the opponent | Si le mouvement empêche la victoire de l'adversaire.
 *         Else : The number of possibilities for the current player on this square.
 *         Sinon : Le nombre de possibilité pour le joueur courant sur le carré.
 */
int evaluationCase(Partie* partie, int ligne, int colonne){

    int nb_pawn = 0;
    int x = ligne;
    int y = colonne;
    int opponent = partie->tour == 1 ? J2 : J1;

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
    // => Si le nombre total de pion de la ligne du joueur ou de case vide de taille max 3 d'un côté, moins trois est supérieur à 0 alors la ligne
    // La ligne possède au moins une possibilité

    int total_possibility = 0;
    int total_pawn_line = 0;

    // ------------------
    // Check horizontally
    // ------------------

    while (opponent != partie->plateau[x][y] &&
            y >= 0 &&
            y <= 6 &&
            nb_pawn < 4) {
        y++;
        nb_pawn++;
    }

    x = ligne;
    y = colonne-1; // Avoid to count two time the original square
    total_pawn_line += nb_pawn;
    nb_pawn = 0;

    while (opponent != partie->plateau[x][y] &&
            y >= 0 &&
            y <= 6 &&
            nb_pawn < 3) {
        y--;
        nb_pawn++;
    }

    total_pawn_line += nb_pawn;

    if (total_pawn_line-3 > 0) {
        total_possibility += total_pawn_line - 3;
    }
    nb_pawn = 0;
    total_pawn_line = 0;
    x = ligne;
    y = colonne;

    // ------------------
    // Check vertically
    // ------------------

    while (opponent != partie->plateau[x][y] && x >= 0 && x <= 5 && nb_pawn < 4) {
        x++;
        nb_pawn++;
    }

    x = ligne-1; // Avoid to count two time the original square
    y = colonne;
    total_pawn_line += nb_pawn;
    nb_pawn = 0;

    while (opponent != partie->plateau[x][y] && x >= 0 && x <= 5 && nb_pawn < 3) {
        x--;
        nb_pawn++;
    }

    total_pawn_line += nb_pawn;

    if (total_pawn_line-3 > 0) {
        total_possibility += total_pawn_line - 3;
    }
    nb_pawn = 0;
    total_pawn_line = 0;
    x = ligne;
    y = colonne;

    // ------------------
    // Check diagonally
    // ------------------
    // x++ y++
    while (opponent != partie->plateau[x][y] &&
           x >= 0 &&
           y >= 0 &&
           x <= 5 &&
           y <= 6 &&
           nb_pawn < 4) {
        x++;
        y++;
        nb_pawn++;
    }

    x = ligne-1; // Avoid to count two time the original square
    y = colonne-1; // Avoid to count two time the original square
    total_pawn_line += nb_pawn;
    nb_pawn = 0;

    while (opponent != partie->plateau[x][y] &&
           x >= 0 &&
           y >= 0 &&
           x <= 5 &&
           y <= 6 &&
           nb_pawn < 3) {
        x--;
        y--;
        nb_pawn++;
    }

    total_pawn_line += nb_pawn;

    if (total_pawn_line-3 > 0) {
        total_possibility += total_pawn_line - 3;
    }
    nb_pawn = 0;
    total_pawn_line = 0;
    x = ligne;
    y = colonne;

    // y-- x++
    while (opponent != partie->plateau[x][y] &&
           x >= 0 &&
           y >= 0 &&
           x <= 5 &&
           y <= 6 &&
           nb_pawn < 4) {
        x++;
        y--;
        nb_pawn++;
    }

    x = ligne - 1;
    y = colonne + 1 ;
    total_pawn_line += nb_pawn;
    nb_pawn = 0;


    while (opponent != partie->plateau[x][y] &&
           x >= 0 &&
           y >= 0 &&
           x <= 5 &&
           y <= 6 &&
           nb_pawn < 3) {
        x--;
        y++;
        nb_pawn++;
    }

    total_pawn_line += nb_pawn;

    if (total_pawn_line-3 > 0) {
        total_possibility += total_pawn_line - 3;
    }
    nb_pawn = 0;
    total_pawn_line = 0;
    x = ligne;
    y = colonne;

    return total_possibility;
}

/**
 * This method allows to give a number to a game according to the possition of the pawn.
 * Cette méthode permet de donner un nombre à une partie selon la position des pions.
 * @param partie The game to evaluate | La partie à évaluer.
 * @return The score of the game | Le score de la partie.
 */
int evaluation(Partie* partie){
    int score = 0;
    int currentPlayer = partie->tour;
    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){
            if (partie->plateau[i][ii] == partie->tour) {
                score += evaluationCase(partie, i, ii);
            } else if (partie->plateau[i][ii] == 2 - partie->tour + 1) {
                partie->tour = 2 - partie->tour + 1;
                score -= evaluationCase(partie, i, ii);
                partie->tour = currentPlayer;
            }
        }
    }
    return score;
}

Arbre* minmax(Partie* partie, int profondeur, int IA){

    Arbre *arbre = (Arbre*) calloc(1, sizeof(arbre));
    arbre->partie = copierPartie(partie);

    Etat state = calculerEtat(partie);
    // Check that the game is over
    if (state != EN_COURS) {
        if (state == VICTOIRE_J1) {
            arbre->score = 1000;
            return arbre;
        } else if (state == VICTOIRE_J2) {
            arbre->score = -1000;
            return arbre;
        } else if (state == EGALITE) {
            arbre->score = 0;
            return arbre;
        }
    }

    if (profondeur == 0) {
        arbre->score = evaluation(partie);
        return arbre;
    }

    for (int i=0; i<=7; i++) {
        Partie* pCopy = copierPartie(partie);

        pCopy->tour = IA == 1 ? J1 : J2;

        if (jouerCoup(pCopy, i) == 1) {
            arbre->enfants[i] = minmax(pCopy, profondeur-1, 1-IA);
            if (arbre->score < arbre->enfants[i]->score) {
                arbre->score = arbre->enfants[i]->score;
            } else {
                free(pCopy);
            }
        }
    }

    return arbre;
}

void detruireArbre(Arbre* arbre){
    free(arbre);
}