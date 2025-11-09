// Fichier : TP2/main_arbre.c

#include "arbre.h"

int main() {
    printf("--- Lancement Test TP2 - Partie Arbres Binaires ---\n");

    // 1. Création de l'arbre synthétique
    Noeud* monArbre = creerArbreSynthetique();
    printf("Arbre synthetique cree.\n");
    printf("Structure attendue : A( B(D, E), C(F, NULL) )\n");

    // 2. Test des parcours
    
    printf("\nParcours Prefixe (RGD) :\n");
    parcoursPrefixe(monArbre);
    printf("\n(Attendu: A B D E C F)");

    printf("\n\nParcours Infixe (GRD) :\n");
    parcoursInfixe(monArbre);
    printf("\n(Attendu: D B E A F C)");

    printf("\n\nParcours Postfixe (GDR) :\n");
    parcoursPostfixe(monArbre);
    printf("\n(Attendu: D E B F C A)");

    // 3. Libération de la mémoire
    printf("\n\nLiberation de l'arbre...\n");
    libererArbre(monArbre);
    printf("Arbre libere.\n");

    printf("\n--- Fin Test TP2 - Partie Arbres ---\n");
    return 0;
}