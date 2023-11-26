#include <stdio.h>
#include <stdlib.h>

// Structure pour représenter une paire d'opérations exclues
typedef struct {
    int operation1;
    int operation2;
} ExclusionPair;

// Structure pour représenter les informations trouvées dans le fichier
typedef struct {
    int maxOperation;
    int maxStation;
} FileInformation;

typedef struct {
    int operations;
    int numOperations;
} Workstation;

// Fonction pour comparer deux stations lors du tri
int compareStations(const void *a, const void *b) {
    return (*(Workstation*)a).numOperations - (*(Workstation*)b).numOperations;
}

// Fonction pour trouver le nombre maximal d'opérations et de stations à partir d'un fichier
FileInformation findMaxOperationAndStationFromFile(const char *filename) {
    FileInformation fileInfo = {0, 0};

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int op1, op2, station;

    while (fscanf(file, "%d %d", &op1, &op2) == 2) {
        if (op1 > fileInfo.maxOperation) {
            fileInfo.maxOperation = op1;
        }
        if (op2 > fileInfo.maxOperation) {
            fileInfo.maxOperation = op2;
        }

        // Trouver le numéro de station le plus élevé
        if (station > fileInfo.maxStation) {
            fileInfo.maxStation = station;
        }
    }

    fclose(file);
    return fileInfo;
}

// Fonction pour vérifier si deux opérations sont exclues
int areOperationsExcluded(ExclusionPair exclusionPairs[], int numPairs, int op1, int op2) {
    for (int i = 0; i < numPairs; i++) {
        if ((exclusionPairs[i].operation1 == op1 && exclusionPairs[i].operation2 == op2) ||
            (exclusionPairs[i].operation1 == op2 && exclusionPairs[i].operation2 == op1)) {
            return 1; // Les opérations sont exclues
        }
    }
    return 0; // Les opérations ne sont pas exclues
}

// Fonction pour répartir les opérations sur les stations en respectant les contraintes d'exclusion
void assignOperationsToStations(ExclusionPair exclusionPairs[], int numPairs, Workstation stations[], int numStations, FileInformation info) {
    for (int op1 = 1; op1 <= info.maxOperation; op1++) {
        // Trouver une station pour l'opération op1
        for (int stationIndex = 0; stationIndex < numStations; stationIndex++) {
            int canAssign = 1;

            // Vérifier si l'opération op1 peut être affectée à cette station
            for (int op2Index = 0; op2Index < stations[stationIndex].numOperations; op2Index++) {
                int op2 = stations[stationIndex].operations[op2Index];
                if (areOperationsExcluded(exclusionPairs, numPairs, op1, op2)) {
                    canAssign = 0;
                    break;
                }
            }

            // Si l'opération op1 peut être affectée à cette station, l'ajouter à la station
            if (canAssign) {
                stations[stationIndex].operations[stations[stationIndex].numOperations] = op1;
                stations[stationIndex].numOperations++;
                break;
            }
        }
    }
}

// Fonction pour afficher la répartition des opérations sur les stations
void printStationAssignmentSorted(Workstation stations[], int numStations) {
    // Trier les stations par ordre croissant avant l'affichage
    qsort(stations, numStations, sizeof(Workstation), compareStations);

    for (int i = 0; i < numStations; i++) {
        printf("Station %d:", i + 1);
        for (int j = 0; j < stations[i].numOperations; j++) {
            printf(" %d", stations[i].operations[j]);
        }
        printf("\n");
    }
}

int main() {
    char* filename;
    printf("entrez le nom du fichier souhaité");
    scanf("%f", filename);
    // Trouver le nombre maximal d'opérations et de stations à partir du fichier
    FileInformation fileInfo = findMaxOperationAndStationFromFile("contraintes.txt");

    // Utiliser les valeurs trouvées
    int maxOperation = fileInfo.maxOperation;
    int maxStation = fileInfo.maxStation;

    // Déclaration et initialisation des stations de travail
    Workstation stations[maxStation];
    for (int i = 0; i < maxStation; i++) {
        stations[i].numOperations = 0;
    }

    // Répartir les opérations sur les stations en respectant les contraintes d'exclusion
    assignOperationsToStations(fileInfo.exclusionPairs, fileInfo.numPairs, stations, maxStation);

    // Afficher la répartition des opérations sur les stations (triées par ordre croissant)
    printStationAssignmentSorted(stations, maxStation);é²)

    return 0;
}