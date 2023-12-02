//
// Created by elise on 01/12/2023.
//

#ifndef EXCLUSIONNOA_EXCLUSION_H
#define EXCLUSIONNOA_EXCLUSION_H

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

#endif //EXCLUSIONNOA_EXCLUSION_H
