#include <stdio.h>
#include "exclusion.h"

int main() {
    FILE *exclusionsFile = fopen("exclusion.txt", "r");
    if (exclusionsFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier texte");
        return 1;
    }

    int operations[MAX_OPERATIONS][2];
    int numOperations = 0;

    while (fscanf(exclusionsFile, "%d %d", &operations[numOperations][0], &operations[numOperations][1]) == 2) {
        numOperations++;
    }

    // Supposons que vous avez une fonction pour lire les affectations de stations, ou implémentez-la ici
    int station[MAX_OPERATIONS]; // Array to store station assignments for each operation

    // Afficher toutes les contraintes d'exclusion
    printExclusionConstraints(operations, numOperations);

    // Vérifier les contraintes d'exclusion
    int op1, op2;
    printf("Entrez deux operations pour verifier la contrainte d'exclusion : ");
    scanf("%d %d", &op1, &op2);

    if (isExclusionViolated(operations, numOperations, station, op1, op2)) {
        printf("Contrainte d'exclusion violee\n");
    } else {
        printf("Contrainte d'exclusion non violee\n");
    }

    Assignment assignments[MAX_OPERATIONS];

    // Proposer une répartition en respectant la contrainte d'exclusion
    assignOperationsExclusion(operations, numOperations, assignments);

    // Afficher la répartition proposée
    printf("Repartition par station :\n");
    for (int i = 0; i < numOperations; i++) {
        printf("Operation %d -> Station %d\n", assignments[i].operation + 1, assignments[i].station + 1);
    }

    return 0;
}1