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
                printf("%sX", "\x1B[33m");
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

    // Select game mode
    printf("\n1. Joueur VS IA basique\n2. Joueur VS Joueur\nChoisissez un mode de jeu : ");
    int mode;
    scanf("%d", &mode);
    while (mode != 1 && mode != 2) {
        printf("Veuillez sélectionner l'option 1 ou 2 : ");
        scanf("%d", &mode);
    }

    // Select interface
    printf("\n1. Jouer en mode graphique\n2. Jouer en mode console\nChoisissez une interface : ");
    int interface;
    scanf("%d", &interface);
    while (interface != 1 && interface != 2) {
        printf("Veuillez sélectionner l'option 1 ou 2 : ");
        scanf("%d", &interface);
    }

    Etat etat = calculerEtat(partie);

    if (interface == 2) {
        while (etat == EN_COURS) {
            printf("\n%sLe joueur %d joue !\n\n", partie->tour == 1 ? "\x1B[31m" : "\x1B[33m", partie->tour);

            if (mode == 2 || (mode == 1 && partie->tour == 2)) {
                int colonne;
                int coup = -1;

                do {
                    if (coup == -1)
                        printf("%sChoisissez la colonne dans laquelle vous souhaitez inserer votre jeton : ", "\x1B[0m");
                    else
                        printf("Veuillez choisir une colonne non remplie entre 1 et 7 : ");
                    scanf("%d", &colonne);
                    coup = jouerCoup(partie, colonne);
                    if (coup)
                        afficher(partie);
                } while (coup != 1);
            } else {
                jouerCoupIA(partie, interface);
            }

            etat = calculerEtat(partie);
            partie->tour = 2 - partie->tour + 1;
        }
    } else {
        etat = boucleGraphique(partie, mode);
    }

    // Display winner
    if (etat == VICTOIRE_J1 || etat == VICTOIRE_J2)
        printf("\nGagnant :\n%s", etat == 1 ? "\x1B[31mJ1\x1B[0m" : "\x1B[33mJ2\x1B[0m");
    else if (etat == EGALITE)
        printf("Égalité !");

    // Ask to replay
    printf("\n\n1. Quitter\n2. Rejouer\nChoisissez une action : ");
    int ret = 0;
    scanf("%d", &ret);
    while (ret != 1 && ret != 2) {
        printf("Veuillez sélectionner l'option 1 ou 2 : ");
        scanf("%d", &ret);
    }
    return (ret - 1);
}

void jouerCoupIA(Partie* partie, int interface) {
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

    jouerCoup(partie, columnToPlay);
    if (interface == 2) {
        afficher(partie);
        printf("IA a joué : %d\n", columnToPlay);
    } else {
         // Wait before IA play in graphical mode (so, player can see the new move)
         sleep(1);
     }
}

// Graphical interface
Etat boucleGraphique(Partie *partie, int mode) {

    int grid_cell_size = 36;
    int grid_width = 7;
    int grid_height = 6;

    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Create the current pawn to play without draw it on the grid
    SDL_Rect pawn = {0,0,grid_cell_size - 1,grid_cell_size - 1,};

    // Create a mouse hover cursor
    SDL_Rect hover = {pawn.x, pawn.y, grid_cell_size,grid_cell_size};

    SDL_Color grid_background_color = {22, 22, 22, 255};
    SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
    SDL_Color grid_hover_color = {44, 44, 44, 255};
    // Red
    SDL_Color p1_color = {255, 0, 0, 255};
    // Yellow
    SDL_Color p2_color = {255, 255, 0, 255};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",SDL_GetError());
        return -1;
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    if (SDL_CreateWindowAndRenderer(window_width, window_height, 0, &window,&renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,"Create window and renderer: %s", SDL_GetError());
        return -1;
    }

    SDL_SetWindowTitle(window, "Connect 4");

    SDL_bool quit = SDL_FALSE;
    SDL_bool mouse_active = SDL_FALSE;
    SDL_bool mouse_hover = SDL_FALSE;

    Etat etat = calculerEtat(partie);

    while (!quit && etat == EN_COURS) {
        SDL_Event event;
        int coup = 0;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN:
                    // Place a new pawn at the clicked case.
                    if (mode == 2 || (mode == 1 && partie->tour == 2))
                        coup = jouerCoup(partie, event.motion.x/grid_cell_size + 1);
                    break;
                case SDL_MOUSEMOTION:
                    // Select current case on which we will ad an hover effect
                    hover.x = (event.motion.x / grid_cell_size) * grid_cell_size;
                    hover.y = (event.motion.y / grid_cell_size) * grid_cell_size;
                    if (!mouse_active)
                        mouse_active = SDL_TRUE;
                    break;
                case SDL_WINDOWEVENT:
                    // Set hover to true
                    if (event.window.event == SDL_WINDOWEVENT_ENTER && !mouse_hover)
                        mouse_hover = SDL_TRUE;
                    else if (event.window.event == SDL_WINDOWEVENT_LEAVE && mouse_hover)
                        mouse_hover = SDL_FALSE;
                    break;
                case SDL_QUIT:
                    // Quit graphical interface
                    quit = SDL_TRUE;
                    break;
            }
        }
        // Draw grid background.
        SDL_SetRenderDrawColor(renderer, grid_background_color.r, grid_background_color.g,grid_background_color.b, grid_background_color.a);
        SDL_RenderClear(renderer);

        // Draw grid lines.
        SDL_SetRenderDrawColor(renderer, grid_line_color.r, grid_line_color.g,grid_line_color.b, grid_line_color.a);
        for (int x = 0; x < 1 + grid_width * grid_cell_size; x += grid_cell_size)
            SDL_RenderDrawLine(renderer, x, 0, x, window_height);
        for (int y = 0; y < 1 + grid_height * grid_cell_size; y += grid_cell_size)
            SDL_RenderDrawLine(renderer, 0, y, window_width, y);

        // Draw grid hover cursor.
        if (mouse_active && mouse_hover) {
            SDL_SetRenderDrawColor(renderer, grid_hover_color.r,grid_hover_color.g,grid_hover_color.b,grid_hover_color.a);
            SDL_RenderFillRect(renderer, &hover);
        }

        if (mode == 1 && partie->tour == 1) {
            coup = 1;
            jouerCoupIA(partie, 1);
        }

        // Draw grid pawns.
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (partie->plateau[i][j] == J1) {
                    SDL_SetRenderDrawColor(renderer, p1_color.r, p1_color.g, p1_color.b, p1_color.a);
                    pawn.x = j * grid_cell_size;
                    pawn.y = i * grid_cell_size;
                    SDL_RenderFillRect(renderer, &pawn);
                } else if (partie->plateau[i][j] == J2) {
                    SDL_SetRenderDrawColor(renderer, p2_color.r, p2_color.g, p2_color.b, p2_color.a);
                    pawn.x = j * grid_cell_size;
                    pawn.y = i * grid_cell_size;
                    SDL_RenderFillRect(renderer, &pawn);
                }
            }
        }

        // If new pawn is placed, change player
        if (coup) {
            etat = calculerEtat(partie);
            partie->tour = partie->tour == J1 ? J2 : J1;
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return etat;

}