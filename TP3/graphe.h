// Fichier : TP2/graphe.h
// ASSUREZ-VOUS QUE CE CONTENU EST BIEN CELUI DE VOTRE FICHIER

#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdio.h>
#include <stdlib.h>

// Structure principale pour notre graphe
typedef struct {
    int nb_sommets; // Nombre de sommets (N)
    int **adjacence;  // La matrice d'adjacence (N x N)
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

// --- NOUVELLES FONCTIONS TP2 (CE SONT LES LIGNES MANQUANTES) ---

/**
 * @brief Charge un graphe depuis un fichier texte (ou stdin).
 * La première ligne du fichier doit contenir le nombre de sommets.
 * Les lignes suivantes contiennent la matrice d'adjacence (N lignes de N entiers).
 * @param nom_fichier Le nom du fichier. Si NULL, lit depuis stdin.
 * @return Un pointeur vers le graphe chargé.
 */
Graphe* chargeGraphe(const char* nom_fichier);

/**
 * @brief Affiche l'ordre de marquage (le tri des sommets par degré) 
 * et le résultat de la coloration.
 * @param g Le graphe.
 * @param couleurs Le tableau de couleurs retourné par Welsh-Powell.
 * @param noms_sommets Un tableau de chaînes de caractères pour les noms (ex: "France").
 * Si NULL, affiche seulement les ID.
 */
void afficher_ordre_marquage_et_resultat(Graphe* g, int* couleurs, const char** noms_sommets);

#endif // GRAPHE_H