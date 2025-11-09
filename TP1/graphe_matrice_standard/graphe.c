#include "graphe.h"
#include <string.h> // Pour calloc (ou memset)

// --- Fonctions de base du Graphe ---

Graphe* creer_graphe(int nb_sommets) {
    // 1. Allouer la structure Graphe
    Graphe* g = (Graphe*)malloc(sizeof(Graphe));
    if (g == NULL) {
        perror("Erreur allocation graphe");
        exit(1);
    }
    g->nb_sommets = nb_sommets;

    // 2. Allouer le tableau des pointeurs de lignes
    g->adjacence = (int**)malloc(nb_sommets * sizeof(int*));
    if (g->adjacence == NULL) {
        perror("Erreur allocation matrice (lignes)");
        free(g);
        exit(1);
    }

    // 3. Allouer chaque ligne et l'initialiser à 0
    for (int i = 0; i < nb_sommets; i++) {
        // calloc met la mémoire à 0, c'est parfait pour nous
        g->adjacence[i] = (int*)calloc(nb_sommets, sizeof(int));
        if (g->adjacence[i] == NULL) {
            perror("Erreur allocation matrice (colonne)");
            // Libérer tout ce qui a été alloué avant de planter
            for(int j = 0; j < i; j++) free(g->adjacence[j]);
            free(g->adjacence);
            free(g);
            exit(1);
        }
    }
    return g;
}

void liberer_graphe(Graphe* g) {
    if (g == NULL) return;
    
    // 1. Libérer chaque ligne
    for (int i = 0; i < g->nb_sommets; i++) {
        free(g->adjacence[i]);
    }
    // 2. Libérer le tableau de pointeurs
    free(g->adjacence);
    // 3. Libérer la structure
    free(g);
}

void ajouter_arete(Graphe* g, int v1, int v2) {
    if (v1 >= 0 && v1 < g->nb_sommets && v2 >= 0 && v2 < g->nb_sommets) {
        g->adjacence[v1][v2] = 1;
        g->adjacence[v2][v1] = 1; // Graphe non-orienté
    }
}

void afficher_matrice(Graphe* g) {
    printf("Matrice d'adjacence (%d sommets):\n", g->nb_sommets);
    printf("   ");
    for (int i = 0; i < g->nb_sommets; i++) printf("%d ", i);
    printf("\n---");
    for (int i = 0; i < g->nb_sommets; i++) printf("--");
    printf("\n");

    for (int i = 0; i < g->nb_sommets; i++) {
        printf("%d | ", i);
        for (int j = 0; j < g->nb_sommets; j++) {
            printf("%d ", g->adjacence[i][j]);
        }
        printf("\n");
    }
}

// --- Algorithme Welsh-Powell ---

// Structure temporaire pour trier les sommets par degré
typedef struct {
    int id_sommet;
    int degre;
} SommetInfo;

// Fonction de comparaison pour qsort (tri décroissant)
int comparer_sommets(const void* a, const void* b) {
    SommetInfo* s1 = (SommetInfo*)a;
    SommetInfo* s2 = (SommetInfo*)b;
    return s2->degre - s1->degre; // Tri décroissant
}

// Vérifie si un sommet peut prendre une couleur
// (s'il n'est adjacent à aucun sommet déjà coloré avec cette couleur)
int peut_colorer(Graphe* g, int sommet, int couleur, int* couleurs) {
    for (int i = 0; i < g->nb_sommets; i++) {
        // Si 'i' est adjacent à 'sommet' ET 'i' a déjà la couleur 'couleur'
        if (g->adjacence[sommet][i] == 1 && couleurs[i] == couleur) {
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
            if (g->adjacence[i][j] == 1) {
                infos_sommets[i].degre++;
            }
        }
    }

    // 2. Trier les sommets par degré décroissant
    qsort(infos_sommets, n, sizeof(SommetInfo), comparer_sommets);

    // 3. Initialiser le tableau des couleurs
    // calloc met tout à 0 (0 = non coloré)
    int* couleurs = (int*)calloc(n, sizeof(int));
    
    int couleur_actuelle = 1;
    int sommets_colores = 0;

    // 4. Boucle principale de coloration
    while (sommets_colores < n) {
        // Parcourir la liste triée
        for (int i = 0; i < n; i++) {
            int sommet_id = infos_sommets[i].id_sommet;

            // Si ce sommet n'a pas de couleur
            if (couleurs[sommet_id] == 0) {
                // Vérifier s'il peut prendre la couleur actuelle
                if (peut_colorer(g, sommet_id, couleur_actuelle, couleurs)) {
                    couleurs[sommet_id] = couleur_actuelle;
                    sommets_colores++;
                }
            }
        }
        // S'il reste des sommets, on passe à la couleur suivante
        if (sommets_colores < n) {
            couleur_actuelle++;
        }
    }

    // Libérer la structure temporaire
    free(infos_sommets);

    printf("\nAlgorithme termine avec %d couleurs.\n", couleur_actuelle);
    return couleurs;
}