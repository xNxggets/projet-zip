#include "deplacements.h"
#include <stdbool.h>

bool positions_egales(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

bool deplacement_valide(const Grille *g, Position actuel, Position destination,
                        Position chemin[], int longueur_chemin, int prochain_numero) {

    if (destination.x < 0 || destination.y < 0 ||
        destination.x >= g->colonnes || destination.y >= g->lignes)
        return false;

    const Case *c = &g->cellules[destination.y][destination.x];

    if (c->numero > 0 && c->numero != prochain_numero)
        return false;

    if (!c->visite)
        return true;

    if (longueur_chemin >= 2) {
        Position precedent = chemin[longueur_chemin - 2];
        if (positions_egales(precedent, destination))
            return true;
    }

    return false;
}

void push_chemin(Position chemin[], int *longueur, Position p) {
    chemin[*longueur] = p;
    (*longueur)++;
}

void pop_chemin(Position chemin[], int *longueur) {
    if (*longueur > 0)
        (*longueur)--;
}
