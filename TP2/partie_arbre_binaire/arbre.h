// Fichier : TP2/arbre.h

#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure du nœud,
// basée sur "Listing 1" de votre TP0.pdf
typedef struct Noeud {
    char val; // Valeur du nœud (un caractère)
    struct Noeud* gauche; // Pointeur vers le fils gauche
    struct Noeud* droit;  // Pointeur vers le fils droit
} Noeud;

/**
 * @brief Crée un nouveau nœud (une feuille).
 * @param val La valeur (char) à stocker dans le nœud.
 * @return Un pointeur vers le nouveau nœud alloué.
 */
Noeud* creerNoeud(char val);

/**
 * @brief Libère récursivement toute la mémoire de l'arbre.
 * (Utilise un parcours postfixe)
 */
void libererArbre(Noeud* racine);

/**
 * @brief Crée un arbre binaire "synthétique" (ad-hoc) pour les tests.
 * @return Un pointeur vers la racine de l'arbre créé.
 */
Noeud* creerArbreSynthetique();

/**
 * @brief Affiche l'arbre en parcours Préfixe (Racine -> Gauche -> Droit).
 */
void parcoursPrefixe(Noeud* racine);

/**
 * @brief Affiche l'arbre en parcours Infixe (Gauche -> Racine -> Droit).
 */
void parcoursInfixe(Noeud* racine);

/**
 * @brief Affiche l'arbre en parcours Postfixe (Gauche -> Droit -> Racine).
 */
void parcoursPostfixe(Noeud* racine);

#endif // ARBRE_H