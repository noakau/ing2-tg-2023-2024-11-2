//
// Created by elise on 02/12/2023.
//
//
// Created by elise on 01/12/2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "precedence.h"

Graphe initialiserGraphe() {
    Graphe graphe;
    graphe.numAretes = 0;
    graphe.aretes = NULL;
    return graphe;
}

void libererGraphe(Graphe *graphe) {
    free(graphe->aretes);
}

Graphe lireContraintesPrecedence(const char *nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    Graphe graphe = initialiserGraphe();

    int de, vers;
    while (fscanf(fichier, "%d %d", &de, &vers) == 2) {
        graphe.numAretes++;
        graphe.aretes = (Arete *)realloc(graphe.aretes, graphe.numAretes * sizeof(Arete));
        if (graphe.aretes == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire\n");
            exit(EXIT_FAILURE);
        }
        graphe.aretes[graphe.numAretes - 1].de = de;
        graphe.aretes[graphe.numAretes - 1].vers = vers;
    }

    fclose(fichier);
    return graphe;
}

void afficherContraintesPrecedence(const Graphe *graphe) {
    printf("Contraintes de precedence :\n");
    for (int i = 0; i < graphe->numAretes; i++) {
        printf("%d -> %d\n", graphe->aretes[i].de, graphe->aretes[i].vers);
    }
}