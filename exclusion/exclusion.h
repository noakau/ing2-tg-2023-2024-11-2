//
// Created by Noa on 26/11/2023.
//

#ifndef EXCLUSION_EXCLUSION_H
#define EXCLUSION_EXCLUSION_H

#endif //EXCLUSION_EXCLUSION_H

/* Structure d'un arc*/
struct Operation
{
    int operation1;
    //int valeur;
    int operation2;
    int maxOperation;
    struct operation* operation_suivante;
};

/* Alias de pointeur sur un Arc */
typedef struct Operation* pOperation;

/* Structure d'un sommet*/
struct Stations
{
    struct Operation* maxOperation;
    int valeur;
    char couleur;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;
