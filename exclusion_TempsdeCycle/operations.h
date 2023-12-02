//
// Created by Noa on 02/12/2023.
//

#ifndef EXCLUSION_TEMPSDECYCLE_OPERATIONS_H
#define EXCLUSION_TEMPSDECYCLE_OPERATIONS_H
typedef struct {
    int operation;
    double execution_time;
} Operation;


int readOperations(Operation **operations, int *total_stations);

#endif //EXCLUSION_TEMPSDECYCLE_OPERATIONS_H
