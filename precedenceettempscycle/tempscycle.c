//
// Created by elise on 02/12/2023.
//
#include <stdio.h>
#include "tempscycle.h"

double readTempsCycle() {
    // Ouvrir le fichier en mode lecture
    FILE *file = fopen("tempscycle.txt", "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return -1.0;  // Valeur par défaut en cas d'erreur
    }

    // Lire la durée du temps de cycle
    double tempsCycle;
    if (fscanf(file, "%lf", &tempsCycle) != 1) {
        fprintf(stderr, "Format incorrect dans le fichier\n");
        fclose(file);
        return -1.0;  // Valeur par défaut en cas d'erreur
    }

    // Fermer le fichier
    fclose(file);

    return tempsCycle;
}