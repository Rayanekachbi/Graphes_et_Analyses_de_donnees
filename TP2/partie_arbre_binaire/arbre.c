#include "arbre.h"

// Crée un nouveau noeud 
Noeud* creerNoeud(char val) {
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        perror("Erreur d'allocation pour le noeud");
        exit(1);
    }
    nouveau->val = val;
    nouveau->gauche = NULL;
    nouveau->droit = NULL;
    return nouveau;
}

// Libère récursivement toute la mémoire de l'arbre (parcours postfixe)
void libererArbre(Noeud* racine) {
    if (racine == NULL) {
        return; // Cas de base
    }
    // On libère d'abord les enfants
    libererArbre(racine->gauche);
    libererArbre(racine->droit);
    // Puis on se libère soi-même
    free(racine);
}

// Crée un arbre "ad hoc" pour les tests
// Arbre créé :
//         A
/*       /   \ */
//      B     C
//     / \   /
//    D   E F
Noeud* creerArbreSynthetique() {
    Noeud* racine = creerNoeud('A');
    
    racine->gauche = creerNoeud('B');
    racine->droit = creerNoeud('C');
    
    racine->gauche->gauche = creerNoeud('D');
    racine->gauche->droit = creerNoeud('E');
    
    racine->droit->gauche = creerNoeud('F');
    // racine->droit->droit reste NULL
    
    return racine;
}


// Implémentation des Parcours

// Parcours Préfixe : Racine, Gauche, Droit (RGD)
void parcoursPrefixe(Noeud* racine) {
    // Cas de base de la récursion
    if (racine == NULL) {
        return;
    }
    
    // Visiter la Racine
    printf("%c ", racine->val);
    
    // Visiter le sous-arbre Gauche
    parcoursPrefixe(racine->gauche);
    
    // Visiter le sous-arbre Droit
    parcoursPrefixe(racine->droit);
}

// Parcours Infixe : Gauche, Racine, Droit (GRD)
void parcoursInfixe(Noeud* racine) {
    // Cas de base de la récursion
    if (racine == NULL) {
        return;
    }
    
    // Visiter le sous-arbre Gauche
    parcoursInfixe(racine->gauche);
    
    // Visiter la Racine
    printf("%c ", racine->val);
    
    // Visiter le sous-arbre Droit
    parcoursInfixe(racine->droit);
}

// Parcours Postfixe : Gauche, Droit, Racine (GDR)
void parcoursPostfixe(Noeud* racine) {
    // Cas de base de la récursion
    if (racine == NULL) {
        return;
    }
    
    // Visiter le sous-arbre Gauche
    parcoursPostfixe(racine->gauche);
    
    // Visiter le sous-arbre Droit
    parcoursPostfixe(racine->droit);
    
    // Visiter la Racine
    printf("%c ", racine->val);
}