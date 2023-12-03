//
// Created by elise on 03/12/2023.
//

#ifndef EXCLUSIONETPRCEDENCE_OPERATION_H
#define EXCLUSIONETPRCEDENCE_OPERATION_H
typedef struct {
    int operation_number;
    double execution_time;
    int assigned_station;  // Nouveau champ pour stocker la station attribuée
} Operation;

int readOperations(Operation **operations, int *total_stations);

#endif //EXCLUSIONETPRCEDENCE_OPERATION_H
