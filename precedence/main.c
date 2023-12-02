#include <stdio.h>
#include "precedenceh.h"

int main() {
    // Lire les contraintes de précédence à partir du fichier
    Graphe graphe = lireContraintesPrecedence("precedence.txt");

    // Vérifier si le graphe est vide (pas de contraintes)
    if (graphe.numAretes == 0) {
        printf("Aucune contrainte de précédence trouvée\n");
        return 1;  // Retourner un code d'erreur
    }

    afficherContraintesPrecedence(&graphe);

    libererGraphe(&graphe);

    return 0;
}
