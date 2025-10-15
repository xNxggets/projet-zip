#include "sauvegarde.h"
#include <stdio.h>

void sauvegarder_partie(const Grille *g, Position chemin[], int longueur_chemin, int prochain_numero) {
    FILE *f = fopen(NOM_FICHIER_SAUVEGARDE, "w");
    if (!f) {
        printf("Erreur : impossible de sauvegarder.\n");
        return;
    }

    fprintf(f, "%d %d\n", g->lignes, g->colonnes);
    fprintf(f, "%d\n", prochain_numero);
    fprintf(f, "%d\n", longueur_chemin);
    for (int i = 0; i < longueur_chemin; ++i)
        fprintf(f, "%d %d\n", chemin[i].x, chemin[i].y);

    for (int i = 0; i < g->lignes; ++i)
        for (int j = 0; j < g->colonnes; ++j)
            fprintf(f, "%d %d\n", g->cellules[i][j].numero, g->cellules[i][j].visite);

    fclose(f);
    printf("Partie sauvegardée.\n");
}

bool charger_partie(Grille *g, Position *chemin, int *longueur_chemin, Position *curseur, int *prochain_numero) {
    FILE *f = fopen(NOM_FICHIER_SAUVEGARDE, "r");
    if (!f) {
        printf("Aucune sauvegarde trouvée.\n");
        return false;
    }

    int L, C;
    if (fscanf(f, "%d %d", &L, &C) != 2) { fclose(f); return false; }
    initialiser_grille(g, L, C);
    fscanf(f, "%d", prochain_numero);
    fscanf(f, "%d", longueur_chemin);

    for (int i = 0; i < *longueur_chemin; ++i)
        fscanf(f, "%d %d", &chemin[i].x, &chemin[i].y);

    for (int i = 0; i < g->lignes; ++i)
        for (int j = 0; j < g->colonnes; ++j)
            fscanf(f, "%d %d", &g->cellules[i][j].numero, (int*)&g->cellules[i][j].visite);

    *curseur = chemin[*longueur_chemin - 1];
    fclose(f);
    printf("Partie chargée.\n");
    return true;
}
