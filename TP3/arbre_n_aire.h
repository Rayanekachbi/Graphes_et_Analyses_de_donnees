#ifndef ARBRE_N_AIRE_H
#define ARBRE_N_AIRE_H

#include <stdio.h>
#include <stdlib.h>

// Structure "Fils Gauche, Frere Droit" (TP0.pdf)
typedef struct NoeudNAire {
    char val;
    struct NoeudNAire* premierEnfant;
    struct NoeudNAire* frereSuivant;
} NoeudNAire;

NoeudNAire* creerNoeudNAire(char val);
void libererArbreNAire(NoeudNAire* racine);

// Ajoute un enfant à un noeud parent
void ajouterEnfant(NoeudNAire* parent, NoeudNAire* enfant);

// Affiche l'arbre (parcours n-aire préfixe)
void afficherArbreNAire(NoeudNAire* racine, int profondeur);

#endif