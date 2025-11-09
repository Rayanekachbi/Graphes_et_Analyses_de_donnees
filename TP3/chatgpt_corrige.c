// Fichier : TP3/chatgpt_corrige.c

#include <stdio.h>
#include <stdlib.h> // Pour malloc, free, qsort

#define MAX_VERTICES 100

struct Graph {
    int vertices;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
};

void addEdge(struct Graph* graph, int u, int v) {
    graph->adjMatrix[u][v] = 1;
    graph->adjMatrix[v][u] = 1;
}

// --- J'ai réutilisé la structure SommetInfo de votre TP2 ---
// --- pour qsort, car le bubble sort est très lent ---
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

// Fonction "peut_colorer" de votre TP2, adaptée
int peut_colorer(struct Graph* graph, int sommet, int couleur, int* couleurs) {
    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjMatrix[sommet][i] == 1 && couleurs[i] == couleur) {
            return 0; // Ne peut pas colorer
        }
    }
    return 1; // Peut colorer
}


void welshPowell(struct Graph* graph) {
    int n = graph->vertices;
    if (n <= 0) return;

    // 1. Calculer les degrés
    SommetInfo* infos_sommets = (SommetInfo*)malloc(n * sizeof(SommetInfo));
    if (infos_sommets == NULL) {
        perror("Allocation infos_sommets echouee");
        return;
    }

    for (int i = 0; i < n; i++) {
        infos_sommets[i].id_sommet = i;
        infos_sommets[i].degre = 0;
        for (int j = 0; j < n; j++) {
            if (graph->adjMatrix[i][j] == 1) {
                infos_sommets[i].degre++;
            }
        }
    }

    // 2. Trier les sommets par degré décroissant
    qsort(infos_sommets, n, sizeof(SommetInfo), comparer_sommets);

    // 3. Initialiser le tableau des couleurs
    // 0 = non coloré
    int* couleurs = (int*)calloc(n, sizeof(int));
    if (couleurs == NULL) {
        perror("Allocation couleurs echouee");
        free(infos_sommets);
        return;
    }

    // --- LOGIQUE CORRIGEE (basée sur votre TP2) ---
    int couleur_actuelle = 1;
    int sommets_colores = 0;

    while (sommets_colores < n) {
        // Parcourir la liste triée
        for (int i = 0; i < n; i++) {
            int sommet_id = infos_sommets[i].id_sommet;

            // Si ce sommet n'a pas de couleur
            if (couleurs[sommet_id] == 0) {
                // Vérifier s'il peut prendre la couleur actuelle
                if (peut_colorer(graph, sommet_id, couleur_actuelle, couleurs)) {
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
    // --- FIN LOGIQUE CORRIGEE ---

    printf("Graphe colore (version C corrigee) avec %d couleurs:\n", couleur_actuelle);
    for (int i = 0; i < n; i++) {
        // Affiche le résultat dans l'ordre des ID (0, 1, 2...)
        printf("Vertex %d: Color %d\n", i, couleurs[i]);
    }

    // Nettoyage
    free(infos_sommets);
    free(couleurs);
}

int main() {
    struct Graph graph;
    graph.vertices = 5;

    // Initialisation TRES IMPORTANTE de la matrice (sinon, valeurs aleatoires)
    for (int i = 0; i < graph.vertices; i++) {
        for (int j = 0; j < graph.vertices; j++) {
            graph.adjMatrix[i][j] = 0;
        }
    }

    // Add edges
    addEdge(&graph, 0, 1);
    addEdge(&graph, 0, 2);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 1, 3);
    addEdge(&graph, 2, 3);
    addEdge(&graph, 3, 4);

    welshPowell(&graph);

    return 0;
}