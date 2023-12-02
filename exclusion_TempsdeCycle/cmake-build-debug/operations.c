//
// Created by Noa on 02/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "..\operations.h"

int readOperations(Operation **operations, char*OperationFilename) {
    // Ouvrir le fichier en mode lecture
    FILE *file = fopen(OperationFilename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1;
    }

    // Lire le nombre total d'opérations et de stations
    int total_operations, max_station = 0;
    while (fscanf(file, "%*d %*f\n") != EOF) {
        total_operations++;
    }

    // Réinitialiser le curseur du fichier à la position initiale
    rewind(file);

    // Allouer de l'espace pour stocker les opérations
    *operations = malloc(total_operations * sizeof(Operation));
    if (*operations == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        fclose(file);
        return -1;
    }

    // Lire chaque ligne du fichier et stocker les données dans la structure Operation
    for (int i = 0; i < total_operations; i++) {
        if (fscanf(file, "%d %lf\n", &((*operations)[i].operation), &((*operations)[i].execution_time)) != 2) {
            fprintf(stderr, "Format de ligne incorrect dans le fichier\n");
            free(*operations);
            fclose(file);
            return -1;
        }
    }
    // Fermer le fichier
    fclose(file);
    return total_operations;
}