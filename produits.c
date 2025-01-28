
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "produits.h"
void afficherProduits() {
    FILE *fichier = fopen("produits.csv", "r");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier produits.csv\n");
        return;
    }

    char ligne[256];
    printf("ID\tNom\t\tQuantite\tPrix\n");
    printf("-------------------------------------------------\n");
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int id, quantite;
        float prix;
        char nom[50];
        // Extraction des valeurs
        sscanf(ligne, "%d,%[^,],%d,%f", &id, nom, &quantite, &prix);
        // Affichage sans virgules
        printf("%d\t%-15s\t%d\t\t%.2f\n", id, nom, quantite, prix);
    }
    fclose(fichier);
}int genererID() {
    FILE *fichier = fopen("produits.csv", "r");
    if (fichier == NULL) {
        return 1;
    }

    int id = 0;
    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        int currentID;
        sscanf(ligne, "%d", &currentID);
        if (currentID > id) {
            id = currentID;
        }
    }
    fclose(fichier);
    return id + 1;
}

void ajouterProduit() {
    Produit nouveauProduit;
    nouveauProduit.id = genererID();
    printf("Nom du produit: ");
    scanf("%s", nouveauProduit.nom);
    printf("Quantite: ");
    scanf("%d", &nouveauProduit.quantite);
    printf("Prix: ");
    scanf("%f", &nouveauProduit.prix);

    FILE *fichier = fopen("produits.csv", "a");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier produits.csv\n");
        return;
    }

    fprintf(fichier, "%d,%s,%d,%.2f\n", nouveauProduit.id, nouveauProduit.nom, nouveauProduit.quantite, nouveauProduit.prix);
    fclose(fichier);
    printf("Produit ajoute avec succes.\n");
}

void modifierProduit() {
    int id;
    printf("ID du produit a modifier: ");
    scanf("%d", &id);

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
            printf("Nouveau nom: ");
            scanf("%s", produit.nom);
            printf("Nouvelle quantite: ");
            scanf("%d", &produit.quantite);
            printf("Nouveau prix: ");
            scanf("%f", &produit.prix);
            fprintf(tempFichier, "%d,%s,%d,%.2f\n", produit.id, produit.nom, produit.quantite, produit.prix);
            trouver = 1;
        } else {
            fprintf(tempFichier, "%s", ligne);
        }
    }
    fclose(fichier);
    fclose(tempFichier);

    if (trouver) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
        printf("Produit modifie avec succes.\n");
    } else {
        remove("temp.csv");
        printf("Produit non trouve.\n");
    }
}

void supprimerProduit() {
    int id;
    printf("ID du produit a supprimer: ");
    scanf("%d", &id);

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
        if (produit.id != id) {
            fprintf(tempFichier, "%s", ligne);
        } else {
            trouver = 1;
        }
    }
    fclose(fichier);
    fclose(tempFichier);

    if (trouver) {
        remove("produits.csv");
        rename("temp.csv", "produits.csv");
        printf("Produit supprime avec succes.\n");
    } else {
        remove("temp.csv");
        printf("Produit non trouve.\n");
    }
}
