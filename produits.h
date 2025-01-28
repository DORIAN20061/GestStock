
#ifndef PRODUITS_H
#define PRODUITS_H

typedef struct {
    int id;
    char nom[50];
    int quantite;
    float prix;
} Produit;

void afficherProduits();
void ajouterProduit();
void modifierProduit();
void supprimerProduit();
int genererID();

#endif
