#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>

// Structure principale pour le graphe
typedef struct {
    int nb_sommets; // Nombre de sommets (N)
    int **adjacence;  // La matrice d'adjacence (N x N)
} Graphe;

// Alloue la mémoire pour un nouveau graphe (structure + matrice N*N).
Graphe* creer_graphe(int nb_sommets);

// Libère toute la mémoire allouée pour le graphe.
void liberer_graphe(Graphe* g);

// Ajoute une arête non-orientée entre deux sommets.
void ajouter_arete(Graphe* g, int v1, int v2);

// Affiche la matrice d'adjacence du graphe.
void afficher_matrice(Graphe* g);

// Calcule la coloration du graphe en utilisant l'algorithme de Welsh-Powell.
int* coloration_welsh_powell(Graphe* g);

// NOUVELLES FONCTIONS TP2

// Charge un graphe depuis un fichier texte (ou stdin).
// La première ligne du fichier doit contenir le nombre de sommets.
// Les lignes suivantes contiennent la matrice d'adjacence (N lignes de N entiers).
Graphe* chargeGraphe(const char* nom_fichier);

// Affiche l'ordre de marquage (le tri des sommets par degré) 
// et le résultat de la coloration.
void afficher_ordre_marquage_et_resultat(Graphe* g, int* couleurs, const char** noms_sommets);

#endif // GRAPHE_H