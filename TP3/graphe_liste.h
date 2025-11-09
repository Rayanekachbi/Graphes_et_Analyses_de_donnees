#ifndef GRAPHE_LISTE_H
#define GRAPHE_LISTE_H

#include <stdio.h>
#include <stdlib.h>

// Déclaration anticipée pour référence croisée
typedef struct Sommet Sommet;
typedef struct CelluleVoisin CelluleVoisin;

// Le "graphe" est un tableau de Sommets
typedef struct {
    int nb_sommets;
    Sommet* tab_sommets; // Tableau de tous les sommets
} Graphe;

// La cellule de la liste d'adjacence (votre 'cellule' du TP0 adaptée)
struct CelluleVoisin {
    Sommet* voisin; // Pointeur vers le sommet voisin
    CelluleVoisin* suivant;
};

// Le Sommet (nœud du graphe)
struct Sommet {
    int id; // 0, 1, 2...
    char* nom; // "France", "Espagne"...
    CelluleVoisin* listeVoisins; // Tête de la liste de ses voisins
    
    // Champs pour Welsh-Powell
    int degre;
    int couleur;
};

// Fonctions Graphe
Graphe* creerGrapheListe(int nb_sommets, const char** noms);
void libererGrapheListe(Graphe* g);
void ajouterAreteListe(Graphe* g, int id1, int id2);
void afficherGrapheListe(Graphe* g);

// Fonctions Liste (Adaptées de votre TP0/liste.c)
CelluleVoisin* NouvCelVoisin(Sommet* v);
void InsererVoisin(Sommet* s, Sommet* v); // Ajoute v à la liste de s

// Welsh-Powell pour Listes
void colorationWelshPowellListe(Graphe* g);

#endif