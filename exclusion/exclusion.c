//
// Created by elise on 29/11/2023.
//

#include <stdio.h>
#include "exclusion.h"

int isExclusionViolated(int operations[MAX_OPERATIONS][2], int numOperations, int station[MAX_OPERATIONS], int op1, int op2) {
    for (int i = 0; i < numOperations; i++) {
        if ((station[op1] == station[operations[i][0]] && station[op2] == station[operations[i][1]]) ||
            (station[op1] == station[operations[i][1]] && station[op2] == station[operations[i][0]])) {
            return 1; // Contrainte d'exclusion violée
        }
    }
    return 0; // Contrainte d'exclusion non violée
}

void printExclusionConstraints(int operations[MAX_OPERATIONS][2], int numOperations) {
    printf("Contraintes d'exclusion :\n");
    for (int i = 0; i < numOperations; i++) {
        printf("%d %d\n", operations[i][0], operations[i][1]);
    }
}

void assignOperationsExclusion(int operations[MAX_OPERATIONS][2], int numOperations, Assignment assignments[MAX_OPERATIONS]) {
    // Assignation simple pour l'exemple
    for (int i = 0; i < numOperations; i++) {
        assignments[i].operation = i;
        assignments[i].station = i % 3; // Assignation à une station arbitraire, à ajuster selon vos besoins
    }
}