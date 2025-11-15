#include "liste.h"

// alloue l'espace mémoire pour une cellule, remplit les champs de la
// structure cellule et retourne un pointeur sur cette cellule 
cellule *NouvCel (point p){
    cellule *nc = (cellule*)malloc(sizeof(cellule));
    if(nc==NULL){
        printf("erreur d'allocation mémoire");
        exit(1);
    }

    nc->p = p;
    nc->precedent = NULL;
    nc->suivant = NULL;

    return nc;
} 

// permet d'insérer la cellule cel après la place pl
// dans la liste liste
void InsererCellule(int pl, cellule *cel, cellule *liste){

    if(cel == NULL || liste == NULL){
        printf("la cellule à inserer ou la liste est NULL");
        return;
    }
    cellule *temp = liste;
    
    // On se déplace jusqu'à la cellule d'index 'pl'
    for(int i=0; i < pl; i++){
        if(temp->suivant == NULL) {
            // Si la position est hors de portée, on s'arrête
            // pour insérer à la fin de la liste atteinte.
            break;
        }
        temp = temp->suivant;
    } 
    
    // Insertion de 'cel' après 'temp'
    cel->suivant = temp->suivant;
    cel->precedent = temp;

    if(temp->suivant != NULL){
        temp->suivant->precedent = cel;
    }
    temp->suivant = cel;
}

// permet de supprimer la cellule à la position pl dans la
// liste (version corrigée)
void SupprimeCellule(int pl, cellule **liste) {
    if (*liste == NULL) {
        printf("La liste est vide\n");
        return;
    }

    cellule *temp = *liste;

    // Parcourir jusqu'à la position 'pl'
    for (int i = 0; i < pl; i++) {
        if (temp == NULL) {
            printf("La position est hors de portée\n");
            return;
        }
        temp = temp->suivant;
    }

    if (temp == NULL) {
        printf("La cellule est hors de portée\n");
        return;
    }

    // Si la cellule à supprimer est la tête
    if (temp->precedent == NULL) {
        *liste = temp->suivant; // Mise à jour de la tête
        if (*liste != NULL) {
            (*liste)->precedent = NULL;
        }
    }
    // Si la cellule à supprimer est la dernière
    else if (temp->suivant == NULL) {
        temp->precedent->suivant = NULL;
    }
    // Si la cellule est au milieu
    else {
        temp->precedent->suivant = temp->suivant;
        temp->suivant->precedent = temp->precedent;
    }

    free(temp); // Libérer la mémoire de la cellule supprimée
}

// affiche la liste liste
void Afficher(cellule *liste){
    cellule *temp = liste;
    while(temp != NULL){
        printf("(%d;%d) ",temp->p.x,temp->p.y);
        temp = temp->suivant;
    }
}