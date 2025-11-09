# TP2 - Applications (Graphes et Arbres)

Ce TP est divisé en deux parties indépendantes.

## 1. Partie Graphe (Welsh-Powell sur la carte d'Europe)

Cette partie applique l'algorithme Welsh-Powell à une carte de l'Europe chargée depuis un fichier.

# Se placer dans le bon dossier
cd partie_graphe_welsh_powell

# Compiler le programme
gcc -o coloration_tp2 main_graphe.c graphe.c -Wall

# Exécuter
./coloration_tp2

## 2. Partie Arbre Binaire (Parcours)

Cette partie implémente les parcours d'arbres binaires (Préfixe, Infixe, Postfixe).

# Se placer dans le bon dossier
cd partie_arbre_binaire

# Compiler le programme
gcc -o parcours_arbre main_arbre.c arbre.c -Wall

# Exécuter
./parcours_arbre