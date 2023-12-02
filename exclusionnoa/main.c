#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
typedef struct {
    int* operations;
    int num_operations;
} Station;


typedef struct {
    int operation1;
    int operation2;
} Exclusion;

// Fonction pour vérifier si deux opérations peuvent être affectées à la même station
int canAssign(int operation1, int operation2, int* stations, Exclusion* exclusions, int numExclusions) {
    // Vérifiez si l'opération est en conflit avec une autre opération dans les contraintes d'exclusion
    for (int j = 0; j < numExclusions; j++) {
        if ((exclusions[j].operation1 == operation1 && exclusions[j].operation2 == operation2) ||
            (exclusions[j].operation1 == operation2 && exclusions[j].operation2 == operation1)) {
            return 0; // Les opérations sont en conflit, ne peuvent pas être affectées à la même station
        }
    }

    // Vérifiez si les opérations ont la même couleur (même station)
    if (stations[operation1] == stations[operation2]) {
        return 0;
    }

    return 1; // Les opérations peuvent être affectées à la même station
}

// Fonction pour lire les exclusions à partir d'un fichier texte
int readExclusions(char* filename, Exclusion** exclusions) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int numExclusions = 0;

    // Trouver le nombre total d'exclusions
    while (fscanf(file, "%d %d", &(*exclusions)[numExclusions].operation1, &(*exclusions)[numExclusions].operation2) == 2) {
        numExclusions++;
    }

    fclose(file);

    // Allouer dynamiquement le tableau d'exclusions en fonction du nombre total d'exclusions
    *exclusions = (Exclusion*)malloc(numExclusions * sizeof(Exclusion));

    return numExclusions;
}

// Fonction pour trouver le numéro de station maximal
int findMaxStation(Exclusion* exclusions, int numExclusions) {
    int maxStation = 0;

    for (int i = 0; i < numExclusions; i++) {
        if (exclusions[i].operation1 > maxStation) {
            maxStation = exclusions[i].operation1;
        }
        if (exclusions[i].operation2 > maxStation) {
            maxStation = exclusions[i].operation2;
        }
    }

    return maxStation;
}

// Fonction pour réduire le nombre de stations en utilisant une coloration de graphe
int reduceStations(int* stations, Exclusion* exclusions, int numExclusions) {
    int maxStation = findMaxStation(exclusions, numExclusions);

    // Utilisation d'un tableau pour stocker les couleurs (numéro de station) des opérations
    int* colors = (int*)malloc((maxStation + 1) * sizeof(int));

    // Initialisation des couleurs
    for (int i = 0; i <= maxStation; i++) {
        colors[i] = i;
    }

    // Appliquer la coloration en respectant les contraintes d'exclusion
    for (int i = 1; i <= maxStation; i++) {
        for (int j = 1; j <= maxStation; j++) {
            if (canAssign(i, j, stations, exclusions, numExclusions) && colors[i] != colors[j]) {
                // Si les opérations peuvent être affectées à la même station et n'ont pas la même couleur,
                // attribuer la couleur commune à ces deux opérations
                int commonColor = colors[i];
                int oldColor = colors[j];
                for (int k = 1; k <= maxStation; k++) {
                    if (colors[k] == oldColor) {
                        colors[k] = commonColor;
                    }
                }
            }
        }
    }

    // Compter le nombre de couleurs distinctes (stations)
    int numColors = 0;
    for (int i = 1; i <= maxStation; i++) {
        if (colors[i] == i) {
            numColors++;
        }
    }

    // Libérer la mémoire allouée
    free(colors);

    return numColors;
}

int main() {
    // Demander à l'utilisateur le nom du fichier texte
    printf("Veuillez entrer le nom du fichier texte : \n ");

    // Allouer dynamiquement de l'espace pour stocker le nom du fichier
    char filename = (char*)malloc(100 * sizeof(char));

    // Vérifier si l'allocation de mémoire a réussi
    if (filename == NULL) {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }


    gets(filename);

    //strcpy(filename,"exclusion.txt");
    // Lire le nom du fichier à partir de l'utilisateur
    //scanf("%s", filename);
    //filename="exclusion.txt";

    // Charger les exclusions à partir du fichier texte
    Exclusion* exclusions = NULL;
    int numExclusions = readExclusions(filename, &exclusions);

    // Trouver le numéro de station maximal
    int numStations = findMaxStation(exclusions, numExclusions);

    // Réduire le nombre de stations en utilisant une coloration de graphe
    int reducedStations = reduceStations(NULL, exclusions, numExclusions);

    printf("Nombre de stations initial : %d\n", numStations);
    gets(filename);
    printf("Nombre de stations réduit : %d\n", reducedStations);

    // Libérer la mémoire allouée
    free(filename);
    free(exclusions);

    return 0;
}