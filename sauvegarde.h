#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "grille.h"
#include <stdbool.h>

#define NOM_FICHIER_SAUVEGARDE "partie_save.txt"

void sauvegarder_partie(const Grille *g, Position chemin[], int longueur_chemin, int prochain_numero);
bool charger_partie(Grille *g, Position *chemin, int *longueur_chemin, Position *curseur, int *prochain_numero);

#endif
