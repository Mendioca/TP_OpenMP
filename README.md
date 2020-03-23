# TP Parallélisation OpenMP

## Introduction

Ce [dépôt git](https://github.com/PereWoulpy/TP_OpenMP.git) contient les deux TP de parallélisation en utilisant OpenMP. Le but était d'implémenter des algorithmes parallèles pour faire des traitements sur des vecteurs, des matrices de nombres flotants (TP1) et également sur des matrices de charatcères (TP2)
Après avoir réalisé ces implémentations, l'exercice était de lancer des tests de performance en modifant les paramètres d'exécution.

## Les Sources

Le fichier [Algorithms.cpp](./src/Algorithms.cpp) contient les implémentations des différents algorithmes demandés. Ils sont séparés par différents _namespace_ c++.

Les fichiers _main_, [numberVector.cpp](./src/numberVector.cpp), [numberMatrix.cpp](./src/numberMatrix.cpp) et [charMatrix.cpp](./src/charMatrix.cpp) contiennent le code pour mesurer les performances des algorithmes pour une taille de donnée fixe, et un nombre de threads _OpenMP_ fixe.

Enfin le fichier [data\_collection.py](./data_collection) est un script python3 qui permet de lancer ces différents exécutable pour tout un set de paramètres.

## Build & Run

Pour compiler le projet, voici les commandes à faire :

```
mkdir build
cd build
cmake ..
make
```

3 executables sont alors compilée : `exec_char`, `exec_numb`, `exec_vect`

Pour lancer un run et obtenir des mesures de performance (depuis la racine du dépôt) :

```
python3 data_collection exec_xxxx max_threads(INT) max_size(INT)
```

## Résultats

Ces runs ont été réalisés sur mon ordinateur personnel disposant d'un processeur Intel Core i7 - 4702MQ avec 4 coeurs et une fréquence de 2.2GHz, et de 8GB de RAM DDR3. Ils ont aussi été réalisés sur une machine de Grid5000, un _dahu_, avec 2 Intel Xeon Gold 6130 pour un total de 32 coeurs et 192GiB de RAM. Tous ces résultats sont rassemblés dans le dossier [results](./results).

## Auteur

* Laurent Turpin, élève en 5ième au département Informatique de l'INSA de Lyon.
