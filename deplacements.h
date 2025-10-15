#ifndef DEPLACEMENTS_H
#define DEPLACEMENTS_H

#include "grille.h"

bool positions_egales(Position a, Position b);
bool deplacement_valide(const Grille *g, Position actuel, Position destination,
                        Position chemin[], int longueur_chemin, int prochain_numero);
void push_chemin(Position chemin[], int *longueur, Position p);
void pop_chemin(Position chemin[], int *longueur);

#endif
