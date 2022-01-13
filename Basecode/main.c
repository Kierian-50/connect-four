#include "Jeu.h"
#include "IA.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
    Partie partie;
   
    int tour = 2;
    do{
        partie.tour = tour;
        for (int i=0; i<6; i++){
            for (int j=0; j<7; j++){
                partie.plateau[i][j] = 0;
            }
        }
        tour = 2 - tour + 1;
    } while(bouclePrincipale(&partie));
    
    return 0;
}