//
// Created by elise on 02/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

int readOperations(Operation **operations, int *total_stations) {
    // Ouvrir le fichier en mode lecture
    FILE *file = fopen("operation.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    // Lire le nombre total d'opérations et de stations
    int total_operations = 0, max_station = 0;
    while (fscanf(file, "%*d %*f\n") != EOF) {
        total_operations++;
    }

    // Réinitialiser le curseur du fichier à la position initiale
    rewind(file);

    // Allouer de l'espace pour stocker les opérations
    *operations = malloc(total_operations * sizeof(Operation));
    if (*operations == NULL) {
        perror("Erreur lors de l'allocation de memoire");
        fclose(file);
        return -1;
    }

    // Lire chaque ligne du fichier et stocker les données dans la structure Operation
    for (int i = 0; i < total_operations; i++) {
        if (fscanf(file, "%d %lf\n", &((*operations)[i].operation_number), &((*operations)[i].execution_time)) != 2) {
            fprintf(stderr, "Format de ligne incorrect dans le fichier\n");
            free(*operations);
            fclose(file);
            return -1;
        }

        // Assigner une station temporaire à chaque opération (ajustée pour commencer à 1)
        (*operations)[i].assigned_station = (i % 2) + 1;  // Commencer à partir de la station 1
        if ((*operations)[i].assigned_station > max_station) {
            max_station = (*operations)[i].assigned_station;
        }
    }

    // Fermer le fichier
    fclose(file);

    // Retourner le nombre total d'opérations et le nombre total de stations
    *total_stations = max_station;
    return total_operations;
}