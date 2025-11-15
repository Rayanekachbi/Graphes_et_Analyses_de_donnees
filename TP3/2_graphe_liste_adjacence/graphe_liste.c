#include "graphe_liste.h"
#include <string.h> // Pour strdup et strcmp

// Fonctions de Liste

// Crée une nouvelle cellule de voisin (similaire à NouvCel).
CelluleVoisin* NouvCelVoisin(Sommet* v) {
    CelluleVoisin* nc = (CelluleVoisin*)malloc(sizeof(CelluleVoisin));
    if (nc == NULL) {
        perror("Erreur d'allocation CelluleVoisin");
        exit(1);
    }
    nc->voisin = v;
    nc->suivant = NULL;
    return nc;
}

// Insère un voisin au début de la liste d'un sommet.
void InsererVoisin(Sommet* s, Sommet* v) {
    if (s == NULL || v == NULL) return;
    
    CelluleVoisin* nc = NouvCelVoisin(v);
    
    // Insère en tête de liste
    nc->suivant = s->listeVoisins;
    s->listeVoisins = nc;
}

// Fonctions de Graphe

// Crée un graphe (tableau de sommets) à partir d'une liste de noms.
Graphe* creerGrapheListe(int nb_sommets, const char** noms) {
    Graphe* g = (Graphe*)malloc(sizeof(Graphe));
    if (g == NULL) {
        perror("Erreur allocation Graphe");
        return NULL;
    }
    g->nb_sommets = nb_sommets;

    // Alloue le tableau de tous les sommets
    g->tab_sommets = (Sommet*)malloc(nb_sommets * sizeof(Sommet));
    if (g->tab_sommets == NULL) {
        perror("Erreur allocation tab_sommets");
        free(g);
        return NULL;
    }

    // Initialise chaque sommet
    for (int i = 0; i < nb_sommets; i++) {
        g->tab_sommets[i].id = i;
        g->tab_sommets[i].nom = strdup(noms[i]); // strdup alloue et copie
        g->tab_sommets[i].listeVoisins = NULL;
        g->tab_sommets[i].degre = 0;
        g->tab_sommets[i].couleur = 0; // 0 = non coloré
    }
    return g;
}

// Libère toute la mémoire du graphe (sommets et listes).
void libererGrapheListe(Graphe* g) {
    if (g == NULL) return;

    for (int i = 0; i < g->nb_sommets; i++) {
        // Libère le nom du sommet
        free(g->tab_sommets[i].nom);
        
        // Libère la liste chaînée des voisins
        CelluleVoisin* cel = g->tab_sommets[i].listeVoisins;
        while (cel != NULL) {
            CelluleVoisin* aSupprimer = cel;
            cel = cel->suivant;
            free(aSupprimer);
        }
    }
    
    // Libère le tableau de sommets
    free(g->tab_sommets);
    // Libère le graphe
    free(g);
}

// Ajoute une arête non-orientée entre deux sommets (par ID).
void ajouterAreteListe(Graphe* g, int id1, int id2) {
    if (id1 < 0 || id1 >= g->nb_sommets || id2 < 0 || id2 >= g->nb_sommets) {
        fprintf(stderr, "Erreur: ID de sommet invalide (%d, %d)\n", id1, id2);
        return;
    }

    Sommet* s1 = &g->tab_sommets[id1];
    Sommet* s2 = &g->tab_sommets[id2];

    // Ajoute s2 à la liste de s1
    InsererVoisin(s1, s2);
    s1->degre++;
    
    // Ajoute s1 à la liste de s2
    InsererVoisin(s2, s1);
    s2->degre++;
}

// Affiche le graphe (listes d'adjacence).
void afficherGrapheListe(Graphe* g) {
    printf("--- Listes d'adjacence du graphe (%d sommets) ---\n", g->nb_sommets);
    for (int i = 0; i < g->nb_sommets; i++) {
        Sommet* s = &g->tab_sommets[i];
        printf("[%s] (deg %d) -> ", s->nom, s->degre);
        
        CelluleVoisin* v = s->listeVoisins;
        if (v == NULL) {
            printf("NULL");
        }
        while (v != NULL) {
            printf("%s -> ", v->voisin->nom);
            v = v->suivant;
        }
        printf("NULL\n");
    }
}

// Algorithme Welsh-Powell pour Listes

// Fonction de comparaison pour qsort, trie les *pointeurs* de Sommet
// par degré décroissant.
int comparer_sommets_liste(const void* a, const void* b) {
    // On reçoit des pointeurs vers des pointeurs de Sommet (Sommet**)
    Sommet* s1 = *(Sommet**)a;
    Sommet* s2 = *(Sommet**)b;
    return s2->degre - s1->degre; // Tri décroissant
}

// Vérifie si un sommet peut prendre une couleur.
// (Vérifie si un de ses voisins a déjà cette couleur)
int peut_colorer_liste(Sommet* s, int couleur) {
    CelluleVoisin* v_cel = s->listeVoisins;
    while (v_cel != NULL) {
        if (v_cel->voisin->couleur == couleur) {
            return 0; // Conflit trouvé
        }
        v_cel = v_cel->suivant;
    }
    return 1; // Pas de conflit
}

// Applique Welsh-Powell sur un graphe à listes d'adjacence.
void colorationWelshPowellListe(Graphe* g) {
    int n = g->nb_sommets;
    if (n <= 0) return;

    // Créer un tableau de POINTEURS vers les sommets pour le tri
    Sommet** sommets_tries = (Sommet**)malloc(n * sizeof(Sommet*));
    if (sommets_tries == NULL) {
        perror("Allocation sommets_tries echouee");
        return;
    }
    for (int i = 0; i < n; i++) {
        sommets_tries[i] = &g->tab_sommets[i];
    }
    
    // Trier les sommets par degré (déjà calculé lors de l'ajout des arêtes)
    qsort(sommets_tries, n, sizeof(Sommet*), comparer_sommets_liste);
    
    // Initialisation (déjà faite dans creerGrapheListe, s->couleur = 0)
    int couleur_actuelle = 1;
    int sommets_colores = 0;

    printf("\n--- Ordre de marquage (Welsh-Powell) ---\n");
    
    // Boucle principale de coloration
    while (sommets_colores < n) {
        printf("Application de la Couleur %d sur :\n", couleur_actuelle);
        
        for (int i = 0; i < n; i++) {
            Sommet* s = sommets_tries[i];
            
            // Si le sommet n'a pas de couleur
            if (s->couleur == 0) {
                // Vérifier s'il peut prendre la couleur actuelle
                if (peut_colorer_liste(s, couleur_actuelle)) {
                    s->couleur = couleur_actuelle;
                    sommets_colores++;
                    printf("   -> %s\n", s->nom); // Affiche le marquage
                }
            }
        }
        
        if (sommets_colores < n) {
            couleur_actuelle++;
        }
    }
    
    // Affichage final
    printf("\n--- Resultats de la Coloration (Listes) ---\n");
    printf("Algorithme a utilise %d couleurs.\n", couleur_actuelle);
    for (int c = 1; c <= couleur_actuelle; c++) {
        printf("   Couleur %d: ", c);
        for (int i = 0; i < n; i++) {
            if (g->tab_sommets[i].couleur == c) {
                printf("%s ", g->tab_sommets[i].nom);
            }
        }
        printf("\n");
    }

    free(sommets_tries);
}