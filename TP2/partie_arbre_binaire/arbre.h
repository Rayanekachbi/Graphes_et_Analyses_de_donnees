#ifndef ARBRE_H
#define ARBRE_H

#include <stdio.h>
#include <stdlib.h>

// Définition de la structure du noeud
typedef struct Noeud {
    char val; // Valeur du noeud (un caractère)
    struct Noeud* gauche; // Pointeur vers le fils gauche
    struct Noeud* droit;  // Pointeur vers le fils droit
} Noeud;

// Crée un nouveau noeud (une feuille).
Noeud* creerNoeud(char val);

// Libère récursivement toute la mémoire de l'arbre.
// (Utilise un parcours postfixe)
void libererArbre(Noeud* racine);

// Crée un arbre binaire "synthétique" (ad-hoc) pour les tests.
Noeud* creerArbreSynthetique();

// Affiche l'arbre en parcours Préfixe (Racine -> Gauche -> Droit).
void parcoursPrefixe(Noeud* racine);

// Affiche l'arbre en parcours Infixe (Gauche -> Racine -> Droit).
void parcoursInfixe(Noeud* racine);

// Affiche l'arbre en parcours Postfixe (Gauche -> Droit -> Racine).
void parcoursPostfixe(Noeud* racine);

#endif // ARBRE_H