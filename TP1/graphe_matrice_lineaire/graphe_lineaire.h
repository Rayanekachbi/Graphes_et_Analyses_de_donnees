#ifndef GRAPHE_LINEAIRE_H
#define GRAPHE_LINEAIRE_H

#include <stdio.h>
#include <stdlib.h>

// --- MODIFIÉ ---
// La structure Graphe utilise maintenant un simple pointeur 'int*'
typedef struct {
    int nb_sommets; // Nombre de sommets (N)
    int *adjacence;   // La matrice d'adjacence linéarisée (taille N*N)
} Graphe;

/**
 * @brief Alloue la mémoire pour un nouveau graphe (structure + matrice N*N).
 * @param nb_sommets Le nombre de sommets du graphe.
 * @return Un pointeur vers le graphe initialisé (matrice mise à 0).
 */
Graphe* creer_graphe(int nb_sommets);

/**
 * @brief Libère toute la mémoire allouée pour le graphe.
 */
void liberer_graphe(Graphe* g);

/**
 * @brief Ajoute une arête non-orientée entre deux sommets.
 */
void ajouter_arete(Graphe* g, int v1, int v2);

/**
 * @brief Affiche la matrice d'adjacence du graphe.
 */
void afficher_matrice(Graphe* g);

/**
 * @brief Calcule la coloration du graphe en utilisant l'algorithme de Welsh-Powell.
 * @return Un tableau d'entiers (taille nb_sommets) où tab[i] 
 * est la couleur du sommet i.
 */
int* coloration_welsh_powell(Graphe* g);

#endif // GRAPHE_LINEAIRE_H