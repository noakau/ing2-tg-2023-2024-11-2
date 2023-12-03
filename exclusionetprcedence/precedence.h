//
// Created by elise on 03/12/2023.
//

#ifndef EXCLUSIONETPRCEDENCE_PRECEDENCE_H
#define EXCLUSIONETPRCEDENCE_PRECEDENCE_H

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

#endif //EXCLUSIONETPRCEDENCE_PRECEDENCE_H
