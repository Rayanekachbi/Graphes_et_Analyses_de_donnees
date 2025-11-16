# Projet Algorithmique et Structures de Données (L3)

Ce projet, réalisé dans le cadre de l'unité d'enseignement **Algorithmique et Structures de Données** (A.A L3), présente l'implémentation et l’analyse de plusieurs structures de données et algorithmes fondamentaux.

Il est structuré en quatre parties (TP0 à TP3), allant des structures de base (listes, arbres) jusqu’aux représentations avancées de graphes et à l’analyse de performance. Un objectif majeur du projet est l’étude et l’implémentation de l’algorithme de coloration **Welsh-Powell**.

**Auteur : Rayane KACHBI**



## Contenu du Projet

Le dépôt inclut les implémentations et analyses suivantes :

* **TP0** : Listes doublement chaînées et réflexion sur leur extension vers les arbres n-aires et les graphes.
* **TP1** : Implémentation de graphes en matrice d'adjacence (matrice standard `int**` et version linéarisée `int*`). Première implémentation de Welsh-Powell.
* **TP2** : Application de Welsh-Powell à un cas réel (carte de l’Europe) avec chargement depuis fichier. Implémentation des parcours d’arbres binaires (Préfixe, Infixe, Postfixe).
* **TP3** : Implémentation d’un arbre n-aire, d’un graphe par listes d’adjacence, correction de code de coloration, et analyse expérimentale des performances de Welsh-Powell.



## Structure des Dossiers

L’arborescence est organisée par travaux pratiques :

* `TP0/` : Listes doublement chaînées
* `TP1/` : Graphes matriciels (standard et linéarisés)
* `TP2/` : Applications (coloration de carte et parcours d’arbres binaires)
* `TP3/` : Structures avancées, correction de code et analyse de performance
* `Compte Rendu Global des TP.pdf` : Rapport détaillé du projet



## Compilation et Exécution

Chaque TP possède ses propres instructions de compilation.



### TP0 : Listes Doublement Chaînées

```bash
# Se placer dans le dossier
cd TP0

# Compiler
gcc -o exeTp0 maListe.c liste.c -Wall

# Exécuter
./exeTp0
```



### TP1 : Graphes (Implémentations Matricielles)

#### 1. Graphe Matrice Standard (N x N)

```bash
cd TP1/graphe_matrice_standard
gcc -o coloration_standard main_graphe.c graphe.c -Wall
./coloration_standard
```

#### 2. Graphe Matrice Linéarisée (N * 1)

```bash
cd TP1/graphe_matrice_lineaire
gcc -o coloration_lineaire main_graphe_lineaire.c graphe_lineaire.c -Wall
./coloration_lineaire
```



### TP2 : Applications (Graphes et Arbres)

#### 1. Partie Graphe (Welsh-Powell sur la carte d’Europe)

```bash
cd TP2/partie_graphe_welsh_powell
gcc -o coloration_tp2 main_graphe.c graphe.c -Wall
./coloration_tp2
```

#### 2. Partie Arbre Binaire (Parcours Préfixe, Infixe, Postfixe)

```bash
cd TP2/partie_arbre_binaire
gcc -o parcours_arbre main_arbre.c arbre.c -Wall
./parcours_arbre
```



### TP3 : Structures Avancées, Analyse et Visualisation

#### 1. Arbre N-aire (Fils Gauche, Frère Droit)

```bash
cd TP3/1_arbre_n_aire
gcc -o test_arbre_n_aire main_arbre_n_aire.c arbre_n_aire.c -Wall
./test_arbre_n_aire
```

#### 2. Graphe par Listes d’Adjacence

```bash
cd TP3/2_graphe_liste_adjacence
gcc -o graphe_liste main_graphe_liste.c graphe_liste.c -Wall
./graphe_liste
```

#### 3. Correction de l’Algorithme Welsh-Powell

```bash
cd TP3/3_correction_welsh_powell
gcc -o welsh_powell_corrige chatgpt_corrige.c -Wall
./welsh_powell_corrige
```

#### 4. Analyse de Performance

```bash
cd TP3/4_analyse_performance
gcc -o perf main_performance.c graphe.c -Wall -O2
./perf > resultats_performance.csv
```

#### 5. Visualisation (Python)

Requiert Python, `networkx` et `matplotlib`.

```bash
cd TP3/5_visualisation_python

python -m venv venv
source venv/bin/activate      # sous Windows : .\venv\Scripts\activate

pip install networkx matplotlib

python visualiser_carte.py
python coloration_corrigee.py
python coloration_carte.py
```

