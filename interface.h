#ifndef INTERFACE_H
#define INTERFACE_H

#include "grille.h"

void effacer_console();
int lire_caractere();
void afficher_grille(const Grille *g, Position curseur, int prochain_numero);

#endif
