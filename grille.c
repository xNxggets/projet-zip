#include "grille.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

void initialiser_grille(Grille *g, int lignes, int colonnes) {
    g->lignes = lignes;
    g->colonnes = colonnes;
    for (int i = 0; i < lignes; ++i)
        for (int j = 0; j < colonnes; ++j) {
            g->cellules[i][j].numero = 0;
            g->cellules[i][j].visite = false;
        }
}

void placer_numeros_aleatoires(Grille *g, int nb_numeros) {
    int total = g->lignes * g->colonnes;
    int *indices = malloc(total * sizeof(int));
    if (!indices) { perror("Mémoire insuffisante"); exit(1); }

    for (int i = 0; i < total; ++i) indices[i] = i;
    for (int i = total - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (int k = 0; k < nb_numeros; ++k) {
        int idx = indices[k];
        int lig = idx / g->colonnes;
        int col = idx % g->colonnes;
        g->cellules[lig][col].numero = k + 1;
    }

    free(indices);
}
