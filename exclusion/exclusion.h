//
// Created by elise on 29/11/2023.
//

#ifndef EXCLUSION_EXClUSION_H
#define EXCLUSION_EXClUSION_H

#define MAX_OPERATIONS 35

typedef struct {
    int operation;
    int station;
} Assignment;

int isExclusionViolated(int operations[MAX_OPERATIONS][2], int numOperations, int station[MAX_OPERATIONS], int op1, int op2);

void printExclusionConstraints(int operations[MAX_OPERATIONS][2], int numOperations);

void assignOperationsExclusion(int operations[MAX_OPERATIONS][2], int numOperations, Assignment assignments[MAX_OPERATIONS]);


#endif //EXCLUSION_EXClUSION_H
