//
// Created by elise on 02/12/2023.
//

#ifndef PRECEDENCEETTEMPSCYCLE_OPERATION_H
#define PRECEDENCEETTEMPSCYCLE_OPERATION_H

typedef struct {
    int operation_number;
    double execution_time;
    int assigned_station;  // Nouveau champ pour stocker la station attribuée
} Operation;

int readOperations(Operation **operations, int *total_stations);

#endif //PRECEDENCEETTEMPSCYCLE_OPERATION_H
