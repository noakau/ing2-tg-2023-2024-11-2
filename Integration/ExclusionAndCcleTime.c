#include "exclusion.h"
#include "temps_de_cycleAndOperation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Created by Noa on 03/12/2023.
//
double getTimingOfOperation(int operation, Operation** all_operations, int nb_op){
    double ExecutionTimeForOp;
    for (int i=0; i<nb_op; i++){
        if ((*all_operations)[i].operation==operation){
            ExecutionTimeForOp= (*all_operations)[i].execution_time;
        }
    }
    return ExecutionTimeForOp;
}

//permet de calculer le temps d'une stations
double calculateStationCycleTime(Station* station, Operation** all_operations, int nb_operation) {
    double cycle_time = 0.0;

    for (int i = 0; i < station->nb_operations; i++) {
        int opIndex = station->operations[i];
        cycle_time += getTimingOfOperation(opIndex,all_operations,nb_operation);
    }
    return cycle_time;
}

// calcule le temps max de toutes les stations
double CalculateMaxStationCycleTime(Station** worksations, int  nbStations, Operation** all_operations, int nb_operation){
    double TimeperStations =0;
    double MaxTemp=0;
    for(int i =0; i< nbStations; i++){
        TimeperStations = calculateStationCycleTime(worksations[i],  all_operations,  nb_operation);
        if(TimeperStations>MaxTemp){
            MaxTemp = TimeperStations;
        }
    }
    return TimeperStations;
}


Station** AssignOpToStationsGivenExclusionAndTiming(Operation* operations, int num_operations, Exclusion* exclusions, int numExclusions, double cycleTime, int* NombreDeStationUtilisees) {
    int nbStations = 0;
    Station** stations = NULL;
    double* stationTimes = NULL;

    for (int i = 0; i < num_operations; i++) {
        int assigned = 0;

        for (int j = 0; j < nbStations; j++) {
            int canBeAssigned = 1;

            // Check if the time of the station is less than the cycleTime
            if (stationTimes[j] >= cycleTime) {
                canBeAssigned = 0;
            }

            // Check exclusions with operations already assigned to the station
            for (int k = 0; k < stations[j]->nb_operations; k++) {
                if (!canAssign(operations[i].operation, stations[j]->operations[k], exclusions, numExclusions)) {
                    canBeAssigned = 0;
                    break;
                }
            }

            if (canBeAssigned) {
                // Check if assigning the operation will exceed the cycle time
                if ((stationTimes[j] + calculateStationCycleTime(stations[j], &operations, num_operations)) <= cycleTime) {
                    // Assign the operation to the station
                    stations[j]->operations = (int*)realloc(stations[j]->operations, (stations[j]->nb_operations + 1) * sizeof(int));
                    stations[j]->operations[stations[j]->nb_operations] = operations[i].operation;
                    stations[j]->nb_operations++;
                    stationTimes[j] += calculateStationCycleTime(stations[j], &operations, num_operations);  // Update station time
                    assigned = 1;
                    break;
                }
            }
        }

        if (!assigned) {
            // Create a new station and assign the operation
            nbStations++;
            Station* sa = (Station*)malloc(sizeof(Station));
            sa->operations = (int*)malloc(sizeof(int));
            sa->operations[0] = operations[i].operation;
            sa->nb_operations = 1;

            // Allocate memory for the station time array
            stationTimes = (double*)realloc(stationTimes, nbStations * sizeof(double));
            stationTimes[nbStations - 1] = calculateStationCycleTime(sa, &operations, num_operations);  // Set initial station time

            // Allocate memory for the stations array
            stations = (Station**)realloc(stations, nbStations * sizeof(Station*));
            stations[nbStations - 1] = sa;
        }
    }

    // Update the output parameter with the number of used stations
    NombreDeStationUtilisees = nbStations;

    // Free the memory for the station time array
    //free(stationTimes);
    // Display stations and their details

// Display stations and their details
    printf("\nStations and their details:\n");
    for (int i = 0; i < nbStations; i++) {
        double stationTime = 0.0;
        printf("Station %d (Time: %.2lf): ", i + 1, stationTimes[i]);

        for (int j = 0; j < stations[i]->nb_operations; j++) {
            int opIndex = stations[i]->operations[j];
            double opTime = getTimingOfOperation(opIndex, operations, num_operations);
            printf("%d ", opIndex);
            stationTime += opTime;
        }

        printf("\n");

        // Update the station time after processing all operations
        stationTimes[i] = stationTime;
    }
// ...
    return stations;
}