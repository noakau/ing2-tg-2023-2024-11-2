#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exclusion.h"

int main() {

    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char* filename = (char*)malloc(100 * sizeof(char));

    // Veuillez noter que vous avez déclaré deux fois 'filename' (une fois en tant que pointeur et une fois en tant que FILE*)
    // Je corrige cela en renommant le pointeur
    FILE *file = fopen("exclusion.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier texte");
        return 1;
    }

    // Obtenir le nom du fichier depuis l'utilisateur
    printf("Entrez le nom du fichier : ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne de fgets

    // Charger les exclusions à partir du fichier texte
    Exclusion* exclusions = NULL;
    int numExclusions = readExclusions(filename, &exclusions);

    printf("Entrez les stations a verifier :\n");
    int op1, op2;
    scanf("%d %d", &op1, &op2);

    int resultat = canAssign(op1, op2, exclusions, numExclusions);
    if (resultat == 1) {
        printf("\nCes operations peuvent etre dans la meme station.\n");
    } else {
        printf("\nCes operations ne peuvent pas etre dans la meme station.\n");
    }

    int* operations = NULL;
    int num_operations = 0;

    getDistinctOperations(exclusions, numExclusions, &operations, &num_operations);

    // Utiliser maintenant le tableau operations pour affecter les opérations aux stations
    assignOperationsToStations(operations, num_operations, exclusions, numExclusions);

    // Libérer la mémoire allouée
    free(filename);
    free(exclusions);

    char pourPause[20];
    fgets(pourPause, sizeof(pourPause), stdin);

    return 0;
}
