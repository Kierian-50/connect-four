Jeu de puissance 4
==

**Version 1.0.0**


## Contributeurs

- Kierian Tirlemont <tirlemont@et.esiea.fr>
- Matéo Castella <castella@et.esiea.fr> 

## Date

- Janvier 2022

## Langage utilisé

- C

#### Librairies utilisés

- SDL2

#### Environnement de développement

- Nous avons développé sur le logiciel CLion.

## Dans quel contexte avons-nous réalisé ce projet ?

Nous avons réalisé ce projet dans le cadre de nos études à l'ESIEA dans le cadre d'un test de compétance en 
développement en bac +3.

## Le but du projet

Le but de base du projet est la réalisation en C d’un jeu de Puissance 4. Pour rappel, le jeu
de Puissance 4 se joue dans une grille verticale de 6 lignes par 7 colonnes, dans laquelle
deux joueurs s’affrontent. A chaque tour, un des deux joueurs choisit une colonne où
placer un pion, dans laquelle celui-ci va glisser par gravité. La partie s’arrête lorsque (1)
un des joueurs a réussi à aligner au moins 4 pions (horizontalement, verticalement ou en
diagonale, comme pour le jeu de morpion) ou (2) si la grille est pleine (dans ce cas, on a
une égalité).

Pour aller plus loin, nous avons pour objectif de développer un mode de jeu un joueur physique contre un autre joueur
physique et un autre mode de jeu ou un joueur physique affronte une intelligence artificielle. Cette intelligence 
articielle comprendra deux niveaux de difficultés : 
- Un niveau basique : L'IA place son pion là où il y a le plus de possibilités d'alligner quatre pions, mais elle 
  placera tout de même en priorité son pion pour aligner quatre pions ou pour empecher que l'adversaire en alligne 
  quatre.
  
- Un niveau plus complexe : Implementation d'un algorithme minmax.

Enfin, le dernière objectif était de développer une interface graphique à l'aide de la librairie SDL2 qui était
imposé et que nous ne connaissions pas.

## La progression du projet

Nous avons rapidement implémenté le moteur de jeu, donc il est possible de réaliser des parties à deux personnes en
mode graphique, ce fût notre première réalisation. Ensuite, nous avons implémenté l'IA basique que nous avons ajouté
à la boucle de jeu, ce qui fait qu'il est possible de jouer en mode console contre l'IA basique. Nous avons par la 
suite ajouté le mode graphique via SDL, donc il est possible de jouer en mode graphique contre l'IA ou contre une 
personne. Nous sommes allés plus loin avec la librairie, puisque nous nous sommes amusés à rajouter une musique 
d'ambience réalisé par Matéo. Nous avons aussi ajouté des bruitages en cas de victoire ou de défaite. 

TODO IA minmax/

## Les installations requises pour faire fonctionner le logiciel

Il est absolument nécessaire d'avoir installer SDL2 pour pouvoir faire fonctionner le logiciel, en faisant par exemple
sur Ubuntu :

```bash
apt-get install libsdl2-dev
```

Il faut que la librairie soit accessible en faisant :

```C
#include <SDL.h>
```

et non 

```C
#include <SDL2/SDL.h>
```

## Installation et fonctionnement

>**Le logiciel fonctionne uniquement sur Linux**.

Une fois que vous êtes dans un environnement linux et que SDL est installé comme expliqué un peu plus haut, vous 
serez en mesure de lancer le logiciel en ajoutant le flag "-pthread" afin de pouvoir utiliser les threads.
