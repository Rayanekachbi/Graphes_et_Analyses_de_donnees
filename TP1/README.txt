# TP1 - Graphes (Implémentations Matricielles)

Ce TP explore deux façons d'implémenter un graphe avec une matrice d'adjacence.
Chaque implémentation est dans son propre dossier.

## 1. Graphe Matrice Standard (N x N)

Compilez et exécutez le code en vous plaçant dans le dossier concerné :

cd graphe_matrice_standard
gcc -o coloration_standard main_graphe.c graphe.c -Wall
./coloration_standard

## 2. Graphe Matrice Linéarisée (N * 1)

Compilez et exécutez le code en vous plaçant dans le dossier concerné :

cd graphe_matrice_lineaire
gcc -o coloration_lineaire main_graphe_lineaire.c graphe_lineaire.c -Wall
./coloration_lineaire