//
// Created by elise on 10/12/2023.
//

#ifndef PRECEDENCETEMPS2_PRECEDENCEETTEMPSCYCLE_H
#define PRECEDENCETEMPS2_PRECEDENCEETTEMPSCYCLE_H

//structure pour la position et les valeurs d'un sommet
typedef struct {
    int sommet;
    double temps;
    int position;
    int nb_predecesseurs;
    int* predecesseurs;
} Sommet;

//structure pour les différentes stations et leurs informations
typedef struct {
    int station;
    int* sommets;
    int nb_sommets;
    int temps_restant;
} Station;

struct Noeud {
    int sommet;
    struct Noeud* suivant;
};
// creation du graphe
struct Graphe {
    int numSommets;
    struct Noeud** listesAdj;
};
// degré des sommets
struct DegreSommet {
    int sommet;
    int degre;
};

#endif //PRECEDENCETEMPS2_PRECEDENCEETTEMPSCYCLE_H
