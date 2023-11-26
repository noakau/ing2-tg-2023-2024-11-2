#include <stdio.h>
#include <stdlib.h>
#include "operations.h"
#include "temps_cycle.h"

int main() {
    // Lire les opérations
    Operation *operations;
    int total_operations, total_stations;
    total_operations = readOperations(&operations, &total_stations);

    if (total_operations <= 0) {
        fprintf(stderr, "Erreur lors de la lecture des operations\n");
        return EXIT_FAILURE;
    }

    // Lire la durée du temps de cycle
    double tempsCycle = readTempsCycle();
    if (tempsCycle < 0.0) {
        fprintf(stderr, "Erreur lors de la lecture du temps de cycle\n");
        free(operations);
        return EXIT_FAILURE;
    }

    // Vérifier la contrainte de temps de cycle
    for (int k = 0; k < total_stations; k++) {
        double total_duration = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if (operations[j].assigned_station == k) {
                total_duration += operations[j].execution_time;
            }
        }

        if (total_duration > tempsCycle) {
            fprintf(stderr, "Contrainte de temps de cycle violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }

    // Vérifier la contrainte de temps par station
    for (int k = 0; k < total_stations; k++) {
        double total_duration_station = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if (operations[j].assigned_station == k) {
                total_duration_station += operations[j].execution_time;
            }
        }

        // Vérifier que le temps total pour la station k est inférieur à 10 secondes
        if (total_duration_station > 10.0) {
            fprintf(stderr, "Contrainte de temps par station violée pour la station %d\n", k);
            free(operations);
            return EXIT_FAILURE;
        }
    }

    // Afficher les données lues
    printf("Operations lues :\n");
    for (int i = 0; i < total_operations; i++) {
        printf("Operation : %d, Temps d'execution : %.2f, Station : %d\n", operations[i].operation_number, operations[i].execution_time, operations[i].assigned_station);
    }

    printf("Temps de cycle : %.2f secondes\n", tempsCycle);

    // Libérer la mémoire
    free(operations);

    return EXIT_SUCCESS;
}