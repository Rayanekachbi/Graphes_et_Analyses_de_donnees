#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // Pour setlocale
#include "graphe.h" // On réutilise le code du TP2

// Crée un graphe aléatoire de N sommets.
// N: Nombre de sommets.
// densite: Probabilité (entre 0.0 et 1.0) qu'une arête existe.
Graphe* genererGrapheAleatoire(int N, float densite) {
    if (N <= 0) return NULL;
    Graphe* g = creer_graphe(N);
    if (g == NULL) return NULL;

    // Pour éviter les doublons et les boucles sur soi-même
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            // Génère un nombre aléatoire entre 0.0 et 1.0
            float prob = (float)rand() / (float)RAND_MAX;
            if (prob < densite) {
                ajouter_arete(g, i, j);
            }
        }
    }
    return g;
}

int main() {
    
    // Indique à printf d'utiliser les paramètres français (pour la virgule)
    setlocale(LC_ALL, ""); 

    // Initialise le générateur de nombres aléatoires
    srand((unsigned int)time(NULL));

    // Tailles de graphes à tester
    int tailles[] = {10, 50, 100, 200, 500, 1000, 2000, 4000, 8000};
    int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);
    float densite = 0.1; // Graphe avec 10% d'arêtes

    // En-tête CSV avec ';' comme séparateur
    printf("N;Temps_CPU (secondes)\n");

    for (int i = 0; i < nb_tailles; i++) {
        int N = tailles[i];
        
        clock_t start = clock();
        
        Graphe* g = genererGrapheAleatoire(N, densite);
        if (g == NULL) {
            fprintf(stderr, "Erreur generation graphe N=%d\n", N);
            continue;
        }
        
        // On suppose que le printf dans coloration_welsh_powell est commenté
        int* couleurs = coloration_welsh_powell(g);
        
        clock_t end = clock();
        
        double temps_cpu = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // %f va maintenant imprimer une virgule grace a setlocale
        printf("%d;%f\n", N, temps_cpu);

        // Nettoyage
        liberer_graphe(g);
        free(couleurs);
    }

    return 0;
}