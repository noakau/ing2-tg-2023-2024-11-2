//
// Created by Noa on 02/12/2023.
//
#include "exclusion.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int canAssign(int operation1, int operation2, Exclusion* exclusions, int numExclusions) {
    //printf("Oprations : %d, %d\n", operation1, operation2);

    // Vérifiez si l'opération est en conflit avec une autre opération dans les contraintes d'exclusion
    for (int j = 0; j < numExclusions; j++) {
        //printf("Exclusion %d : %d, %d\n", j, exclusions[j].operation1, exclusions[j].operation2);
        if ((exclusions[j].operation1 == operation1 && exclusions[j].operation2 == operation2) ||
            (exclusions[j].operation1 == operation2 && exclusions[j].operation2 == operation1)) {
            return 0; // Les opérations sont en conflit, ne peuvent pas être affectées à la même station
        }
    }

    return 1; // Les opérations peuvent être affectées à la même station
}

// Fonction pour lire les exclusions à partir d'un fichier texte
int readExclusions(char* filename, Exclusion** exclusions) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int numExclusions = 0;
    int ope1 =0;
    int ope2 = 0;

    // Trouver le nombre total d'exclusions
    while (fscanf(file, "%d %d", &ope1, &ope2) == 2) {
        numExclusions++;
    }

    // Allouer de la mémoire pour le tableau d'exclusions
    *exclusions = (Exclusion*)malloc(numExclusions * sizeof(Exclusion));

    // Réinitialiser la position du curseur dans le fichier
    fseek(file, 0, SEEK_SET);

    // Lire les exclusions du fichier
    printf("Exclusions lues :\n");
    for (int i = 0; i < numExclusions; i++) {
        if (fscanf(file, "%d %d", &(*exclusions)[i].operation1, &(*exclusions)[i].operation2) != 2) { // ici on execute tout de mêm le stockage des exclusions dans le tableau grâce au if
            fprintf(stderr, "Erreur lors de la lecture des exclusions depuis le fichier.\n");
            exit(EXIT_FAILURE);
        }

        // Afficher les exclusions
        printf("%d %d\n", (*exclusions)[i].operation1, (*exclusions)[i].operation2);

    }

    fclose(file);

    return numExclusions;
}

int isOperationInArray(int operation, int* array, int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] == operation) {
            return 1;
        }
    }
    return 0;
}

void getDistinctOperations(Exclusion* exclusions, int num_exclusions, int** operations, int* num_operations) {
    // Utiliser un tableau dynamique pour stocker les opérations distinctes
    int* distinctOperations = NULL;
    int numDistinctOperations = 0;

    for (int i = 0; i < num_exclusions; i++) {
        if (!isOperationInArray(exclusions[i].operation1, distinctOperations, numDistinctOperations)) {

            distinctOperations = (int*)realloc(distinctOperations, (numDistinctOperations + 1) * sizeof(int));
            distinctOperations[numDistinctOperations++] = exclusions[i].operation1;
        }

        if (!isOperationInArray(exclusions[i].operation2, distinctOperations, numDistinctOperations)) {

            distinctOperations = (int*)realloc(distinctOperations, (numDistinctOperations + 1) * sizeof(int));
            distinctOperations[numDistinctOperations++] = exclusions[i].operation2;
        }
    }

    *operations = distinctOperations;
    *num_operations = numDistinctOperations;
}

Station** assignOperationsToStations(int* operations, int num_operations, Exclusion* exclusions, int numExclusions,int * NombreDeStationUtilisees) {
    int nbStations=0;
    // Initialiser le tableau des stations
    Station** stations = NULL;

    for (int i = 0; i < num_operations; i++) {
        int assigned = 0;

        // Essayer d'assigner l'opération à une station existante
        for (int j = 0; j < nbStations; j++) {
            int canBeAssigned = 1;

            // Vérifier les exclusions avec les opérations déjà assignées à la station
            for (int k = 0; k < stations[j]->nb_operations; k++) {
                if (!canAssign(operations[i], stations[j]->operations[k], exclusions, numExclusions)) {
                    canBeAssigned = 0;
                    break;
                }
            }

            if (canBeAssigned) { // si on peut assigner cette opérations à la même station
                // Assigner l'opération à la station existante
                stations[j]->operations = (int*)realloc(stations[j]->operations, (stations[j]->nb_operations + 1) * sizeof(int)); //on realloue la mémoire avec la bonne taille
                stations[j]->operations[stations[j]->nb_operations] = operations[i];
                stations[j]->nb_operations++;
                assigned = 1;
                break;
            }
        }

        if (!assigned) { // si nous n'avons pas reussi a assigné l'operation à une station
            // on crée une nouvelle station et y assigne l'opération
           nbStations++;
            Station* sa  = (Station*) malloc(sizeof (Station));
            sa->operations = (int*)malloc(sizeof(int));
            sa->operations[0] = operations[i];
            sa->nb_operations = 1;

            stations = (Station*)realloc(stations, nbStations * sizeof(Station));
            stations[nbStations-1] = sa;
        }
    }

    // Afficher les résultats
    for (int i = 0; i < nbStations; i++) {
        printf("Station %d : ", i + 1);
        for (int j = 0; j < stations[i]->nb_operations; j++) {
            printf("%d ", stations[i]->operations[j]);
        }
        printf("\n");
    }

    *NombreDeStationUtilisees = nbStations;
    return stations;
}