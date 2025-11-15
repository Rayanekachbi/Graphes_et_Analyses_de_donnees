#include "graphe_liste.h"

// On utilise directement les noms courts (2 lettres)
const char* NOMS_PAYS[11] = {
    "Fr",     // 0
    "Es",     // 1
    "Po",     // 2
    "An",     // 3
    "It",     // 4
    "Au",     // 5
    "Su",     // 6
    "Al",     // 7
    "Lu",     // 8
    "Be",     // 9
    "PB"      // 10
};

const int NB_PAYS = 11;

// IDs pour la lisibilité
#define FR 0
#define ES 1
#define PO 2
#define AN 3
#define IT 4
#define AU 5
#define SU 6
#define AL 7
#define LU 8
#define BE 9
#define PB 10

int main() {
    printf("--- Lancement Test TP3 - Graphe par Listes d'Adjacence ---\n");

    // Créer le graphe
    Graphe* g = creerGrapheListe(NB_PAYS, NOMS_PAYS);
    if (g == NULL) {
        return 1;
    }

    // Ajouter les arêtes (frontières)
    printf("Ajout des aretes...\n");
    // France (Fr) : Es, An, It, Su, Al, Lu, Be
    ajouterAreteListe(g, FR, ES);
    ajouterAreteListe(g, FR, AN);
    ajouterAreteListe(g, FR, IT);
    ajouterAreteListe(g, FR, SU);
    ajouterAreteListe(g, FR, AL);
    ajouterAreteListe(g, FR, LU);
    ajouterAreteListe(g, FR, BE);

    // Espagne (Es) : Fr, An, Po
    ajouterAreteListe(g, ES, PO);

    // Italie (It) : Fr, Su, Au
    ajouterAreteListe(g, IT, SU);
    ajouterAreteListe(g, IT, AU);

    // Autriche (Au) : It, Su, Al
    ajouterAreteListe(g, AU, SU);
    ajouterAreteListe(g, AU, AL);

    // Suisse (Su) : Fr, It, Au, Al
    ajouterAreteListe(g, SU, AL);

    // Allemagne (Al) : Fr, Su, Au, Lu, Be, PB
    ajouterAreteListe(g, AL, LU);
    ajouterAreteListe(g, AL, BE);
    ajouterAreteListe(g, AL, PB);

    // Luxembourg (Lu) : Fr, Be, Al
    ajouterAreteListe(g, LU, BE);

    // Belgique (Be) : Fr, Lu, Al, PB
    ajouterAreteListe(g, BE, PB);
    
    // Afficher le graphe
    afficherGrapheListe(g);

    // Lancer la coloration
    colorationWelshPowellListe(g);

    // Nettoyage
    libererGrapheListe(g);
    
    printf("\n--- Fin Test TP3 - Graphe par Listes ---\n");
    return 0;
}