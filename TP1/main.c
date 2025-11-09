#include "graphe.h"
//#include "graphe_lineaire.h" 
// On inclut le nouveau .h

int main() {
    // Exemple de graphe (ex: Graphe "Maison" à 5 sommets)
    int N = 5;
    Graphe* g = creer_graphe(N);

    // Bords du "carré"
    ajouter_arete(g, 0, 1);
    ajouter_arete(g, 1, 2);
    ajouter_arete(g, 2, 3);
    ajouter_arete(g, 3, 0);

    // "Toit" du triangle
    ajouter_arete(g, 0, 4);
    ajouter_arete(g, 1, 4);

    // Affiche la matrice pour vérifier
    afficher_matrice(g);

    // Lancer la coloration
    int* couleurs = coloration_welsh_powell(g);

    // Afficher les résultats
    printf("Resultats de la coloration :\n");
    for (int i = 0; i < N; i++) {
        printf("Sommet %d -> Couleur %d\n", i, couleurs[i]);
    }

    // Nettoyage
    liberer_graphe(g);
    free(couleurs); // Ne pas oublier de libérer le tableau de couleurs

    return 0;
}