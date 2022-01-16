#include "Jeu.h"
#include "IA.h"
#include "Sound.h"

/**
 * This method allows to diplay the current game past in parameter.
 * Cette méthod permet d'afficher la partie courante passé en parametre.
 * @param partie - Game to display | La partie à afficher.
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
 * This method aLlows to play a move in a specific column.
 * Cette méthode permet de jouer un mouvement dans une colonne particulière.
 * @param partie - Game on which we must place the move.
 *                 La partie sur laquelle on veut faire le mouvement.
 * @param colonne - Column of the game in which the pawn is placed.
 *                  La colonne dans laquelle on veut placer le pion.
 * @return 0 if the placement is invalid else 1.
 *         0 si le placement est invalide sinon 1.
 */
int jouerCoup(Partie* partie, int colonne) {
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
 * This method allows to check the state of the game (win, lose and egality).
 * Cette méthode permet de vérifier l'état de la partie (gagné, perdu et égalité).
 * @param partie - The game which we calculate the state.
 *                 La partie sur laquelle on calcul l'état.
 * @return An element of the enum Etat which says the state of the game.
 *         Un element de l'énumération d'un Etat qui donne l'état de la partie.
 */
Etat calculerEtat(Partie* partie) {

    int isBoardFull = 0; // 0 = True ; 1 = False

    for (int i=0; i<6; i++){
        for (int ii=0; ii<7; ii++){

            // Avoid to test the long test if the square is empty
            // Moreover it will help to know if the game is draw.
            // Evite de tester le long test si la case est vide
            // De plus, ca aidera à savoir si la partie est égalité.
            if (partie->plateau[i][ii] != VIDE) {

                int nb_pawn = 1;
                int x = i;
                int y = ii;

                // ----------------------
                // Check horizontally
                // ----------------------

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

                // ----------------------
                // Check vertically
                // ----------------------

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

                // ----------------------
                // Check diagonally x++ y++
                // ----------------------

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

                // ----------------------
                // Check y-- x++
                // ----------------------
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
 * Allows to start a game loop : start music, display menus and start loop.
 * Player choose to play against another player or against IA, then he can choose to play in graphical or in console mode.
 * After those, the loop start and each player play until one of them win.
 * @param partie - game to start
 * @return 1 if players want to replay or 0
 */
int bouclePrincipale(Partie* partie) {

    // create a new thread to play music theme in loop
    pthread_t threadId;
    pthread_create(&threadId, NULL, loopMusicTheme, NULL);

    // Select game mode
    printf("\n1. Joueur VS IA\n2. Joueur VS Joueur\nChoisissez un mode de jeu : ");
    int mode;
    scanf("%d", &mode);
    while (mode != 1 && mode != 2) {
        printf("Veuillez sélectionner l'option 1 ou 2 : ");
        scanf("%d", &mode);
    }

    int ia = 0;
    if (mode == 1) {
//        printf("\n1. IA basique\n2. IA moyenne\nChoisissez le niveau de difficulté : ");
        printf("\n1. IA basique\nChoisissez le niveau de difficulté : ");
        scanf("%d", &ia);
        while (ia != 1) {
            printf("Veuillez sélectionner l'option 1 : ");
            scanf("%d", &ia);
        }
    }

    // Select interface mode
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
                if (ia == 1)
                    playBasicIAShot(partie, interface);
//                else if (ia == 2)
//                    playMediumIAShot(partie, interface);
            }

            etat = calculerEtat(partie);
            partie->tour = 2 - partie->tour + 1;
        }
    } else {
        etat = graphicalLoop(partie, mode, ia);
    }

    // Stop music theme loop and close audio device
    pthread_cancel(threadId);
    SDL_Quit();

    // Display winner
    if (etat == VICTOIRE_J1 || etat == VICTOIRE_J2) {
        if (mode == 2 || (mode == 1 && etat == VICTOIRE_J2)) {
            pthread_t win;
            pthread_create(&win, NULL, playWinMusic, NULL);
        } else if (mode == 1 && etat == VICTOIRE_J1) {
            pthread_t lose;
            pthread_create(&lose, NULL, playLoseMusic, NULL);
        }
        printf("\nGagnant :\n%s", etat == 1 ? "\x1B[31mJ1\x1B[0m" : "\x1B[33mJ2\x1B[0m");
    } else if (etat == EGALITE) {
        printf("Égalité !");
    }

    // Ask for replay
    printf("\n\n1. Quitter\n2. Rejouer\nChoisissez une action : ");
    int ret = 0;
    scanf("%d", &ret);
    while (ret != 1 && ret != 2) {
        printf("Veuillez sélectionner l'option 1 ou 2 : ");
        scanf("%d", &ret);
    }

    return (ret - 1);
}

/**
 * This function allows to play an IA shot in function of score returned by evaluationCase
 * @param partie game on which IA must play his shot
 * @param interface interface chosen by player : display IA shot if we are in console mode
 */
int playBasicIAShot(Partie* partie, int interface) {
    int highestEval = 0;
    int columnToPlay = 0;

    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 6; i++) {
            if (partie->plateau[0][j] == VIDE && (partie->plateau[i][j] != VIDE || i == 5)) {
                int eval = evaluationCase(partie, i == 5 ? i : i - 1, j);
                if (eval >= highestEval) {
                    highestEval = eval;
                    columnToPlay = j+1;
                }
                break;
            }
        }
    }

    int coup = jouerCoup(partie, columnToPlay);
    if (interface == 2) {
        afficher(partie);
        printf("IA a joué : %d", columnToPlay);
    }
    return coup;
}

/**
 * This function allows to play a medium IA shot in function of score returned by evaluationCase
 * @param partie game on which IA must play his shot
 * @param interface interface chosen by player : display IA shot if we are in console mode
 */
int playMediumIAShot(Partie* partie, int interface) {

    Arbre* arbre = minmax(partie, 6, 1);

    int columnToPlay = -1;

    for (int i=1; i<=7; i++) {
        if (arbre->enfants[i]->score == 1000) {
            columnToPlay = i;
            break;
        } else if (arbre->enfants[i]->score == -1000) {
            columnToPlay = i;
            break;
        }
    }

    if (columnToPlay == -1){
        int max = -10000;
        for (int i=1; i<=7; i++) {
            if (max <= columnToPlay) {
                columnToPlay = i;
            }
        }
    }

    int coup = jouerCoup(partie, columnToPlay);
    if (interface == 2) {
        afficher(partie);
        printf("IA a joué : %d", columnToPlay);
    }
    return coup;
}

/**
 * This function allows to display a game in graphical mode thanks to SDL2 library
 * @param partie game to display
 * @param mode chosen mode : IA vs Player or Player vs Player
 * @param ia chosen ia mode : basic or medium
 * @return state of the game : EGALITE, VICTOIRE_J1 or VICTOIRE_J2
 */
Etat graphicalLoop(Partie *partie, int mode, int ia) {

    // define grid cell size, grid width, grid height, window width and window height
    int grid_cell_size = 100;
    int grid_width = 7;
    int grid_height = 6;
    int window_width = (grid_width * grid_cell_size) + 1;
    int window_height = (grid_height * grid_cell_size) + 1;

    // Create the current pawn to play without draw it on the grid
    SDL_Rect pawn = {0,0,grid_cell_size - 1,grid_cell_size - 1,};

    // Create a mouse hover cursor
    SDL_Rect hover = {pawn.x, pawn.y, grid_cell_size,grid_cell_size};

    // Define color used
    SDL_Color grid_background_color = {22, 22, 22, 255};
    SDL_Color grid_line_color = {44, 44, 44, 255};
    SDL_Color grid_hover_color = {44, 44, 44, 255};
    // Red
    SDL_Color p1_color = {255, 0, 0, 255};
    // Yellow
    SDL_Color p2_color = {255, 255, 0, 255};

    // Init video device
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",SDL_GetError());
        return -1;
    }

    // Init window
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

    // Start event loop
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
                    // Select current case on which we will add an hover effect
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

        // Play IA shot
        if (mode == 1 && partie->tour == 1) {
            if (ia == 1)
                coup = playBasicIAShot(partie, 1);
//            else if (ia == 2)
//                coup = playMediumIAShot(partie, 1);
        }

        // Draw grid pawns.
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (partie->plateau[i][j] == J1) {
                    SDL_SetRenderDrawColor(renderer, p1_color.r, p1_color.g, p1_color.b, p1_color.a);
                    pawn.x = j * grid_cell_size;
                    pawn.y = i * grid_cell_size;
                    drawCircle(renderer, pawn.x + 50, pawn.y + 50, 40);
                } else if (partie->plateau[i][j] == J2) {
                    SDL_SetRenderDrawColor(renderer, p2_color.r, p2_color.g, p2_color.b, p2_color.a);
                    pawn.x = j * grid_cell_size;
                    pawn.y = i * grid_cell_size;
                    drawCircle(renderer, pawn.x + 50, pawn.y + 50, 40);
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

    // Close window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return etat;

}

/**
 * This function allows to draw a filled circle point per point
 * @param renderer scene on which we render our circle
 * @param x horizontal coordinate of center of circle
 * @param y vertical coordinate of center of circle
 * @param radius radius of the circle
 */
void drawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius))
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
        }
    }
}