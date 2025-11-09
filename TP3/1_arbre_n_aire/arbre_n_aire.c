#include "arbre_n_aire.h"

NoeudNAire* creerNoeudNAire(char val) {
    NoeudNAire* n = (NoeudNAire*)malloc(sizeof(NoeudNAire));
    n->val = val;
    n->premierEnfant = NULL;
    n->frereSuivant = NULL;
    return n;
}

void libererArbreNAire(NoeudNAire* racine) {
    if (racine == NULL) return;
    libererArbreNAire(racine->premierEnfant);
    libererArbreNAire(racine->frereSuivant);
    free(racine);
}

// Ajoute un enfant à un noeud parent
void ajouterEnfant(NoeudNAire* parent, NoeudNAire* enfant) {
    if (parent == NULL || enfant == NULL) return;

    if (parent->premierEnfant == NULL) {
        // C'est le premier enfant
        parent->premierEnfant = enfant;
    } else {
        // Le parent a déjà des enfants, on trouve le dernier frère
        NoeudNAire* frere = parent->premierEnfant;
        while (frere->frereSuivant != NULL) {
            frere = frere->frereSuivant;
        }
        // On s'ajoute à la fin de la liste des frères
        frere->frereSuivant = enfant;
    }
}

// Affiche l'arbre (parcours n-aire préfixe modifié)
void afficherArbreNAire(NoeudNAire* racine, int profondeur) {
    if (racine == NULL) return;
    
    // Indentation pour la profondeur
    for (int i = 0; i < profondeur; i++) {
        printf("  ");
    }
    printf("- %c\n", racine->val);
    
    // Visite récursive des enfants
    afficherArbreNAire(racine->premierEnfant, profondeur + 1);
    
    // Visite récursive des frères (sur le même niveau)
    afficherArbreNAire(racine->frereSuivant, profondeur);
}