#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#include "exclusion.h"


int main() {
    // Demander à l'utilisateur le nom du fichier texte
    // printf("Veuillez entrer le nom du fichier texte : \n ");

    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char* filename = (char*)malloc(100 * sizeof(char));

    // Vérifier si l'allocation de mémoire a réussi
    if (filename == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }


    gets(filename);

    strcpy(filename,"exclusion.txt");
    // Lire le nom du fichier à partir de l'utilisateur
    //scanf("%s", filename);
    //filename="exclusion.txt";

    // Charger les exclusions à partir du fichier texte
    Exclusion* exclusions = NULL;
    int numExclusions = readExclusions(filename, &exclusions);

    printf("entrrez les stations a verifier:\n");
    int op1;
    int op2;
    scanf ("%d %d", &op1, &op2);
    int resultat = canAssign(op1, op2,exclusions, numExclusions );
    if (resultat ==1){
        printf("\n ces operations peuvent etre  dans la meme station.");
        gets(filename);
    }
    else {
        printf("\n ces operations ne peuvent pas etre  dans la meme station.");
        gets(filename);
    }

    int* operations = NULL;
    int num_operations = 0;

    getDistinctOperations(exclusions, numExclusions, &operations, &num_operations);

    // Utilisez maintenant le tableau operations pour affecter les opérations aux stations
    assignOperationsToStations(operations, num_operations, exclusions, numExclusions);




    // Libérer la mémoire allouée
    free(filename);
    free(exclusions);

    char pourPause[20];
    gets(pourPause);

    return 0;
}