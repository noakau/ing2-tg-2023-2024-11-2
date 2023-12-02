#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "C:\Users\Noa\CLionProjects\ing2\ProjetTDG\exclusion_TempsdeCycle\cmake-build-debug\temps_cycle.h"

#include "C:\Users\Noa\CLionProjects\ing2\ProjetTDG\exclusion_TempsdeCycle\cmake-build-debug\exclusion.h"
//permet de compter le temps d'une operation précise de la station
double getTimingOfOperation(int operation, Operation** all_operations, int nb_op){
    double ExecutionTimeForOp;
    for (int i=0; i<nb_op; i++){
        if ((*all_operations)[i].operation==operation){
            ExecutionTimeForOp= (*all_operations)[i].execution_time;
        }
    }
    return ExecutionTimeForOp;
}
//permet de calculer le temps d'une stations
double calculateStationCycleTime(Station* station, Operation** all_operations, int nb_operation) {
    double cycle_time = 0.0;

    for (int i = 0; i < station->nb_operations; i++) {
        int opIndex = station->operations[i];
        cycle_time += getTimingOfOperation(opIndex,all_operations,nb_operation);
    }
    return cycle_time;
}


int main() {
    // Demander à l'utilisateur le nom du fichier texte d'exclusion

    printf("Veuillez entrer le nom du fichier d'exclusions : \n ");

    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char* Exclusionfilename = (char*)malloc(100 * sizeof(char));

    // Vérifier si l'allocation de mémoire a réussi
    if (Exclusionfilename == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    strcpy(Exclusionfilename,"exclusion.txt"); //pour faciliter les tests
    // Lire le nom du fichier à partir de l'utilisateur
    //scanf("%s", filename);
    //filename="exclusion.txt";

    // Charger les exclusions à partir du fichier texte
    Exclusion* exclusions = NULL;
    int numExclusions = readExclusions(Exclusionfilename, &exclusions);

    printf("entrez deux operations a verifier:\n");
    int op1;
    int op2;
    scanf ("%d %d", &op1, &op2);
    int resultat = canAssign(op1, op2,exclusions, numExclusions );
    if (resultat ==1){
        printf(" ces operations peuvent etre  dans la meme station.\n");
        gets(Exclusionfilename);
    }
    else {
        printf(" ces operations ne peuvent pas etre  dans la meme station.\n");
        gets(Exclusionfilename);
    }

    // Lire les opérations
    Operation *operations;
    int total_operations;
    char* operationfilename = (char*)malloc(100 * sizeof(char));
    printf("Veuillez entrer le nom du fichier d'operations : \n ");
    //scanf("%s", operationfilename);
    strcpy(operationfilename,"exclusion.txt");
    total_operations = readOperations(&operations, operationfilename);

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
    int* operationsDansStation = NULL;
    int num_operations = 0;

    getDistinctOperations(exclusions, numExclusions, &operationsDansStation, &num_operations);
    Station **Workstation;
    int* nbStations;

    // Utilisez maintenant le tableau operations pour affecter les opérations aux stations
    Workstation=assignOperationsToStations(operationsDansStation, num_operations, exclusions, numExclusions, &nbStations);
    printf("il y a %d stations",  nbStations);
    gets(Exclusionfilename);

    double StationTime= calculateStationCycleTime( Workstation[0], &operations, total_operations);
    printf("temps de stations 0: %.8f", StationTime);
    gets(Exclusionfilename);
    free(operationsDansStation);

    // Vérifier la contrainte de temps de cycle
   for (int k = 0; k < nbStations; k++) {
        double total_duration = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if ((*Workstation)->operations[k] == k) {
                total_duration += operations[j].execution_time;
            }
        }

        if (total_duration > tempsCycle) {
            fprintf(stderr, "Contrainte de temps de cycle violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }

    // Vérifier la contrainte de temps par station
    for (int k = 0; k < nbStations; k++) {
        double total_duration_station = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if ((*Workstation)->operations[k] == k) {
                total_duration_station += operations[j].execution_time;
            }
        }

        // Vérifier que le temps total pour la station k est inférieur à 10 secondes
        if (total_duration_station > 10.0) {
            fprintf(stderr, "Contrainte de temps par station violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }


    printf("Temps de cycle : %.2f secondes\n", tempsCycle);
    gets(Exclusionfilename);

    return EXIT_SUCCESS;
}