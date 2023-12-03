//
// Created by elise on 02/12/2023.
//

#ifndef PRECEDENCEETTEMPSCYCLE_OPERATION_H
#define PRECEDENCEETTEMPSCYCLE_OPERATION_H
#include "precedence.h"

// Définition de la structure Operation (à ajuster selon votre code)
typedef struct {
    int operation_number;
    double execution_time;
    int assigned_station;
} Operation;

int readOperations(Operation **operations, int *total_stations);
int* ordonnerOperations(Graphe* graphe, Operation* operations, int total_operations);


#endif //PRECEDENCEETTEMPSCYCLE_OPERATION_H
