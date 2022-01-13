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
    int ret = 0;
    if (colonne >= 1 && colonne <= 7) {
        for (int i = 0; i < 6; i++) {
            int stop = 0;
            if (partie->plateau[i][colonne] == J1 || partie->plateau[i][colonne] == J2) {
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
        int coup = 1;
        do {
            if (coup == 0) printf("Veuillez choisir une colonne entre 1 et 7.");
            coup = jouerCoup(partie, selection);
        } while (coup != 1);
        calculerEtat(partie);
        partie->tour = 2 - partie->tour + 1;
    }
    return 1;
}