#include "graphe.h"
#include <string.h> // Pour calloc (ou memset)

// Fonctions de base du Graphe

Graphe* creer_graphe(int nb_sommets) {
    // Allouer la structure Graphe
    Graphe* g = (Graphe*)malloc(sizeof(Graphe));
    if (g == NULL) {
        perror("Erreur allocation graphe");
        exit(1);
    }
    g->nb_sommets = nb_sommets;

    // Allouer le tableau des pointeurs de lignes
    g->adjacence = (int**)malloc(nb_sommets * sizeof(int*));
    if (g->adjacence == NULL) {
        perror("Erreur allocation matrice (lignes)");
        free(g);
        exit(1);
    }

    // Allouer chaque ligne et l'initialiser à 0
    for (int i = 0; i < nb_sommets; i++) {
        // calloc met la mémoire à 0
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
    
    // Libérer chaque ligne
    for (int i = 0; i < g->nb_sommets; i++) {
        free(g->adjacence[i]);
    }
    // Libérer le tableau de pointeurs
    free(g->adjacence);
    // Libérer la structure
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
    printf("   "); // Espace pour l'alignement
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

// Algorithme Welsh-Powell

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
    
    // Calculer les degrés
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

    // Trier les sommets par degré décroissant
    qsort(infos_sommets, n, sizeof(SommetInfo), comparer_sommets);

    // Initialiser le tableau des couleurs
    // calloc met tout à 0 (0 = non coloré)
    int* couleurs = (int*)calloc(n, sizeof(int));
    
    int couleur_actuelle = 1;
    int sommets_colores = 0;

    // Boucle principale de coloration
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

// NOUVELLES FONCTIONS TP2

Graphe* chargeGraphe(const char* nom_fichier) {
    FILE* f = NULL;
    int nb_sommets = 0;
    
    if (nom_fichier != NULL) {
        f = fopen(nom_fichier, "r");
        if (f == NULL) {
            perror("Erreur ouverture fichier");
            return NULL;
        }
        printf("Chargement du graphe depuis '%s'...\n", nom_fichier);
    } else {
        f = stdin; // Lire depuis l'entrée standard
        printf("Entrez l'ordre du graphe (nb sommets) : ");
    }

    // Lire l'ordre du graphe (première ligne)
    if (fscanf(f, "%d", &nb_sommets) != 1) {
        fprintf(stderr, "Erreur lecture nombre de sommets.\n");
        if (nom_fichier != NULL) fclose(f);
        return NULL;
    }
    
    if (nb_sommets <= 0) {
         fprintf(stderr, "Nombre de sommets invalide.\n");
         if (nom_fichier != NULL) fclose(f);
        return NULL;
    }

    // Créer le graphe
    Graphe* g = creer_graphe(nb_sommets);
    
    if (nom_fichier == NULL) {
         printf("Entrez la matrice d'adjacence (%d x %d) :\n", nb_sommets, nb_sommets);
    }

    // Lire la matrice
    for (int i = 0; i < nb_sommets; i++) {
        
        // Guide l'utilisateur pour la saisie stdin
        if (nom_fichier == NULL) {
            printf("Entrez la ligne %d (%d entiers) : ", i, nb_sommets);
        }

        for (int j = 0; j < nb_sommets; j++) {
            int val;
            if (fscanf(f, "%d", &val) != 1) {
                 fprintf(stderr, "Erreur lecture matrice [ligne %d, col %d].\n", i, j);
                 liberer_graphe(g);
                 if (nom_fichier != NULL) fclose(f);
                 return NULL;
            }
            // On force l'adjacence à 1 (le TP parle de poids 0 ou 1)
            if (val != 0) {
                // Pas besoin d'appeler ajouter_arete, on remplit directement
                g->adjacence[i][j] = 1;
            }
        }
    }
    
    if (nom_fichier != NULL) {
        fclose(f);
    }
    
    printf("Graphe charge avec %d sommets.\n", nb_sommets);
    return g;
}


void afficher_ordre_marquage_et_resultat(Graphe* g, int* couleurs, const char** noms_sommets) {
    int n = g->nb_sommets;
    
    // On doit recalculer les degrés pour l'ordre de marquage
    SommetInfo* infos_sommets = (SommetInfo*)malloc(n * sizeof(SommetInfo));
    if (!infos_sommets) {
        perror("Erreur allocation infos_sommets");
        return;
    }
    for (int i = 0; i < n; i++) {
        infos_sommets[i].id_sommet = i;
        infos_sommets[i].degre = 0;
        for (int j = 0; j < n; j++) {
            if (g->adjacence[i][j] == 1) {
                infos_sommets[i].degre++;
            }
        }
    }

    // Trier les sommets (l'ordre de marquage)
    qsort(infos_sommets, n, sizeof(SommetInfo), comparer_sommets);

    // Afficher l'ordre de marquage
    printf("\n--- Ordre de marquage (Welsh-Powell) ---\n");
    printf("(Tri des sommets par degre decroissant)\n");
    for (int i = 0; i < n; i++) {
        int id = infos_sommets[i].id_sommet;
        printf("%d. Sommet %d (%s) - Degre: %d\n", 
               i + 1, 
               id, 
               (noms_sommets ? noms_sommets[id] : "--"), 
               infos_sommets[i].degre);
    }

    // Afficher les résultats de la coloration
    printf("\n--- Resultats de la Coloration ---\n");
    // On doit trouver la couleur max
    int nb_couleurs = 0;
    for(int i = 0; i < n; i++) {
        if(couleurs[i] > nb_couleurs) nb_couleurs = couleurs[i];
    }
    printf("Algorithme a utilise %d couleurs.\n", nb_couleurs);

    for (int c = 1; c <= nb_couleurs; c++) {
        printf("   Couleur %d: ", c);
        for (int i = 0; i < n; i++) {
            if (couleurs[i] == c) {
                // Affiche le nom si disponible, sinon l'ID
                if(noms_sommets) printf("%s ", noms_sommets[i]);
                else printf("%d ", i);
            }
        }
        printf("\n");
    }

    free(infos_sommets);
}