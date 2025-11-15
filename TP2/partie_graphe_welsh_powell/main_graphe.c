#include "graphe.h"

// Noms des pays pour l'affichage
// Doit correspondre à l'ordre de la matrice dans carte_europe.txt
const char* NOMS_PAYS[11] = {
    "France (Fr)",      // 0
    "Espagne (Es)",     // 1
    "Portugal (Po)",    // 2
    "Andorre (An)",     // 3
    "Italie (It)",      // 4
    "Autriche (Au)",    // 5
    "Suisse (Su)",      // 6
    "Allemagne (Al)",   // 7
    "Luxembourg (Lu)",  // 8
    "Belgique (Be)",    // 9
    "Pays-Bas (PB)"     // 10
};


int main() {
    printf("--- Lancement Test TP2 - Partie Graphe ---\n");

    // Charger le graphe depuis le fichier
    Graphe* g = chargeGraphe("carte_europe.txt");
    
    if (g == NULL) {
        fprintf(stderr, "Impossible de charger le graphe.\n");
        return 1;
    }

    // Afficher la matrice pour vérifier
    afficher_matrice(g);

    // Lancer la coloration
    int* couleurs = coloration_welsh_powell(g);

    // Afficher les résultats détaillés
    if (g->nb_sommets == 11) {
        afficher_ordre_marquage_et_resultat(g, couleurs, NOMS_PAYS);
    } else {
        // Affichage générique si ce n'est pas le graphe des pays
        afficher_ordre_marquage_et_resultat(g, couleurs, NULL);
    }

    // Nettoyage
    liberer_graphe(g);
    free(couleurs);

    printf("\n--- Test 'chargeGraphe' depuis stdin ---\n");
    printf("Creez un petit graphe (ex: 3 sommets, matrice 3x3)\n");
    Graphe* g_stdin = chargeGraphe(NULL); // NULL pour lire depuis stdin
    
    if (g_stdin) {
        afficher_matrice(g_stdin);
        int* couleurs_stdin = coloration_welsh_powell(g_stdin);
        afficher_ordre_marquage_et_resultat(g_stdin, couleurs_stdin, NULL);
        
        liberer_graphe(g_stdin);
        free(couleurs_stdin);
    }

    printf("\n--- Fin Test TP2 - Partie Graphe ---\n");
    return 0;
}