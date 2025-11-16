Projet Algorithmique et Structures de Données (L3)
Ce projet, réalisé dans le cadre de l'unité d'enseignement "Algorithmique et Structures de Données" (A.A L3), retrace l'implémentation et l'analyse de diverses structures de données et algorithmes.

Le projet est divisé en quatre parties (TP0 à TP3), progressant de structures fondamentales (listes, arbres) vers des implémentations de graphes et l'analyse de performance. L'un des objectifs centraux est l'implémentation et l'étude de l'algorithme de coloration de Welsh-Powell.

Auteur : Rayane KACHBI

Contenu du Projet
Ce dépôt contient les implémentations et analyses suivantes :

TP0 : Fondations sur les listes doublement chaînées et réflexion sur leur extension vers les arbres n-aires et les graphes.

TP1 : Implémentation de graphes avec des matrices d'adjacence (standard int** et linéarisée int*) et première implémentation de l'algorithme de Welsh-Powell.

TP2 : Application de Welsh-Powell à un cas concret (carte de l'Europe) avec chargement depuis un fichier. Implémentation des parcours d'arbres binaires (Préfixe, Infixe, Postfixe).

TP3 : Implémentation de structures avancées (arbre n-aire, graphe par listes d'adjacence), correction de codes de coloration et analyse de performance expérimentale de l'algorithme Welsh-Powell.

Structure des Dossiers
L'arborescence du projet est organisée par TP :

TP0/ : Listes doublement chaînées.

TP1/ : Graphes (matrices standard et linéarisées).

TP2/ : Applications (graphe carte d'Europe et parcours d'arbres binaires).

TP3/ : Structures avancées, correction de code et analyse de performance.

Compte Rendu Global des TP.pdf : Le rapport détaillé du projet.

Compilation et Exécution
Chaque TP contient ses propres instructions de compilation et d'exécution.

TP0 : Listes Doublement Chaînées
Instructions pour compiler et exécuter le test des listes.

Bash

# Se placer dans le dossier
cd TP0

# Compiler le programme
gcc -o exeTp0 maListe.c liste.c -Wall

# Exécuter le programme
./exeTp0
TP1 : Graphes (Implémentations Matricielles)
Ce TP explore deux implémentations de la matrice d'adjacence.

1. Graphe Matrice Standard (N x N)

Bash

# Se placer dans le dossier
cd TP1/graphe_matrice_standard

# Compiler
gcc -o coloration_standard main_graphe.c graphe.c -Wall

# Exécuter
./coloration_standard
2. Graphe Matrice Linéarisée (N * 1)

Bash

# Se placer dans le dossier
cd TP1/graphe_matrice_lineaire

# Compiler
gcc -o coloration_lineaire main_graphe_lineaire.c graphe_lineaire.c -Wall

# Exécuter
./coloration_lineaire
TP2 : Applications (Graphes et Arbres)
1. Partie Graphe (Welsh-Powell sur la carte d'Europe)

Cette partie applique l'algorithme à la carte d'Europe chargée depuis carte_europe.txt.

Bash

# Se placer dans le bon dossier
cd TP2/partie_graphe_welsh_powell

# Compiler le programme
gcc -o coloration_tp2 main_graphe.c graphe.c -Wall

# Exécuter
./coloration_tp2
2. Partie Arbre Binaire (Parcours)

Cette partie teste les parcours Préfixe, Infixe et Postfixe.

Bash

# Se placer dans le bon dossier
cd TP2/partie_arbre_binaire

# Compiler le programme
gcc -o parcours_arbre main_arbre.c arbre.c -Wall

# Exécuter
./parcours_arbre
TP3 : Structures Avancées, Analyse et Visualisation
Ce TP contient plusieurs projets indépendants en C et en Python.

1. Arbre N-aire (Fils Gauche, Frère Droit) [C]

Bash

# Se placer dans le dossier
cd TP3/1_arbre_n_aire

# Compiler
gcc -o test_arbre_n_aire main_arbre_n_aire.c arbre_n_aire.c -Wall

# Exécuter
./test_arbre_n_aire
2. Graphe par Listes d'Adjacence [C]

Bash

# Se placer dans le dossier
cd TP3/2_graphe_liste_adjacence

# Compiler
gcc -o graphe_liste main_graphe_liste.c graphe_liste.c -Wall

# Exécuter
./graphe_liste
3. Correction Welsh-Powell [C]

Bash

# Se placer dans le dossier
cd TP3/3_correction_welsh_powell

# Compiler
gcc -o welsh_powell_corrige chatgpt_corrige.c -Wall

# Exécuter
./welsh_powell_corrige
4. Analyse de Performance [C]

Bash

# Se placer dans le dossier
cd TP3/4_analyse_performance

# Compiler avec optimisation
gcc -o perf main_performance.c graphe.c -Wall -O2

# Exécuter et rediriger la sortie
./perf > resultats_performance.csv
5. Visualisation [Python] Cette partie nécessite un environnement Python et les bibliothèques networkx et matplotlib.

Bash

# Se placer dans le dossier
cd TP3/5_visualisation_python

# Créer un environnement virtuel
python -m venv venv
source venv/bin/activate  # (ou .\venv\bin\activate sur Windows)

# Installer les librairies
pip install networkx matplotlib

# Exécuter les scripts (au choix)
python visualiser_carte.py
python coloration_corrigee.py
python coloration_carte.py