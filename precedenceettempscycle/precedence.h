//
// Created by elise on 02/12/2023.
//

#ifndef PRECEDENCEETTEMPSCYCLE_PRECEDENCE_H
#define PRECEDENCEETTEMPSCYCLE_PRECEDENCE_H

// Définition des structures Graphe et Arete
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

#endif //PRECEDENCEETTEMPSCYCLE_PRECEDENCE_H
