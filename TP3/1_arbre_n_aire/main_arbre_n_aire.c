#include "arbre_n_aire.h"
#include <stdio.h>

/*
 * Arbre créé :
 * A
 * /|\
 * B C D
 * / \  |
 * E   F G
 */
NoeudNAire* creerArbreNAireSynthetique() {
    // Niveau 0
    NoeudNAire* racine = creerNoeudNAire('A');

    // Niveau 1 (Enfants de A)
    NoeudNAire* nB = creerNoeudNAire('B');
    NoeudNAire* nC = creerNoeudNAire('C');
    NoeudNAire* nD = creerNoeudNAire('D');
    
    ajouterEnfant(racine, nB); // A -> B
    ajouterEnfant(racine, nC); // A -> B -> C (frère)
    ajouterEnfant(racine, nD); // A -> B -> C -> D (frère)

    // Niveau 2 (Enfants de B et D)
    NoeudNAire* nE = creerNoeudNAire('E');
    NoeudNAire* nF = creerNoeudNAire('F');
    NoeudNAire* nG = creerNoeudNAire('G');

    ajouterEnfant(nB, nE); // B -> E
    ajouterEnfant(nB, nF); // B -> E -> F (frère)
    
    ajouterEnfant(nD, nG); // D -> G

    return racine;
}

int main() {
    printf("--- Lancement Test TP3 - Arbre N-aire ---\n");

    // Création de l'arbre
    NoeudNAire* monArbre = creerArbreNAireSynthetique();
    
    printf("Arbre n-aire synthetique cree.\n");
    printf("Structure attendue :\n");
    printf("- A\n");
    printf("  - B\n");
    printf("    - E\n");
    printf("    - F\n");
    printf("  - C\n");
    printf("  - D\n");
    printf("    - G\n");

    // Affichage
    printf("\nAffichage de l'arbre (parcours prefixe modifie) :\n");
    afficherArbreNAire(monArbre, 0);

    // Libération de la mémoire
    printf("\nLiberation de l'arbre...\n");
    libererArbreNAire(monArbre);
    printf("Arbre libere.\n");

    printf("\n--- Fin Test TP3 - Arbre N-aire ---\n");
    return 0;
}