//
// Created by Noa on 03/12/2023.
//

#ifndef INTEGRATION_EXCLUSION_H
#define INTEGRATION_EXCLUSION_H
typedef struct {
    int* operations;
    int nb_operations;
} Station;

//structure d'exclusions de teux opérations
typedef struct {
    int operation1;
    int operation2;
} Exclusion;

int canAssign(int operation1, int operation2, Exclusion* exclusions, int numExclusions);
int readExclusions(char* filename, Exclusion** exclusions);
int isOperationInArray(int operation, int* array, int size);
void getDistinctOperations(Exclusion* exclusions, int num_exclusions, int** operations, int* num_operations);
Station** assignOperationsToStations(int* operations, int num_operations, Exclusion* exclusions, int numExclusions,int * NombreDeStationUtilisees);

#endif //INTEGRATION_EXCLUSION_H
