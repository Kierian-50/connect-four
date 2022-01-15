#include "Jeu.h"
#include "IA.h"

/**
 * Allows to display current game
 * @param partie - game to display
 */
void afficher(Partie* partie) {
    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){
            printf("%s[", "\x1B[0m");
            if (partie->plateau[i][ii] == VIDE){
                printf(" ");
            } else if (partie->plateau[i][ii] == J1) {
                printf("%sO", "\x1B[31m");
            } else if (partie->plateau[i][ii] == J2) {
                printf("%sX", "\x1B[34m");
            }
            printf("%s]", "\x1B[0m");
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
int jouerCoup(Partie* partie, int colonne) { // TODO demander à Matéo s'il gère que la colonne est pleine
    int ret = 0;
    if (colonne >= 1 && colonne <= 7 && partie->plateau[0][colonne - 1] == VIDE) {
        colonne = colonne - 1;
        for (int i = 0; i < 6; i++) {
            int stop = 0;
            if (partie->plateau[i][colonne] != VIDE) {
                partie->plateau[i - 1][colonne] = partie->tour == 1 ? J1 : J2;
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

                while (partie->plateau[i][ii] == partie->plateau[x][y+1] &&
                        y+1 >= 0 &&
                        y+1 <= 6 &&
                        nb_pawn < 4) {
                    y++;
                    nb_pawn++;
                }

                x = i;
                y = ii;

                while (partie->plateau[i][ii] == partie->plateau[x][y-1] &&
                        y-1 >= 0 &&
                        y-1 <= 6 &&
                        nb_pawn < 4) {
                    y--;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == J1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == J2) {
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
                    if (partie->plateau[i][ii] == J1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == J2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }

                // Check diagonally x++ y++

                while (partie->plateau[i][ii] == partie->plateau[x+1][y+1] &&
                        x+1 >= 0 &&
                        y+1 >= 0 &&
                        x+1 <= 5 &&
                        y+1 <= 6 &&
                        nb_pawn < 4) {
                    x++;
                    y++;
                    nb_pawn++;
                }

                x = i;
                y = ii;


                while (partie->plateau[i][ii] == partie->plateau[x-1][y-1] &&
                        x-1 >= 0 &&
                        y-1 >= 0 &&
                        x-1 <= 5 &&
                        y-1 <= 6 &&
                        nb_pawn < 4) {
                    x--;
                    y--;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == J1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == J2) {
                        return VICTOIRE_J2;
                    }
                } else {
                    nb_pawn = 1;
                    x = i;
                    y = ii;
                }

                // Check y-- x++

                while (partie->plateau[i][ii] == partie->plateau[x+1][y-1] &&
                        x+1 >= 0 &&
                        y-1 >= 0 &&
                        x+1 <= 5 &&
                        y-1 <= 6 &&
                        nb_pawn < 4) {
                    x++;
                    y--;
                    nb_pawn++;
                }

                x = i;
                y = ii;

                while (partie->plateau[i][ii] == partie->plateau[x-1][y+1] &&
                        x-1 >= 0 &&
                        y+1 >= 0 &&
                        x-1 <= 5 &&
                        y+1 <= 6 &&
                        nb_pawn < 4) {
                    x--;
                    y++;
                    nb_pawn++;
                }

                // Analyse
                if (nb_pawn >= 4) {
                    if (partie->plateau[i][ii] == J1) {
                        return VICTOIRE_J1;
                    } else if (partie->plateau[i][ii] == J2) {
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

/**
 * Allows to start a game loop : player choose to play against another player or against IA,
 * then loop start and each player play until one of them win
 * @param partie - game to start
 * @return 0 when game is finished
 */
int bouclePrincipale(Partie* partie) {

    initSDL();

    printf("1. Joueur VS IA basique\n2. Joueur VS Joueur\nChoisissez un mode de jeu :");
    int mode;
    scanf("%d", &mode);

    Etat etat = calculerEtat(partie);

    while (etat == EN_COURS) {
        printf("\n%sLe joueur %d joue !\n\n",  partie->tour == 1 ? "\x1B[31m" : "\x1B[34m", partie->tour);

        if (mode == 2 || (mode == 1 && partie->tour == 2)) {
            int colonne;
            int coup = -1;

            do {
                if (coup == -1)
                    printf("%sChoisissez la colonne dans laquelle vous souhaitez inserer votre jeton :", "\x1B[0m");
                else
                    printf("Veuillez choisir une colonne non remplie entre 1 et 7 :");
                scanf("%d", &colonne);
                coup = jouerCoup(partie, colonne);
                if (coup)
                    afficher(partie);
            } while (coup != 1);
        } else {
            int highestEval = 0;
            int columnToPlay = 0;

            for (int j = 0; j < 7; j++) {
                for (int i = 0; i < 6; i++) {
                    if (partie->plateau[0][j] == VIDE && (partie->plateau[i][j] != VIDE || i == 5)) {
                        int eval = evaluationCase(partie, i == 5 ? i : i - 1, j);
                        if (eval > highestEval) {
                            highestEval = eval;
                            columnToPlay = j+1;
                        }
                        break;
                    }
                }
            }

            printf("IA joue : %d\n", columnToPlay);
            jouerCoup(partie, columnToPlay);
            afficher(partie);
        }

        etat = calculerEtat(partie);
        partie->tour = 2 - partie->tour + 1;
    }

    if (etat != EGALITE)
        printf("Gagnant :\n%s", etat == 1 ? "J1" : "J2");
    else
        printf("Égalité !");
    //printf("%s", strcat("%s a gagné la partie !", partie->tour == 1 ? "J1" : "J2"));
    int ret = 0;
    do {
        scanf("\n1. Rejouer\n2. Quitter\nChoisissez une action :%d", &ret);
    } while (ret - 1 < 0 || ret - 1 > 1);
    return ret;
}

// Graphical functions

void nettoyageRessources(SDL_Window *w, SDL_Renderer *r, SDL_Texture *t) {
    SDL_Log("Erreur : %s\n", SDL_GetError());
    if (t != NULL)
        SDL_DestroyTexture(t);
    if (r != NULL)
        SDL_DestroyRenderer(r);
    if (w != NULL)
        SDL_DestroyWindow(w);
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void initSDL() {

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture[6][7];
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect = {0, 0, 640, 480};

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        nettoyageRessources(NULL, NULL, NULL);

    window = SDL_CreateWindow("Connect 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (window == NULL)
        nettoyageRessources(window, NULL, NULL);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
        nettoyageRessources(window, renderer, NULL);

    for (int x = 0; x < 6; x++) {
        for (int y = 0; y < 7; y++) {
            picture[x][y] = SDL_LoadBMP("../images/grid_overlay.bmp");

            texture = SDL_CreateTextureFromSurface(renderer, picture[x][y]);
            SDL_FreeSurface(picture[x][y]);
            if (texture == NULL)
                nettoyageRessources(window, renderer, NULL);
            if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0 || SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
                nettoyageRessources(window, renderer, texture);
        }
    }
//    if (picture == NULL)
//        nettoyageRessources(window, renderer, NULL);

//    texture = SDL_CreateTextureFromSurface(renderer, picture);
//    SDL_FreeSurface(picture);
//    if (texture == NULL)
//        nettoyageRessources(window, renderer, NULL);
//    if (SDL_QueryTexture(texture, NULL, NULL, &dest_rect.w, &dest_rect.h) != 0 || SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
//        nettoyageRessources(window, renderer, texture);

    SDL_RenderPresent(renderer);
    SDL_Delay(5000);

}