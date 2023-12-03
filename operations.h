//
// Created by jules on 02/12/23.
//

#ifndef TEMPS_DE_CYCLE_OPERATIONS_H
#define TEMPS_DE_CYCLE_OPERATIONS_H
typedef struct {
    int operation_number;
    double execution_time;
    int assigned_station;  // Nouveau champ pour stocker la station attribuée
} Operation;

int readOperations(Operation **operations, int *total_stations);

#endif //TEMPS_DE_CYCLE_OPERATIONS_H
