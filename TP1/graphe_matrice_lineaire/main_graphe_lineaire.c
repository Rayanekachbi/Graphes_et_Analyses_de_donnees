#include "graphe_lineaire.h"
#include <stdio.h>

int main() {
    // Créer un graphe simple
    int N = 5;
    Graphe* g = creer_graphe(N);

    printf("--- Creation d'un graphe a %d sommets ---\n", N);

    // Ajouter des arêtes (Exemple: un cycle à 5 sommets)
    // 0 -- 1 -- 2
    // |    |    |  (3-2)
    // 4 -- 3 --/
    // (et 1-3)
    
    ajouter_arete(g, 0, 1);
    ajouter_arete(g, 1, 2);
    ajouter_arete(g, 2, 3);
    ajouter_arete(g, 3, 4);
    ajouter_arete(g, 4, 0); // Le cycle
    ajouter_arete(g, 1, 3); 

    // Afficher la matrice pour vérifier
    afficher_matrice(g);

    // Lancer l'algorithme de Welsh-Powell
    int* couleurs = coloration_welsh_powell(g);

    // Afficher le résultat
    printf("\n--- Resultat de la coloration ---\n");
    for (int i = 0; i < N; i++) {
        printf("Sommet %d -> Couleur %d\n", i, couleurs[i]);
    }

    // Nettoyage
    liberer_graphe(g);
    free(couleurs);
    
    printf("\n--- Test TP1 termine ---\n");

    return 0;
}