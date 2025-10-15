#include "grille.h"
#include "deplacements.h"
#include "interface.h"
#include "sauvegarde.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand((unsigned int)time(NULL));

    Grille grille;
    int taille = 5;
    int nb_numeros = 5;

    printf("Jeu ZIP - Configuration\n");
    printf("Taille de la grille (5 à 10, 0=5) : ");
    scanf("%d", &taille);
    if (taille < TAILLE_MIN || taille > TAILLE_MAX) taille = 5;

    printf("Nombre de numéros (1 à 12, 0=5) : ");
    scanf("%d", &nb_numeros);
    if (nb_numeros < 1 || nb_numeros > NB_NUMEROS_MAX) nb_numeros = 5;

    while (getchar() != '\n');

    initialiser_grille(&grille, taille, taille);
    placer_numeros_aleatoires(&grille, nb_numeros);

    Position curseur = {0, 0};
    for (int i = 0; i < taille; ++i)
        for (int j = 0; j < taille; ++j)
            if (grille.cellules[i][j].numero == 1)
                curseur = (Position){j, i};

    Position chemin[TAILLE_MAX * TAILLE_MAX];
    int longueur_chemin = 0;
    push_chemin(chemin, &longueur_chemin, curseur);
    grille.cellules[curseur.y][curseur.x].visite = true;
    int prochain_numero = 2;

    while (1) {
        effacer_console();
        afficher_grille(&grille, curseur, prochain_numero);
        printf("\nCommande : z/q/s/d, e=sauvegarde, l=charger, x=quitter\n");

        int touche = lire_caractere();
        Position dest = curseur;
        bool quitter = false;

        switch (touche) {
            case 'z': case 'w': dest.y--; break;
            case 's': dest.y++; break;
            case 'q': case 'a': dest.x--; break;
            case 'd': dest.x++; break;
            case 'e': sauvegarder_partie(&grille, chemin, longueur_chemin, prochain_numero); continue;
            case 'l': charger_partie(&grille, chemin, &longueur_chemin, &curseur, &prochain_numero); continue;
            case 'x': quitter = true; break;
            default: continue;
        }

        if (quitter) break;

        if (!deplacement_valide(&grille, curseur, dest, chemin, longueur_chemin, prochain_numero))
            continue;

        if (!grille.cellules[dest.y][dest.x].visite) {
            push_chemin(chemin, &longueur_chemin, dest);
            grille.cellules[dest.y][dest.x].visite = true;
            if (grille.cellules[dest.y][dest.x].numero == prochain_numero)
                prochain_numero++;
        } else {
            pop_chemin(chemin, &longueur_chemin);
        }

        curseur = dest;

        bool tout_visite = true;
        for (int i = 0; i < grille.lignes; ++i)
            for (int j = 0; j < grille.colonnes; ++j)
                if (!grille.cellules[i][j].visite)
                    tout_visite = false;

        if (tout_visite) {
            effacer_console();
            afficher_grille(&grille, curseur, prochain_numero);
            printf("\nBravo, vous avez gagné !\n");
            break;
        }
    }

    printf("Fin du jeu.\n");
    return 0;
}
