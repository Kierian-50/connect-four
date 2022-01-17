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

#### Librairie utilisé

- SDL2

#### Environnement de développement

- Nous avons développé sur l'IDE CLion.

#### Lien du dépot github

- https://github.com/Kierian-50/connect-four

## Dans quel contexte avons-nous réalisé ce projet ?

Nous avons réalisé ce projet durant nos études à l'ESIEA, dans le cadre d'un test de compétences en 
développement, en bac +3.

## Le but du projet

Le but de base du projet est la réalisation en C d’un jeu de Puissance 4. Pour rappel, le jeu
de Puissance 4 se joue dans une grille verticale de 6 lignes par 7 colonnes, dans laquelle
deux joueurs s’affrontent. À chaque tour, un des deux joueurs choisit une colonne où
placer un pion, dans laquelle celui-ci va glisser par gravité. La partie s’arrête lorsque (1)
un des joueurs a réussi à aligner au moins 4 pions (horizontalement, verticalement ou en
diagonale, comme pour le jeu de morpion) ou (2) si la grille est pleine (dans ce cas, on a
une égalité).

Pour aller plus loin, nous avons pour objectif de développer un mode de jeu un joueur physique contre un autre joueur
physique et un autre mode de jeu ou un joueur physique affronte une intelligence artificielle. Cette intelligence 
articielle comprendra deux niveaux de difficultés : 
- Un niveau basique : L'IA place son pion là où il y a le plus de possibilités d'aligner quatre pions, mais elle 
  placera tout de même en priorité son pion pour aligner quatre pions ou pour empêcher que l'adversaire d'en aligner 
  quatre.
  
- Un niveau plus complexe : Implementation de l'algorithme minmax.

Enfin, le dernier objectif était de développer une interface graphique à l'aide de la librairie SDL2 qui était
imposé et que nous ne connaissions pas.

## La progression du projet

Nous avons rapidement implémenté le moteur de jeu, donc il est possible de réaliser des parties à deux personnes en
mode graphique, ce fût notre première réalisation. Ensuite, nous avons implémenté l'IA basique que nous avons ajouté
à la boucle de jeu, ce qui fait qu'il est possible de jouer en mode console contre l'IA basique.

Nous avons par la suite ajouté le mode graphique en utilisant la librairie SDL, donc il est possible de jouer en mode 
graphique contre l'IA ou contre une personne. Nous sommes allés plus loin avec cette librairie, puisque nous nous sommes 
amusés à rajouter une musique d'ambiance réalisée par Matéo. Nous avons aussi ajouté des bruitages en cas de victoire ou 
de défaite. Les musiques sont gérées via des threads afin de ne pas bloquer la boucle de jeu.

Concernant l'intelligence artificielle qui implémente l'algorithme minmax, nous avons implémenté l'algorithme et l'avons
testé unitairement avec de bons résultats, mais nous n'avons pas eu le temps de gérer des bugs dans la boucle de jeu.
Nous avons retiré cette fonctionnalité de la boucle de jeu pour éviter que l'utilisateur l'utilise et ne comprenne pas
que le jeu crash. Il semblerait que le problème vienne d'un problème de mémoire, mais nous n'avons pas eu le temps de 
comprendre d'où venait l'erreur, d'autant plus que durant les tests unitaires nous n'avons pas eu de bug, mieux les 
résultats étaient bons.

Comme vous pouvez le voir dans le code source, nous avons tenu à tester unitairement toutes les méthodes afin de 
vérifier le bon comportement de la méthode dans différents cas normaux, limites et d'erreurs. Une méthode *TestJeu*
contient toutes les méthodes de test.

## Les installations requises pour faire fonctionner le logiciel

Il est absolument nécessaire d'avoir installé SDL2 pour pouvoir faire fonctionner le logiciel, en faisant par exemple
sur Ubuntu :

```bash
apt-get install libsdl2-dev
```

Il faut que la librairie soit accessible en faisant :

```C
#include <SDL.h>
```

ou

```C
#include <SDL2/SDL.h>
```

## Installation et fonctionnement

>**Le logiciel fonctionne uniquement sur Linux**.

Une fois que vous êtes dans un environnement linux et que SDL est installé comme expliqué un peu plus haut, vous 
serez en mesure de lancer le logiciel <ins>**en ajoutant le flag "-pthread" lors de la compilation afin de pouvoir 
utiliser les threads.**</ins>

Vous pourrez trouver ci-dessous un exemple de cmake :

```cmake
cmake_minimum_required(VERSION 3.21)
project(connect_four C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2 -pthread")

find_package(SDL2 REQUIRED)

include_directories(Basecode)

add_executable(connect_four
        Basecode/IA.c
        Basecode/IA.h
        Basecode/Jeu.c
        Basecode/Jeu.h
        Basecode/main.c
        Basecode/TestJeu.c
        Basecode/TestJeu.h
        Basecode/Sound.c
        Basecode/Sound.h)

target_link_libraries(connect_four SDL2::SDL2)
```

>**N'hésitez pas à mettre le son durant l'utilisation du logiciel afin de profiter de la musique d'ambiance et 
> des bruitages**.

>**Lancement des tests**.

Pour lancer les tests unitaires, il suffit de décommenter les lignes qui se trouvent dans le main et executer. Dans la
console, vous pourrez visualiser le résultat des tests.
