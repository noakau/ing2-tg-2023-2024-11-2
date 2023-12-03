//
// Created by elise on 02/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "precedence.h"

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


// Fonction utilitaire pour calculer les degrés entrants des opérations
static void calculerDegresEntrants(Graphe* graphe, int* inDegrees, int total_operations) {
    for (int i = 0; i < total_operations; i++) {
        inDegrees[i] = 0;
    }

    for (int i = 0; i < graphe->numAretes; i++) {
        int vers = graphe->aretes[i].vers;
        inDegrees[vers]++;
    }
}

// Fonction utilitaire pour libérer la mémoire utilisée par le tri topologique
static void libererTriTopologique(int* order) {
    free(order);
}

// Function to perform topological sort and return the order of operations
int* ordonnerOperations(Graphe* graphe, Operation* operations, int total_operations) {
    int* order = (int*)malloc(total_operations * sizeof(int));
    if (order == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        return NULL;
    }

    // Calculate in-degrees for each operation
    int* inDegrees = (int*)calloc(total_operations, sizeof(int));
    if (inDegrees == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        free(order);
        return NULL;
    }

    for (int i = 0; i < graphe->numAretes; i++) {
        int vers = graphe->aretes[i].vers;
        inDegrees[vers]++;
    }

    // Initialize a queue for operations with in-degree 0
    int* queue = (int*)malloc(total_operations * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < total_operations; i++) {
        if (inDegrees[i] == 0) {
            queue[rear] = i;
            rear++;
        }
    }

    // Perform topological sort
    int orderIndex = 0;
    while (front < rear) {
        int currentOperation = queue[front];
        order[orderIndex] = currentOperation;
        orderIndex++;

        for (int i = 0; i < graphe->numAretes; i++) {
            if (graphe->aretes[i].de == currentOperation) {
                int vers = graphe->aretes[i].vers;
                inDegrees[vers]--;

                if (inDegrees[vers] == 0) {
                    queue[rear] = vers;
                    rear++;
                }
            }
        }

        front++;
    }

    // Check for a cycle in the graph (inconsistent precedence constraints)
    if (orderIndex != total_operations) {
        fprintf(stderr, "Erreur : Le graphe a un cycle (contraintes de précédence incohérentes)\n");
        free(order);
        free(queue);
        free(inDegrees);
        return NULL; // There is a cycle, return NULL
    }

    // Free allocated memory
    free(queue);
    free(inDegrees);

    return order;
}

