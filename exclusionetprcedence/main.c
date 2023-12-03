#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exclusion.h"
#include "precedence.h"
#include "operation.h"

// Déclaration de la fonction isEdge
int isEdge(const Graphe *graphe, int de, int vers);
// Définition de la fonction pour ajuster les stations en tenant compte des contraintes de précédence
void adjustStationsWithPrecedence(Operation *operations, int total_operations, Graphe *precedenceGraph) {
    // Parcourir les contraintes de précédence
    for (int i = 0; i < total_operations; i++) {
        for (int j = 0; j < i; j++) {
            if (isEdge(precedenceGraph, operations[j].operation_number, operations[i].operation_number)) {
                // L'opération précédente doit être dans une station inférieure
                if (operations[j].assigned_station >= operations[i].assigned_station) {
                    operations[i].assigned_station = operations[j].assigned_station + 1;
                }
            }
        }
    }
}
void assignOperationsWithConstraints(Operation *operations, int total_operations,
                                     Exclusion *exclusions, int numExclusions,
                                     Graphe *precedenceGraph) {
    // Attribuer les opérations aux stations en tenant compte des contraintes d'exclusions et de précédences
    for (int i = 0; i < total_operations; i++) {
        int currentStation = 1;  // Commencer par la première station

        // Vérifier les contraintes d'exclusion pour cette opération
        for (int j = 0; j < numExclusions; j++) {
            if (operations[i].operation_number == exclusions[j].operation1 ||
                operations[i].operation_number == exclusions[j].operation2) {
                // Les opérations exclues ne peuvent pas être dans la même station
                currentStation++;
            }
        }

        // Vérifier les contraintes de précédence pour cette opération
        for (int j = 0; j < i; j++) {
            if (isEdge(precedenceGraph, operations[j].operation_number, operations[i].operation_number)) {
                // L'opération précédente doit être dans une station inférieure
                if (operations[j].assigned_station >= currentStation) {
                    currentStation = operations[j].assigned_station + 1;
                }
            }
        }

        // Attribuer la station à l'opération
        operations[i].assigned_station = currentStation;

        // Vous pouvez afficher les affectations ici si nécessaire
        printf("Operation : %d, Station : %d\n", operations[i].operation_number, operations[i].assigned_station);
    }
}

// Fonction pour afficher les stations et les opérations qui y sont assignées
void printStations(Operation *operations, int total_operations) {
    // Trouver le nombre total de stations
    int maxStation = 0;
    for (int i = 0; i < total_operations; i++) {
        if (operations[i].assigned_station > maxStation) {
            maxStation = operations[i].assigned_station;
        }
    }

    // Allouer un tableau pour chaque station
    Operation **stations = (Operation **)malloc((maxStation + 1) * sizeof(Operation *));
    for (int i = 0; i <= maxStation; i++) {
        stations[i] = (Operation *)malloc(total_operations * sizeof(Operation));
    }

    // Initialiser les tableaux de stations
    for (int i = 0; i <= maxStation; i++) {
        for (int j = 0; j < total_operations; j++) {
            stations[i][j].operation_number = -1;  // Valeur par défaut pour une opération non assignée
        }
    }

    // Remplir les tableaux de stations
    for (int i = 0; i < total_operations; i++) {
        int station = operations[i].assigned_station;
        int j = 0;
        while (stations[station][j].operation_number != -1) {
            j++;
        }
        stations[station][j] = operations[i];
    }

    // Afficher les stations et les opérations qui y sont assignées
    for (int i = 1; i <= maxStation; i++) {
        printf("Station %d : ", i);
        int j = 0;
        while (stations[i][j].operation_number != -1) {
            printf("%d ", stations[i][j].operation_number);
            j++;
        }
        printf("\n");
    }

    // Libérer la mémoire allouée pour les tableaux de stations
    for (int i = 0; i <= maxStation; i++) {
        free(stations[i]);
    }
    free(stations);
}

int main() {
    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char *filename = (char *)malloc(100 * sizeof(char));

    FILE *file = fopen("exclusion.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier texte");
        return 1;
    }

    // Obtenir le nom du fichier depuis l'utilisateur
    printf("Entrez le nom du fichier : ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne de fgets

    // Charger les exclusions à partir du fichier texte
    Exclusion *exclusions = NULL;
    int numExclusions = readExclusions(filename, &exclusions);

    printf("Entrez les stations a verifier :\n");
    int op1, op2;
    scanf("%d %d", &op1, &op2);

    int resultat = canAssign(op1, op2, exclusions, numExclusions);
    if (resultat == 1) {
        printf("\nCes operations peuvent etre dans la meme station.\n");
    } else {
        printf("\nCes operations ne peuvent pas etre dans la meme station.\n");
    }

    // Lire les opérations
    Operation *operations;
    int total_operations, total_stations;
    total_operations = readOperations(&operations, &total_stations);

    if (total_operations <= 0) {
        fprintf(stderr, "Erreur lors de la lecture des operations\n");
        return EXIT_FAILURE;
    }

// Lire les contraintes de précédence à partir du fichier
    Graphe precedenceGraph = lireContraintesPrecedence("precedence.txt");

// Vérifier si le graphe est vide (pas de contraintes)
    if (precedenceGraph.numAretes == 0) {
        printf("Aucune contrainte de précédence trouvée\n");
        return EXIT_FAILURE;  // Retourner un code d'erreur
    }

// Appeler la fonction pour assigner les opérations aux stations
    assignOperationsWithConstraints(operations, total_operations, exclusions, numExclusions, &precedenceGraph);

    // Appeler la fonction pour ajuster les stations en tenant compte des contraintes de précédence
    adjustStationsWithPrecedence(operations, total_operations, &precedenceGraph);

    // Afficher les opérations et les stations attribuées
    printf("Operations attribuees aux stations :\n");
    for (int i = 0; i < total_operations; i++) {
        printf("Operation : %d, Temps d'execution : %.2f, Station : %d\n",
               operations[i].operation_number, operations[i].execution_time, operations[i].assigned_station);
    }

    // Appeler la fonction pour afficher les stations et les opérations qui y sont assignées
    printStations(operations, total_operations);

    // Libérer la mémoire allouée pour le graphe de précédence
    libererGraphe(&precedenceGraph);
    // Libérer la mémoire allouée pour les opérations
    free(operations);

    return 0;
}
