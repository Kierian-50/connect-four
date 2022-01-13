#include "Jeu.h"
#include "IA.h"
#include <stdio.h>
#include <stdlib.h>

void afficher(Partie* partie){
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

int jouerCoup(Partie* partie, int colonne){
    return 0;
}

Etat calculerEtat(Partie* partie){
    return EN_COURS;
}

int bouclePrincipale(Partie* partie){
    return 0;
}