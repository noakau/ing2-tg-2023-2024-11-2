//
// Created by elise on 30/09/2023.
//

#ifndef TDGTP3ESSAIE2_TP3_H
#define TDGTP3ESSAIE2_TP3_H

#include <stdio.h>
#include <stdlib.h>

// Structure d'un arc
struct Arc
{
    int sommet; // Numero de sommet d'un arc adjacent au sommet initial
    int valeur;
    int poids;
    struct Arc* arc_suivant;
};

// Alias de pointeur sur un Arc
typedef struct Arc* pArc;

// Structure d'un sommet
struct Sommet
{
    struct Arc* arc;
    int valeur;
};

// Alias de pointeur sur un Sommet
typedef struct Sommet* pSommet;

// Alias d'un Graphe
typedef struct Graphe
{
    int taille;
    int orientation;
    int ordre;
    pSommet* pSommet;
} Graphe;

// Creation graphe
Graphe* CreerGraphe(int ordre);

// La construction du reseau peut se faire a partir d'un fichier dont le nom est passe en parametre
//Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs

Graphe * lire_graphe(char * nomFichier, int matA[9][9]);

// Ajouter l'arete entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2,int pds);

// Affichage des successeurs du sommet num
void afficher_successeurs(pSommet * sommet, int num);

// Affichage du graphe avec les successeurs de chaque sommet

void graphe_afficher(Graphe* graphe);

/*Affichage de la couleur des sommets*/
void afficher_Couleur_Graphe(Graphe *g);

/* Recupere l'index depuis la velur d'un sommet */

int Index_depuis_valeur_du_sommet(Graphe *g, int valeurSommet);

// Definition des fonctions necessaires
int nettoyerFluxEntree();
int choixdep();
int choixfin();
void dijkstra(int matA[9][9], int depart, int arrivee, int ordre);


#endif //TDGTP3ESSAIE2_TP3_H
