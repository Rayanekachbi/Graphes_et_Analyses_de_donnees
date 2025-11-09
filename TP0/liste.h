#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Définition des Structures ---

typedef struct{
    int x;
    int y;
} point;

// Déclaration anticipée pour que 'cellule' puisse s'auto-référencer
typedef struct cellule cellule;

struct cellule{
    point p;
    cellule *precedent;
    cellule *suivant;
};


// --- Prototypes des Fonctions ---

/**
 * @brief Alloue l'espace mémoire pour une cellule, remplit les 
 * champs de la structure cellule et retourne un pointeur sur cette cellule.
 */
cellule *NouvCel (point p);

/**
 * @brief Permet d'insérer la cellule cel après la place pl dans la liste liste.
 */
void InsererCellule(int pl, cellule *cel, cellule *liste);

/**
 * @brief Permet de supprimer la cellule à la position pl dans la liste.
 * @param liste Un pointeur vers le pointeur de tête de liste.
 */
void SupprimeCellule(int pl, cellule **liste);

/**
 * @brief Affiche la liste liste.
 */
void Afficher(cellule *liste);

#endif // LISTE_H