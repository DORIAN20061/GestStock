
#include <stdio.h>
#include <stdlib.h>
#include "produits.h"

void acheterProduits() {
    int id;
    int quantite;
    printf("ID du produit a acheter: ");
    scanf("%d", &id);
    printf("Quantite a acheter: ");
    scanf("%d", &quantite);

    FILE *fichier = fopen("produits.csv", "r");
    FILE *tempFichier = fopen("temp.csv", "w");
    if (fichier == NULL || tempFichier == NULL) {
        printf("Erreur: Impossible d'ouvrir les fichiers\n");
        return;
    }

    char ligne[256];
    int trouver = 0;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Produit produit;
        sscanf(ligne, "%d,%[^,],%d,%f", &produit.id, produit.nom, &produit.quantite, &produit.prix);
        if (produit.id == id) {
            if (produit.quantite >= quantite) {
                produit.quantite -= quantite;
                fprintf(tempFichier, "%d,%s,%d,%.2f\n", produit.id, produit.nom, produit.quantite, produit.prix);
                trouver = 1;
            } else {
                printf("Quantite insuffisante en stock.\n");
                fclose(fichier);
                fclose(tempFichier);
                remove("temp.csv");
                return;
            }
        } else {
            fprintf(tempFichier, "%s", ligne);
        }
    }
    fclose(fichier);
    fclose(tempFichier);

    if (trouver) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
        printf("Achat effectue avec succes.\n");
    } else {
        remove("temp.csv");
        printf("Produit non trouve.\n");
    }
}
