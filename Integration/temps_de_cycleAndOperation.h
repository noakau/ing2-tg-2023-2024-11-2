//
// Created by Noa on 03/12/2023.
//

#ifndef INTEGRATION_TEMPS_DE_CYCLEANDOPERATION_H
#define INTEGRATION_TEMPS_DE_CYCLEANDOPERATION_H
typedef struct {
    int operation;
    double execution_time;
    int assigned_station;  // Nouveau champ pour stocker la station attribuée
} Operation;

double readTempsCycle(char*TimeFilename);
int readOperations(Operation **operations, int *total_stations,char*OperationFilename);
#endif //INTEGRATION_TEMPS_DE_CYCLEANDOPERATION_H
