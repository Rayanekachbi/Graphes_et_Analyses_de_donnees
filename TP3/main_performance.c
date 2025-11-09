// Fichier : TP3/main_performance.c (Modifié pour Excel FR)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h> // <-- 1. AJOUTER CE HEADER
#include "graphe.h" // On réutilise le code du TP2

/**
 * @brief Crée un graphe aléatoire de N sommets.
 * @param N Nombre de sommets.
 * @param densite Probabilité (entre 0.0 et 1.0) qu'une arête existe.
 */
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
    
    // 2. DIRE A PRINTF D'UTILISER LES PARAMETRES FRANCAIS (POUR LA VIRGULE)
    setlocale(LC_ALL, ""); 

    // Initialise le générateur de nombres aléatoires
    srand((unsigned int)time(NULL));

    // On reprend vos tailles qui ont bien fonctionné
    int tailles[] = {10, 50, 100, 200, 500, 1000, 2000, 4000, 8000};
    int nb_tailles = sizeof(tailles) / sizeof(tailles[0]);
    float densite = 0.1; // Graphe avec 10% d'arêtes

    // 3. CHANGER LE SEPARATEUR EN ';'
    printf("N;Temps_CPU (secondes)\n");

    for (int i = 0; i < nb_tailles; i++) {
        int N = tailles[i];
        
        // --- Mesure du temps ---
        clock_t start = clock();
        
        Graphe* g = genererGrapheAleatoire(N, densite);
        if (g == NULL) {
            fprintf(stderr, "Erreur generation graphe N=%d\n", N);
            continue;
        }
        
        // On suppose que vous avez commenté le printf dans graphe.c
        int* couleurs = coloration_welsh_powell(g);
        
        clock_t end = clock();
        // --- Fin Mesure ---
        
        double temps_cpu = ((double) (end - start)) / CLOCKS_PER_SEC;
        
        // 4. CHANGER LE SEPARATEUR EN ';'
        // %f va maintenant imprimer une virgule grace a setlocale
        printf("%d;%f\n", N, temps_cpu);

        // Nettoyage
        liberer_graphe(g);
        free(couleurs);
    }

    return 0;
}