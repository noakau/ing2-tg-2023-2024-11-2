//
// Created by Noa on 02/12/2023.
//
#include <stdio.h>
#include "temps_cycle.h"

double readTempsCycle() {
    // Ouvrir le fichier en mode lecture
    FILE *file = fopen("temps_cycle.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier temps_cycle.txt");
        return -1.0;  // Valeur par défaut en cas d'erreur
    }

    // Lire la durée du temps de cycle
    double tempsCycle;
    if (fscanf(file, "%lf", &tempsCycle) != 1) {
        fprintf(stderr, "Format incorrect dans le fichier temps_cycle.txt\n");
        fclose(file);
        return -1.0;  // Valeur par défaut en cas d'erreur
    }

    // Fermer le fichier
    fclose(file);

    return tempsCycle;
}