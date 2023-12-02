#include <stdio.h>
#include <limits.h>
#include "tp3.h"

#define MAX_ORDRE 9

// Tout d'abord on viens choisir le sommet de depart
int choixdepart(){
    int a;
    do{
        printf("Entrer le sommet de depart :");
        if (scanf("%d", &a) != 1){
            printf("Erreur, veuillez entrer un chiffre valide\n");
            continue;
        }

        if (a < 0 || a > 8){
            printf("Erreur, veuillez entrer un sommet de depart valide\n");
        }

    }while (a<0 || a>8);

    return a;
}

// Ensuite on viens choisir le sommet d'arrivee
int choixarrivee(){
    int a;
    do{
        printf("Entrer le sommet d'arrivee :");
        if (scanf("%d", &a) != 1){
            printf("Erreur, veuillez entrer un chiffre valide\n");
            continue;
        }

        if (a<0 || a>8){
            printf("Erreur, veuillez entrer un sommet de depart valide\n");
        }
    }while (a< 0 || a>8);

    return a;
}

// Maintenant on créée un autre sous-programme pour l'algorithme de Dijkstra
void dijkstra(int matA[9][9], int depart, int arrivee, int ordre){
    // On commence par initialiser les tableaux
    int dist[ordre]; // Il stocke la distance la plus courte entre le sommet de depart et chaque sommet
    int pred[ordre]; // Il stocke le predecesseur de chaque sommet du chemin le plus court
    int visite[ordre]; // Il dit si le sommet a ete visite ou pas

    // On initialise tout
    for (int i=0; i<ordre; ++i){
        dist[i] = INT_MAX;
        pred[i] = -1;
        visite[i] = 0;
    }
    dist[depart] = 0;

    // On passe au code de l'algorithme de Dijkstra
    for (int compteur = 0; compteur<ordre-1; ++compteur){
        int a = -1;
        int min_dist = 1;

        // On choisi le sommet pas visite qui possede la plus petite distance
        for (int b = 0; b<ordre; ++b){
            if (!visite[b] && dist[b]<min_dist){
                a = b;
                min_dist = dist[b];
            }
        }
        visite[a] = 1; // Puis on indique le sommet comme visite

        // Dorenavant on met à jour des distances
        for (int b = 0; b<ordre; ++b){
            if (!visite[b] && matA[a][b] && dist[a] != 0 && dist[a] + matA[a][b] < dist[b]){
                dist[b] = dist[a] + matA[a][b];
                pred[b] = a;
            }
        }
    }

    // Finalement on affiche le chemin le plus court et sa longueur
    printf("Entre les sommets %d et %d, le plus court chemin est ", depart, arrivee);
    int courant = arrivee;
    while (courant != depart){
        printf("%d<-", courant);
        courant = pred[courant];
    }
    printf("%d de longueur %d.\n", depart, dist[arrivee]);
}

int main(){

    char *nomfichier[50];

    printf("Entrer le nom du fichier :");
    gets(nomfichier);

    // On initialise le graphe
    int matA[MAX_ORDRE][MAX_ORDRE];
    Graphe *g = lire_graphe(nomfichier, matA); // Lecture du graphe

    // On initialise les sommets de depart, d'arrivee et l'ordre du graphe
    int Sommetdepart;
    int Sommetarrivee;
    int ordre = g->ordre;

    // On utilise donc nos sous-programmes vus precedemment avec notre graphe
    Sommetdepart = choixdepart();
    Sommetarrivee = choixarrivee();

    // On appelle notre fonction pour l'algorithme de Dijkstra
    dijkstra(matA, Sommetdepart, Sommetarrivee, ordre);

    return 0;
}
