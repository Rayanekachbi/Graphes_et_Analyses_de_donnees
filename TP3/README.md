# TP3 - Instructions de Compilation

Ce dossier contient plusieurs programmes indépendants pour les différentes parties du TP3.

## 1. Correction du code C de Welsh-Powell

Cette partie concerne le code `chatgpt_corrige.c` qui corrige les problèmes d'initialisation et d'algorithme du code C fourni.

```bash
# Compiler le programme
gcc -o welsh_powell_corrige chatgpt_corrige.c -Wall -Wextra

# Exécuter le programme
./welsh_powell_corrige

# Compiler le programme de test de l'arbre
gcc -o test_arbre_n_aire main_arbre_n_aire.c arbre_n_aire.c -Wall -Wextra

# Exécuter le test
./test_arbre_n_aire

# Compiler le programme
gcc -o graphe_liste main_graphe_liste.c graphe_liste.c -Wall -Wextra

# Exécuter
./graphe_liste

# Compiler avec optimisation (-O2) pour des mesures de temps fiables
gcc -o perf main_performance.c graphe.c -Wall -O2

# Exécuter et rediriger la sortie vers un fichier CSV
./perf > resultats.csv

# Vous pouvez ensuite ouvrir resultats.csv dans un tableur
# pour générer la courbe (Temps en Y, N en X log)

## Partie 5 : Visualisation et Coloration (Python)

Assurez-vous d'avoir Python et `pip` installés.

### 1. Installation des librairies

```bash
pip install networkx matplotlib

Ce script dessine le graphe des 11 pays.
python visualiser_carte.py

Ce script corrige l'algorithme de Welsh-Powell défaillant et l'applique à un graphe d'exemple, puis le dessine.
python coloration_corrigee.py