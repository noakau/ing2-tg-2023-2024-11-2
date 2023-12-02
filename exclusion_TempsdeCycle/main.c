#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "C:\Users\Noa\CLionProjects\ing2\ProjetTDG\exclusion_TempsdeCycle\cmake-build-debug\temps_cycle.h"

#include "C:\Users\Noa\CLionProjects\ing2\ProjetTDG\exclusion_TempsdeCycle\cmake-build-debug\exclusion.h"


int main() {
    // Lire les opérations
    Operation *operations;
    int total_operations, total_stations;
    total_operations = readOperations(&operations, &total_stations);

    if (total_operations <= 0) {
        fprintf(stderr, "Erreur lors de la lecture des operation\n");
        return EXIT_FAILURE;
    }

    // Lire la durée du temps de cycle
    double tempsCycle = readTempsCycle();
    if (tempsCycle < 0.0) {
        fprintf(stderr, "Erreur lors de la lecture du temps de cycle\n");
        free(operations);
        return EXIT_FAILURE;
    }

    // Vérifier la contrainte de temps de cycle
   /*for (int k = 0; k < total_stations; k++) {
        double total_duration = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if (operations[j].assigned_station == k) {
                total_duration += operations[j].execution_time;
            }
        }

        if (total_duration > tempsCycle) {
            fprintf(stderr, "Contrainte de temps de cycle violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }*/

    // Vérifier la contrainte de temps par station
    /*for (int k = 0; k < total_stations; k++) {
        double total_duration_station = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if (operations[j].assigned_station == k) {
                total_duration_station += operations[j].execution_time;
            }
        }

        // Vérifier que le temps total pour la station k est inférieur à 10 secondes
        if (total_duration_station > 10.0) {
            fprintf(stderr, "Contrainte de temps par station violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }*/


   printf("Temps de cycle : %.2f secondes\n", tempsCycle);


// Demander à l'utilisateur le nom du fichier texte

     printf("Veuillez entrer le nom du fichier texte : \n ");

    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char* filename = (char*)malloc(100 * sizeof(char));

    // Vérifier si l'allocation de mémoire a réussi
    if (filename == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }




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

    int* operationsDansStation = NULL;
    int num_operations = 0;

    getDistinctOperations(exclusions, numExclusions, &operationsDansStation, &num_operations);

    // Utilisez maintenant le tableau operations pour affecter les opérations aux stations
    assignOperationsToStations(operationsDansStation, num_operations, exclusions, numExclusions);
    gets(filename);


    // Libérer la mémoire
    free(operationsDansStation);

    return EXIT_SUCCESS;
}