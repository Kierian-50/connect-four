#include "Jeu.h"
#include "TestJeu.h"
#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    Partie partie;

    testAfficher();
    testJouerCoup();

//    int tour = 2;
//    do{
//        partie.tour = tour;
//        for (int i=0; i<6; i++){
//            for (int j=0; j<7; j++){
//                partie.plateau[i][j] = VIDE;
//            }
//        }
//        tour = 2 - tour + 1;
//    } while(bouclePrincipale(&partie));

    return 0;
}