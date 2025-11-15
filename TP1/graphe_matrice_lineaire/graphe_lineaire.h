#ifndef GRAPHE_LINEAIRE_H
#define GRAPHE_LINEAIRE_H

#include <stdio.h>
#include <stdlib.h>

// La structure Graphe utilise maintenant un simple pointeur 'int*'
typedef struct {
    int nb_sommets; // Nombre de sommets (N)
    int *adjacence;   // La matrice d'adjacence linéarisée (taille N*N)
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

#endif // GRAPHE_LINEAIRE_H