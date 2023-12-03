//
// Created by Noa on 03/12/2023.
//

#ifndef INTEGRATION_EXCLUSIONANDCYCLETIME_H
#define INTEGRATION_EXCLUSIONANDCYCLETIME_H

#include "temps_de_cycleAndOperation.h"
#include "exclusion.h"

double getTimingOfOperation(int operation, Operation** all_operations, int nb_op);
double calculateStationCycleTime(Station* station, Operation** all_operations, int nb_operation);
double CalculateMaxStationCycleTime(Station** worksations, int  nbStations, Operation** all_operations, int nb_operation);
Station** AssignOpToStationsGivenExclusionAndTiming(Operation* operations, int num_operations, Exclusion* exclusions, int numExclusions, double cycleTime, int* NombreDeStationUtilisees);
#endif //INTEGRATION_EXCLUSIONANDCYCLETIME_H
