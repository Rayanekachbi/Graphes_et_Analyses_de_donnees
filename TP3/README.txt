# TP3 - Structures Avancées, Analyse et Visualisation

Ce TP contient plusieurs projets indépendants en C et en Python.

## 1. Arbre N-aire (Fils Gauche, Frère Droit) [C]

# Se placer dans le dossier
cd 1_arbre_n_aire

# Compiler
gcc -o test_arbre_n_aire main_arbre_n_aire.c arbre_n_aire.c -Wall

# Exécuter
./test_arbre_n_aire

## 2. Graphe par Listes d'Adjacence [C]

# Se placer dans le dossier
cd 2_graphe_liste_adjacence

# Compiler
gcc -o graphe_liste main_graphe_liste.c graphe_liste.c -Wall

# Exécuter
./graphe_liste

## 3. Correction Welsh-Powell [C]

# Se placer dans le dossier
cd 3_correction_welsh_powell

# Compiler
gcc -o welsh_powell_corrige chatgpt_corrige.c -Wall

# Exécuter
./welsh_powell_corrige

## 4. Analyse de Performance [C]

# Se placer dans le dossier
cd 4_analyse_performance

# Compiler avec optimisation
gcc -o perf main_performance.c graphe.c -Wall -O2

# Exécuter et rediriger la sortie
./perf > resultats_performance.csv

## 5. Visualisation [Python]

# Se placer dans le dossier
cd 5_visualisation_python

# Créer un environnement virtuel
python -m venv venv
source venv/bin/activate  (ou .\venv\bin\activate sur Windows)

# Installer les librairies
pip install networkx matplotlib

# Exécuter les scripts (au choix)
python visualiser_carte.py
python coloration_corrigee.py
python coloration_carte.py