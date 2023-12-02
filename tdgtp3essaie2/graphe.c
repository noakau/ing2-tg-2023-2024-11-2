//
// Created by elise on 30/09/2023.

#include "tp3.h"
#define MAX 9999

// On reutilise les sous-programmes donnés dans le TP2

void afficher_successeurs(pSommet * sommet, int num)
{
    printf(" sommet %d :\n",num);

    pArc tmp =sommet[num]->arc;

    while(tmp!=NULL)
    {
        printf("%d : %d / ",tmp->sommet, tmp->poids); // Affichage pour chaque arc numero sommet successeur et poids
        tmp=tmp->arc_suivant;
    }

}

pSommet* CreerArete(pSommet* sommet,int s1,int s2,int pds)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->poids=pds;

        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->poids=pds;
        Newarc->arc_suivant=NULL;
        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// Affichage des informations du graphe
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    printf("ordre = %d\n", graphe->ordre);

    printf("liste des sommets :\n");
    for (int i = 0; i < graphe->ordre; i++)
    {
        printf("%d\n", graphe->pSommet[i]->valeur);
    }

    printf("taille = %d\n", graphe->taille);

    printf("listes d'adjacence :\n");
    for (int i = 0; i < graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }
}

Graphe* CreerGraphe(int ordre)
{   // Allocation pour la structure du graphe et les sommets
    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}


// Dans ce sous-programme on modifie et ajuste des elements afin de convenir au TP3
Graphe* lire_graphe(char* nomFichier, int matA[9][9])
{
    Graphe* graphe;
    FILE* ifs = fopen(nomFichier, "r");
    int ordre, taille, orientation, poids;

    if (!ifs)
    {
        printf("Erreur lors de la lecture du fichier\n");
        exit(-1);
    }

    // On a la lecture de l'ordre
    fscanf(ifs, "%d", &ordre);

    // On créée le graphe d'ordre sommets
    graphe = CreerGraphe(ordre);

    for (int i = 0; i < ordre; i++){
        int sommet;
        fscanf(ifs, "%d", &sommet);
    }

    // On lit la taille et l'orientation
    fscanf(ifs, "%d", &taille);

    graphe->orientation = 0; // Pour signifier un graphe non orienté
    graphe->ordre = ordre;
    graphe->taille = taille;

    // On initialise maintenant la matrice d'adjacence
    for (int i = 0; i<graphe->ordre; i++){
        for (int j = 0; j<graphe->ordre; j++){
            matA[i][j] = MAX;
        }
    }

    // On lit les arêtes et leur poids
    for (int i = 0; i < taille; i++){
        int s1, s2;
        fscanf(ifs, "%d %d %d", &s1, &s2, &poids);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);
        matA[s1][s2] = poids;
        matA[s2][s1] = poids;
    }

    fclose(ifs);

    return graphe;
}
