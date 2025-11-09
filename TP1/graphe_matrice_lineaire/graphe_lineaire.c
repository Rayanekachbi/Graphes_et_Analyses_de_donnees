#include "graphe_lineaire.h" // On inclut le nouveau .h
#include <string.h> // Pour calloc

// --- Fonctions de base du Graphe ---

Graphe* creer_graphe(int nb_sommets) {
    // 1. Allouer la structure Graphe
    Graphe* g = (Graphe*)malloc(sizeof(Graphe));
    if (g == NULL) {
        perror("Erreur allocation graphe");
        exit(1);
    }
    g->nb_sommets = nb_sommets;

    // --- MODIFIÉ ---
    // 2. Allouer la matrice en un seul bloc (N * N)
    // calloc met la mémoire à 0, c'est parfait pour nous
    g->adjacence = (int*)calloc(nb_sommets * nb_sommets, sizeof(int));
    if (g->adjacence == NULL) {
        perror("Erreur allocation matrice linéarisée");
        free(g);
        exit(1);
    }
    
    return g;
}

void liberer_graphe(Graphe* g) {
    if (g == NULL) return;
    
    // --- MODIFIÉ ---
    // 1. Libérer le bloc unique de la matrice
    free(g->adjacence);
    // 2. Libérer la structure
    free(g);
}

void ajouter_arete(Graphe* g, int v1, int v2) {
    // On récupère N pour la formule
    int n = g->nb_sommets;
    
    if (v1 >= 0 && v1 < n && v2 >= 0 && v2 < n) {
        // --- MODIFIÉ ---
        // On utilise la formule [i * N + j]
        g->adjacence[v1 * n + v2] = 1;
        g->adjacence[v2 * n + v1] = 1; // Graphe non-orienté
    }
}

void afficher_matrice(Graphe* g) {
    int n = g->nb_sommets; // On récupère N
    printf("Matrice d'adjacence (%d sommets) - [LINEARISÉE]:\n", n);
    printf("   ");
    for (int i = 0; i < n; i++) printf("%d ", i);
    printf("\n---");
    for (int i = 0; i < n; i++) printf("--");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d | ", i);
        for (int j = 0; j < n; j++) {
            // --- MODIFIÉ ---
            // On utilise la formule [i * N + j] pour l'accès
            printf("%d ", g->adjacence[i * n + j]);
        }
        printf("\n");
    }
}

// --- Algorithme Welsh-Powell ---

// Structure temporaire pour trier les sommets par degré
// (Identique à la version précédente)
typedef struct {
    int id_sommet;
    int degre;
} SommetInfo;

// Fonction de comparaison pour qsort (tri décroissant)
// (Identique à la version précédente)
int comparer_sommets(const void* a, const void* b) {
    SommetInfo* s1 = (SommetInfo*)a;
    SommetInfo* s2 = (SommetInfo*)b;
    return s2->degre - s1->degre; // Tri décroissant
}

// Vérifie si un sommet peut prendre une couleur
// (s'il n'est adjacent à aucun sommet déjà coloré avec cette couleur)
int peut_colorer(Graphe* g, int sommet, int couleur, int* couleurs) {
    int n = g->nb_sommets; // On récupère N
    
    for (int i = 0; i < n; i++) {
        // --- MODIFIÉ ---
        // On utilise la formule [i * N + j] pour l'accès
        // (ici [sommet * N + i])
        if (g->adjacence[sommet * n + i] == 1 && couleurs[i] == couleur) {
            return 0; // Ne peut pas colorer
        }
    }
    return 1; // Peut colorer
}

int* coloration_welsh_powell(Graphe* g) {
    int n = g->nb_sommets;
    
    // 1. Calculer les degrés
    SommetInfo* infos_sommets = (SommetInfo*)malloc(n * sizeof(SommetInfo));
    for (int i = 0; i < n; i++) {
        infos_sommets[i].id_sommet = i;
        infos_sommets[i].degre = 0;
        for (int j = 0; j < n; j++) {
            // --- MODIFIÉ ---
            // On utilise la formule [i * N + j] pour l'accès
            if (g->adjacence[i * n + j] == 1) {
                infos_sommets[i].degre++;
            }
        }
    }

    // 2. Trier les sommets par degré décroissant
    // (Identique à la version précédente)
    qsort(infos_sommets, n, sizeof(SommetInfo), comparer_sommets);

    // 3. Initialiser le tableau des couleurs
    // (Identique à la version précédente)
    int* couleurs = (int*)calloc(n, sizeof(int));
    
    int couleur_actuelle = 1;
    int sommets_colores = 0;

    // 4. Boucle principale de coloration
    // (Identique à la version précédente, car la logique
    // d'accès est cachée dans la fonction 'peut_colorer')
    while (sommets_colores < n) {
        for (int i = 0; i < n; i++) {
            int sommet_id = infos_sommets[i].id_sommet;

            if (couleurs[sommet_id] == 0) {
                if (peut_colorer(g, sommet_id, couleur_actuelle, couleurs)) {
                    couleurs[sommet_id] = couleur_actuelle;
                    sommets_colores++;
                }
            }
        }
        if (sommets_colores < n) {
            couleur_actuelle++;
        }
    }

    free(infos_sommets);

    printf("\nAlgorithme (linéarisé) termine avec %d couleurs.\n", couleur_actuelle);
    return couleurs;
}