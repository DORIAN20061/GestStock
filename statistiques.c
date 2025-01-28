
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "produits.h"
#include "statistiques.h"

void afficherStatistiques() {
    FILE *fichier = fopen("produits.csv", "r");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier produits.csv\n");
        return;
    }

    int nombreProduits = 0;
    int quantiteTotale = 0;
    float prixTotal = 0.0;
    float prixMin = __FLT_MAX__;
    float prixMax = 0.0;
    char produitMin[50];
    char produitMax[50];

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Produit produit;
        sscanf(ligne, "%d,%[^,],%d,%f", &produit.id, produit.nom, &produit.quantite, &produit.prix);
        nombreProduits++;
        quantiteTotale += produit.quantite;
        prixTotal += produit.prix;
        if (produit.prix < prixMin) {
            prixMin = produit.prix;
            strcpy(produitMin, produit.nom);
        }
        if (produit.prix > prixMax) {
            prixMax = produit.prix;
            strcpy(produitMax, produit.nom);
        }
    }
    fclose(fichier);

    float prixMoyen = (nombreProduits > 0) ? prixTotal / nombreProduits : 0.0;

    printf("Statistiques des produits:\n");
    printf("Nombre total de produits: %d\n", nombreProduits);
    printf("Quantite totale en stock: %d\n", quantiteTotale);
    printf("Prix moyen des produits: %.2f\n", prixMoyen);
    printf("Produit le moins cher: %s (%.2f)\n", produitMin, prixMin);
    printf("Produit le plus cher: %s (%.2f)\n", produitMax, prixMax);
}
