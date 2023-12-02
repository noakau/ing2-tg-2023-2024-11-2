//
// Created by elise on 22/11/2023.
//

#ifndef OPERATIONSPROJETTDG_OPERATIONS_H
#define OPERATIONSPROJETTDG_OPERATIONS_H

typedef struct {
    int operation_number;
    double execution_time;
    int assigned_station;  // Nouveau champ pour stocker la station attribuée
} Operation;

int readOperations(Operation **operations, int *total_stations);

#endif //OPERATIONSPROJETTDG_OPERATIONS_H
