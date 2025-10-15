#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
  #include <conio.h>
#else
  #include <termios.h>
  #include <unistd.h>
#endif

void effacer_console() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int lire_caractere() {
#ifdef _WIN32
    int c = _getch();
    if (c == 0 || c == 0xE0) _getch();
    return c;
#else
    struct termios ancien, nouveau;
    tcgetattr(STDIN_FILENO, &ancien);
    nouveau = ancien;
    nouveau.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &nouveau);
    int c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &ancien);
    return c;
#endif
}

void afficher_grille(const Grille *g, Position curseur, int prochain_numero) {
    printf("Jeu ZIP - Deplacements: z/s/q/d | e=sauvegarder | l=charger | x=quitter\n");
    printf("Prochain numero attendu : %d\n", prochain_numero);

    for (int i = 0; i < g->lignes; ++i) {
        for (int j = 0; j < g->colonnes; ++j) {
            Position p = {j, i};
            const Case *c = &g->cellules[i][j];
            bool est_curseur = (curseur.x == j && curseur.y == i);

            if (est_curseur) printf("[");
            else printf(" ");

            if (c->numero > 0)
                printf("%2d", c->numero);
            else if (c->visite)
                printf(" .");
            else
                printf("  ");

            if (est_curseur) printf("]");
            else printf(" ");
        }
        printf("\n");
    }
}
