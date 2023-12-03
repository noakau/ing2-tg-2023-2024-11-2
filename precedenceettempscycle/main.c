#include <stdio.h>
#include <stdlib.h>
#include "operation.h"
#include "tempscycle.h"
#include "precedence.h"

int main() {
    Graphe graphe = lireContraintesPrecedence("precedence.txt");

    if (graphe.numAretes == 0) {
        printf("Aucune contrainte de précédence trouvée\n");
        return 1;  // Retourner un code d'erreur
    }

    afficherContraintesPrecedence(&graphe);

    double tempsCycle;
    tempsCycle = readTempsCycle();
    if (tempsCycle <= 0.0) {
        fprintf(stderr, "Erreur : Le temps de cycle doit être une valeur positive\n");
        return EXIT_FAILURE;
    }

    Operation *operations;
    int total_operations, total_stations;

    total_operations = readOperations(&operations, &total_stations);

    if (total_operations <= 0) {
        fprintf(stderr, "Erreur lors de la lecture des operations\n");
        libererGraphe(&graphe);
        return EXIT_FAILURE;
    }

    // Vérifier la contrainte de temps par station
    for (int k = 0; k < total_stations; k++) {
        double total_duration_station = 0.0;
        for (int j = 0; j < total_operations; j++) {
            if (operations[j].assigned_station == k) {
                total_duration_station += operations[j].execution_time;
            }
        }

        // Vérifier que le temps total pour la station k est inférieur au temps de cycle
        if (total_duration_station > tempsCycle) {
            fprintf(stderr, "Contrainte de temps par station violée pour la station %d\n", k);
            free(operations);
            libererGraphe(&graphe);
            return EXIT_FAILURE;
        }
    }

    int *operationOrder = ordonnerOperations(&graphe, operations, total_operations);
    if (operationOrder == NULL) {
        fprintf(stderr, "Erreur lors de l'ordonnancement des opérations\n");
        free(operations);
        libererGraphe(&graphe);
        return EXIT_FAILURE;
    }

    // Répartition des opérations dans les stations
    int *stationDurations = (int *)calloc(total_stations, sizeof(int));
    int stationIndex = 0;

    for (int i = 0; i < total_operations; i++) {
        int operationIndex = operationOrder[i];
        int currentStation = stationIndex % total_stations;

        // Vérifier si le temps total de la station dépasse le temps de cycle
        if ((int)(stationDurations[currentStation] + operations[operationIndex].execution_time) > (int)tempsCycle) {
            // Créer une nouvelle station si nécessaire
            stationIndex++;
            currentStation = stationIndex % total_stations;
        }

        // Affecter l'opération à la station actuelle
        operations[operationIndex].assigned_station = currentStation;
        stationDurations[currentStation] += operations[operationIndex].execution_time;
    }

    // Afficher les opérations ordonnées et réparties dans les stations
    printf("Operations ordonnees et reparties dans les stations :\n");
    for (int i = 0; i < total_operations; i++) {
        int index = operationOrder[i];
        printf("Operation : %d, Temps d'execution : %.2f, Station : %d\n",
               operations[index].operation_number, operations[index].execution_time,
               operations[index].assigned_station);
    }

    printf("Temps de cycle : %.2f secondes\n", tempsCycle);

    // Libérer la mémoire
    free(operationOrder);
    free(stationDurations);
    free(operations);
    libererGraphe(&graphe);

    return 0;
}
