#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "exclusion.h"
#include "temps_de_cycleAndOperation.h"
#include "precedense.h"


int main() {
int choix;
    do {
        // Afficher le menu
        printf("\nMenu :\n");
        printf("1. Test de la contrainte d'exclusion\n");
        printf("2. Test de la contrainte de temps de cycle et d'operation\n");
        printf("3. Test de la contrainte de précédence et temps de cycle\n");
        printf("4. Test de deux contraintes simultanément\n");
        printf("5. Quitter\n");

        // Demander le choix de l'utilisateur
        printf("Choix : ");
        scanf("%d", &choix);

        if(choix ==1){
        printf("Veuillez entrer le nom du fichier d'exclusions : \n ");

        // Allouer dynamiquement de l'espace pour stocker le nom du fichier
        char* Exclusionfilename = (char*)malloc(100 * sizeof(char));

        // Vérifier si l'allocation de mémoire a réussi
        if (Exclusionfilename == NULL) {
            perror("Erreur lors de l'allocation de mémoire");
            exit(EXIT_FAILURE);
        }

        //strcpy(Exclusionfilename,"exclusion.txt"); //pour faciliter les tests
        // Lire le nom du fichier à partir de l'utilisateur
        scanf("%s", Exclusionfilename);
        //filename="exclusion.txt";

        // Charger les exclusions à partir du fichier texte
        Exclusion* exclusions = NULL;
        int numExclusions = readExclusions(Exclusionfilename, &exclusions);

        printf("entrez deux operations a verifier:\n");
        int op1;
        int op2;
        scanf ("%d %d", &op1, &op2);
        int resultat = canAssign(op1, op2,exclusions, numExclusions );
        if (resultat ==1){
            printf(" ces operations peuvent etre  dans la meme station.\n");
            gets(Exclusionfilename);
        }
        else {
            printf(" ces operations ne peuvent pas etre  dans la meme station.\n");
            gets(Exclusionfilename);
        }
        int* operationsDansStation = NULL;
        int num_operations = 0;

        getDistinctOperations(exclusions, numExclusions, &operationsDansStation, &num_operations);

        Station **Workstation;
        int* nbStations;

        // Utilisez maintenant le tableau operations pour affecter les opérations aux stations
        Workstation=assignOperationsToStations(operationsDansStation, num_operations, exclusions, numExclusions, &nbStations);
        printf("il y a %d stations",  nbStations);
        gets(Exclusionfilename);

        }
        if(choix ==2){

            Operation *operations;
            int total_operations, total_stations;
            char* operationfilename = (char*)malloc(100 * sizeof(char));
            printf("Veuillez entrer le nom du fichier d'operations : \n ");
            scanf("%s", operationfilename);
            //strcpy(operationfilename,"operations.txt");

            total_operations = readOperations(&operations, &total_stations, operationfilename);

            if (total_operations <= 0) {
                fprintf(stderr, "Erreur lors de la lecture des operations\n");
                return EXIT_FAILURE;
            }

            // Lire la durée du temps de cycle
            char* TimeFilename = (char*)malloc(100 * sizeof(char));
            printf("Veuillez entrer le nom du fichier de temps : \n ");
            scanf("%s", TimeFilename);
            double tempsCycle = readTempsCycle(TimeFilename);
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
        }

        if(choix ==3){

                // Lire les contraintes de précédence à partir du fichier
            char* PrecedenseFilename = (char*)malloc(100 * sizeof(char));
            printf("Veuillez entrer le nom du fichier de precedense : \n ");
            scanf("%s", PrecedenseFilename);
                Graphe graphe = lireContraintesPrecedence(PrecedenseFilename);
            char* TimeFilename = (char*)malloc(100 * sizeof(char));
            printf("Veuillez entrer le nom du fichier de temps : \n ");
            scanf("%s", TimeFilename);
            char* operationfilename = (char*)malloc(100 * sizeof(char));
            printf("Veuillez entrer le nom du fichier d'operations : \n ");
            scanf("%s", operationfilename);


                // Vérifier si le graphe est vide (pas de contraintes)
                if (graphe.numAretes == 0) {
                    printf("Aucune contrainte de précédence trouvée\n");
                    return 1;  // Retourner un code d'erreur
                }

                afficherContraintesPrecedence(&graphe);

                // Lire la durée du temps de cycle
                double tempsCycle = readTempsCycle(TimeFilename);
                if (tempsCycle < 0.0) {
                    fprintf(stderr, "Erreur lors de la lecture du temps de cycle\n");
                    libererGraphe(&graphe);  // Libérer la mémoire avant de quitter en cas d'erreur
                    return EXIT_FAILURE;
                }

                // Lire les opérations
                Operation *operations;
                int total_operations, total_stations;
                total_operations = readOperations(&operations, &total_stations, operationfilename);

                if (total_operations <= 0) {
                    fprintf(stderr, "Erreur lors de la lecture des operations\n");
                    libererGraphe(&graphe);  // Libérer la mémoire avant de quitter en cas d'erreur
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

                    // Vérifier que le temps total pour la station k est inférieur à 10 secondes
                    if (total_duration_station > 10.0) {
                        fprintf(stderr, "Contrainte de temps par station violee pour la station %d\n", k);
                        free(operations);
                        libererGraphe(&graphe);
                        return EXIT_FAILURE;
                    }
                }

                // Afficher les données lues
                printf("Operations lues :\n");
                for (int i = 0; i < total_operations; i++) {
                    printf("Operation : %d, Temps d'execution : %.2f, Station : %d\n", operations[i].operation_number, operations[i].execution_time, operations[i].assigned_station);
                }

                printf("Temps de cycle : %.2f secondes\n", tempsCycle);

                libererGraphe(&graphe);


            }


    } while (choix != 5);

    return 0;
}
