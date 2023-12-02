//
// Created by elise on 01/12/2023.
//

#ifndef PRECEDENCE_PRECEDENCEH_H
#define PRECEDENCE_PRECEDENCEH_H

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

#endif //PRECEDENCE_PRECEDENCEH_H
