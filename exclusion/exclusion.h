//
// Created by Noa on 26/11/2023.
//

#ifndef EXCLUSION_EXCLUSION_H
#define EXCLUSION_EXCLUSION_H
//structure de station contenant les opérations
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
void assignOperationsToStations(int* operations, int num_operations, Exclusion* exclusions, int numExclusions);
#endif //EXCLUSION_EXCLUSION_H


