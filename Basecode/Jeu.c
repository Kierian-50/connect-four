#include "Jeu.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

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
}

int jouerCoup(Partie* partie, int colonne) {
    for (int i = 0; i < 6; i++) {
        if (partie->plateau[i][colonne] == J1 || partie->plateau[i][colonne] == J2) {
            partie->plateau[i-1][colonne] = partie->tour == 1 ? J1 : J2;
            break;
        }
    }
}

Etat calculerEtat(Partie* partie) {
    return EN_COURS;
}

int bouclePrincipale(Partie* partie) {
    while (calculerEtat(partie) == EN_COURS) {
        int selection;
        printf("Choisissez la colonne dans laquelle vous souhaitez insérer votre jeton : ");
        scanf("%d", &selection);
        printf("Selection : %d", selection);
        afficher(partie);
        jouerCoup(partie, selection);
        calculerEtat(partie);
    }
    return 1;
}