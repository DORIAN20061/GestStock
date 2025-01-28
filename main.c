#include <stdio.h>
#include <stdlib.h>
#include "produits.h"
#include "commandes.h"
#include "statistiques.h"

void afficherMenu() {
    printf("\n");
    printf("\n");
    printf("\n");
    printf( "                          ****************************************\n");
    printf( "                              Bienvenue Sur GESTOCK KEYCE\n");
    printf( "                          ****************************************\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                           Menu\n");
    printf("                           ----- \n");
    printf("                           1. Afficher les produits\n");
    printf("                           2. Ajouter un produit\n");
    printf("                           3. Modifier un produit\n");
    printf("                           4. Supprimer un produit\n");
    printf("                           5. Acheter des produits\n");
    printf("                           6. Afficher les statistiques\n");
    printf("                           7. Quitter\n");
     printf("\n");
    printf("\n");
    printf("Choisissez une option: ");
}

int main() {
    int choix;
    do {
        afficherMenu();
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                afficherProduits();
                break;
            case 2:
                ajouterProduit();
                break;
            case 3:
                modifierProduit();
                break;
            case 4:
                supprimerProduit();
                break;
            case 5:
                acheterProduits();
                break;
            case 6:
                afficherStatistiques();
                break;
            case 7:
                printf("Au revoir !--------------------------------------\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choix != 7);

    return 0;
}
