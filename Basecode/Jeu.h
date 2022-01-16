#pragma once

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Les différents états possibles d'une partie
typedef enum{EN_COURS, VICTOIRE_J1, VICTOIRE_J2, EGALITE} Etat;
//Les valeurs possibles d'une case dans la grille
typedef enum{VIDE, J1, J2} Case;

typedef struct {
    Case plateau[6][7]; //la grille de jeu, la ligne 0 est la plus proche du sol
    int tour; //1 ou 2, le joueur dont c'est le tour
} Partie;
/**
*Partie 1 : moteur du jeu
**/

/**
*Affichage de la partie en ligne de commande
**/
void afficher(Partie* partie);
/**
*Fonction appliquant le coup du joueur sur le plateau, et changeant la valeur de partie->tour (1->2 ou 2->1)
*Renvoie 0 si le coup est impossible, 1 sinon
**/
int jouerCoup(Partie* partie, int colonne);
/**
*Fonction calculant l'état actuel de la partie :
*EN_COURS : personne n'a gagné, et il est toujours possible de jouer (i.e. la grille n'est pas pleine) ;
*VICTOIRE_J1 ou VICTOIRE_J2 : un joueur a réussi à aligner 4 pions ou plus (vertical, horizontal ou diagonal) ;
*EGALITE : la grille est pleine et aucun joueur n'a gagné
**/
Etat calculerEtat(Partie* partie);
/**
*Première boucle du jeu, en mode console
*A chaque itération, le joueur dont c'est le tour est invité à saisir un numéro de colonne (entre 1 et 7)
*Une fois un coup valide joué, on vérifie l'état
*On répète tant que l'état est EN_COURS
*Renvoie 1 si les joueurs veulent rejouer, 0 sinon
**/
int bouclePrincipale(Partie* partie);
void jouerCoupIA(Partie* partie, int interface);
Etat boucleGraphique(Partie *partie, int mode);