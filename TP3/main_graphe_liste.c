// Fichier : TP3/main_graphe_liste.c (Modifié pour affichage court)

#include "graphe_liste.h"

// --- MODIFICATION ICI ---
// On utilise directement les noms courts (2 lettres)
const char* NOMS_PAYS[11] = {
    "Fr",      // 0
    "Es",      // 1
    "Po",      // 2
    "An",      // 3
    "It",      // 4
    "Au",      // 5
    "Su",      // 6
    "Al",      // 7
    "Lu",      // 8
    "Be",      // 9
    "PB"       // 10
};
// --- FIN MODIFICATION ---

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

    // 1. Créer le graphe
    Graphe* g = creerGrapheListe(NB_PAYS, NOMS_PAYS);
    if (g == NULL) {
        return 1;
    }

    // 2. Ajouter les arêtes (frontières)
    printf("Ajout des aretes...\n");
    // France (Fr) : Es, An, It, Su, Al, Lu, Be
    ajouterAreteListe(g, FR, ES);
    ajouterAreteListe(g, FR, AN);
    ajouterAreteListe(g, FR, IT);
    ajouterAreteListe(g, FR, SU);
    ajouterAreteListe(g, FR, AL);
    ajouterAreteListe(g, FR, LU);
    ajouterAreteListe(g, FR, BE);

    // Espagne (Es) : Fr, An, Po (Fr, An déjà faits)
    ajouterAreteListe(g, ES, PO);

    // Portugal (Po) : Es (déjà fait)
    // Andorre (An) : Es, Fr (déjà faits)

    // Italie (It) : Fr, Su, Au (Fr déjà fait)
    ajouterAreteListe(g, IT, SU);
    ajouterAreteListe(g, IT, AU);

    // Autriche (Au) : It, Su, Al (It déjà fait)
    ajouterAreteListe(g, AU, SU);
    ajouterAreteListe(g, AU, AL);

    // Suisse (Su) : Fr, It, Au, Al (tous déjà faits sauf Al)
    ajouterAreteListe(g, SU, AL);

    // Allemagne (Al) : Fr, Su, Au, Lu, Be, PB (tous déjà faits sauf PB)
    ajouterAreteListe(g, AL, LU); // (Fr, Su, Au déjà faits)
    ajouterAreteListe(g, AL, BE);
    ajouterAreteListe(g, AL, PB);

    // Luxembourg (Lu) : Fr, Be, Al (tous déjà faits)
    ajouterAreteListe(g, LU, BE); // (Fr, Al déjà faits)

    // Belgique (Be) : Fr, Lu, Al, PB (tous déjà faits sauf PB)
    ajouterAreteListe(g, BE, PB);
    
    // Pays-Bas (PB) : Be, Al (tous déjà faits)

    // 3. Afficher le graphe
    afficherGrapheListe(g);

    // 4. Lancer la coloration
    colorationWelshPowellListe(g);

    // 5. Nettoyage
    libererGrapheListe(g);
    
    printf("\n--- Fin Test TP3 - Graphe par Listes ---\n");
    return 0;
}