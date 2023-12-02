#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp6.h"

#define MAX_ORDRE 100
#define INFINI 9999

// Fonction de création d'un graphe avec un ordre donné
Graphe* CreerGraphe(int ordre) {
    Graphe* Newgraphe = (Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++) {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }

    return Newgraphe;
}

// Fonction pour ajouter une arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet, int s1, int s2, int pds) {
    if (sommet[s1]->arc == NULL) {
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->valeur = 0; // Vous pouvez initialiser la valeur à 0 par défaut
        Newarc->poids = pds;

        Newarc->arc_suivant = NULL;
        sommet[s1]->arc = Newarc;
        return sommet;
    } else {
        pArc temp = sommet[s1]->arc;
        while (!(temp->arc_suivant == NULL)) {
            temp = temp->arc_suivant;
        }
        pArc Newarc = (pArc)malloc(sizeof(struct Arc));
        Newarc->sommet = s2;
        Newarc->valeur = 0; // Vous pouvez initialiser la valeur à 0 par défaut
        Newarc->poids = pds;
        Newarc->arc_suivant = NULL;
        temp->arc_suivant = Newarc;
        return sommet;
    }
}

// Affichage des successeurs du sommet num
void afficher_successeurs(pSommet* sommet, int num) {
    printf("Successeurs du sommet %d :\n", num);
    pArc tmp = sommet[num]->arc;
    while (tmp != NULL) {
        printf("Sommet : %d, Capacité : %d\n", tmp->sommet, tmp->poids);
        tmp = tmp->arc_suivant;
    }
    printf("\n");
}

// Fonction pour afficher les informations du graphe
void graphe_afficher(Graphe* graphe) {
    printf("Graphe\n");
    printf("Ordre = %d\n", graphe->ordre);
    printf("Liste des sommets :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%d\n", graphe->pSommet[i]->valeur);
    }
    printf("Taille = %d\n", graphe->taille);
    printf("Listes d'adjacence :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
    }
}

// Fonction pour lire un graphe à partir d'un fichier texte
Graphe* lire_graphe(char* nomFichier) {
    FILE* ifs = fopen(nomFichier, "r");
    int ordre, taille, orientation, poids;

    if (!ifs) {
        printf("Erreur lors de la lecture du fichier\n");
        exit(-1);
    }

    // On a la lecture de l'ordre
    fscanf(ifs, "%d", &ordre);

    // On créée le graphe d'ordre sommets
    Graphe* graphe = CreerGraphe(ordre);

    for (int i = 0; i < ordre; i++) {
        int sommet;
        fscanf(ifs, "%d", &sommet);
    }

    // On lit la taille et l'orientation
    fscanf(ifs, "%d %d", &taille, &orientation);

    graphe->orientation = orientation;
    graphe->ordre = ordre;
    graphe->taille = taille;

    // On initialise maintenant la matrice d'adjacence
    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < graphe->ordre; j++) {
            graphe->matrice_adjacence[i][j] = INFINI;
        }
    }

    // On lit les arêtes et leur poids
    for (int i = 0; i < taille; i++) {
        int s1, s2;
        fscanf(ifs, "%d %d %d", &s1, &s2, &poids);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);
        graphe->matrice_adjacence[s1][s2] = poids;
        if (!orientation) {
            graphe->matrice_adjacence[s2][s1] = poids;
        }
    }

    fclose(ifs);

    return graphe;
}

// Alias de structure pour représenter le graphe des flots
typedef struct {
    int ordre;
    int flots[MAX_ORDRE][MAX_ORDRE];
} GrapheFlots;

// Fonction Felkurson pour le calcul du flot maximal
GrapheFlots felkurson(Graphe* graphe) {
    GrapheFlots grapheFlots;
    grapheFlots.ordre = graphe->ordre;


    return grapheFlots;
}

// Fonction calcul des écarts du graphe des flots
GrapheFlots getEcart(Graphe* graphe, GrapheFlots* grapheFlots) {
    GrapheFlots ecart;
    ecart.ordre = graphe->ordre;

    for (int i = 0; i < graphe->ordre; i++) {
        for (int j = 0; j < graphe->ordre; j++) {
            ecart.flots[i][j] = graphe->matrice_adjacence[i][j] - grapheFlots->flots[i][j];
        }
    }

    return ecart;
}

int main() {
    char nomfichier[50];

    printf("Entrer le nom du fichier : ");
    fgets(nomfichier, sizeof(nomfichier), stdin);
    nomfichier[strcspn(nomfichier, "\n")] = '\0';

    // Charger le graphe à partir du fichier texte
    struct Graphe* g = lire_graphe(nomfichier);

    // Appeler le sous-programme pour calculer le flot maximal
    GrapheFlots flots = felkurson(g);

    // Afficher le graphe des flots et les flots calculés
    printf("Graphe des flots :\n");
    for (int i = 0; i < flots.ordre; i++) {
        for (int j = 0; j < flots.ordre; j++) {
            printf("%d ", flots.flots[i][j]);
        }
        printf("\n");
    }

    // Appeler le sous-programme pour calculer les écarts
    GrapheFlots ecart = getEcart(g, &flots);

    // Afficher le graphe des écarts
    printf("Graphe des écarts :\n");
    for (int i = 0; i < ecart.ordre; i++) {
        for (int j = 0; j < ecart.ordre; j++) {
            printf("%d ", ecart.flots[i][j]);
        }
        printf("\n");
    }

    return 0;
}

