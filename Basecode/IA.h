#pragma once
#include "Jeu.h"

//Arbre de décision
typedef struct sArbre{
    Partie* partie; //La partie représentée par le noeud d'arbre
    int score; //la valeur du noeud
    struct sArbre* enfants[7]; //les dérivations possibles de la partie (7 coups possibles au maximum)
} Arbre;

/**
** Fonction utilisée par le minmax
** Alloue un pointeur sur partie et copie les informations de la partie en paramètre
**/
Partie* copierPartie(Partie* partie);
/**
** Evaluation d'une partie pour le minmax
**/
int evaluation(Partie* partie);
/**
** Evalution d'une case pour l'IA basique
**/
int evaluationCase(Partie* partie, int ligne, int colonne);
/**
** Construction de l'arbre de décision (voir cours sur minmax)
** la partie est l'état du plateau représenté par le noeud courant de l'arbre -> la racine représente l'état actuel, et les autres noeuds des possibilités
** la profondeur permet de définir un cas d'arrêt -> si elle est égale à 0, on évalue directement le noeud, qui sera une feuille
** l'entier IA vaut soit 0, soit 1, et permet de savoir si on veut maximiser le score (étage représentant un tour de l'IA) ou le minimiser (représentant un tour du joueur)
**/
Arbre* minmax(Partie* partie, int profondeur, int IA);
/**
** Destruction propre de l'arbre de décision (la RAM de votre PC vous dit merci)
**/
void detruireArbre(Arbre* arbre);