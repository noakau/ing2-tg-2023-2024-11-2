//
// Created by Noa on 03/12/2023.
//

#ifndef INTEGRATION_PRECEDENSE_H
#define INTEGRATION_PRECEDENSE_H
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
Graphe lireContraintesPrecedence( char *nomFichier);
void afficherContraintesPrecedence(const Graphe *graphe);


#endif //INTEGRATION_PRECEDENSE_H
