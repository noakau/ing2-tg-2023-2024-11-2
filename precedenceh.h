//
// Created by jules on 03/12/23.
//

#ifndef TEMPS_DE_CYCLE_PRECEDENCEH_H
#define TEMPS_DE_CYCLE_PRECEDENCEH_H
typedef struct {
    int de;
    int vers;
} Arete;

typedef struct {
    int numAretes;
    Arete *aretes;
} Graphe;

Graphe initialiserGraphe();
void libererGraphe(Graphe *graphe);
Graphe lireContraintesPrecedence(const char *nomFichier);
void afficherContraintesPrecedence(const Graphe *graphe);
