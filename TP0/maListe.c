#include "liste.h"

int main(){
    int nbr;
    point a;
    cellule *head = NULL; // Toujours initialiser la tête à NULL
    cellule *A = NULL;

    printf("Nombre de points: ");
    scanf("%d",&nbr);

    if(nbr <= 0) {
        printf("Nombre de points nul ou negatif. Fin.\n");
        return 0; 
    }

    printf("Inserez x et y du point n 1: ");
    scanf("%d%d",&(a.x),&(a.y));
    head = NouvCel(a);
    A = head;

    // Ajouter le reste des points
    for(int i = 1; i < nbr; i++){ 
        printf("Inserez x et y du point n %d: ",i+1);
        scanf("%d%d",&(a.x),&(a.y));
        
        A->suivant = NouvCel(a);
        A->suivant->precedent = A; // Lier le précédent (liste doublement chaînée)
        A = A->suivant; // Avancer au nouveau noeud
    }

    printf("Liste creee: ");
    Afficher(head);

    // Insertion
    point b_point = {10, 11}; // Initialisation propre du point
    cellule *B = NouvCel(b_point);

    printf("\nInsertion de (10;11) en position 2:\n");
    InsererCellule(2, B, head); 
    Afficher(head);

    // Suppression
    printf("\nSuppression de l'element en position 2:\n");
    SupprimeCellule(2, &head); // On passe l'adresse de la tête
    Afficher(head);

    // Libération de la mémoire
    printf("\nLiberation de la liste...\n");
    cellule *temp = head;
    cellule *aSupprimer;
    
    while (temp != NULL) {
        aSupprimer = temp;
        temp = temp->suivant;
        free(aSupprimer);
    }
    head = NULL; 
    
    printf("Memoire liberee.\n");
    
    return 0;
}