#ifndef GRILLE_H
#define GRILLE_H

#include <stdbool.h>

#define TAILLE_MIN 5
#define TAILLE_MAX 10
#define NB_NUMEROS_MAX 12

typedef struct {
    int numero;
    bool visite;
} Case;

typedef struct {
    int lignes;
    int colonnes;
    Case cellules[TAILLE_MAX][TAILLE_MAX];
} Grille;

typedef struct {
    int x;
    int y;
} Position;

/* Fonctions liées à la grille */
void initialiser_grille(Grille *g, int lignes, int colonnes);
void placer_numeros_aleatoires(Grille *g, int nb_numeros);

#endif
