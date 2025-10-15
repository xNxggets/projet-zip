CC = gcc
CFLAGS = -Wall -Wextra -std=c11

OBJETS = main.o grille.o deplacements.o interface.o sauvegarde.o

zip: $(OBJETS)
	$(CC) $(CFLAGS) -o zip $(OBJETS)

main.o: main.c grille.h deplacements.h interface.h sauvegarde.h
grille.o: grille.c grille.h
deplacements.o: deplacements.c deplacements.h grille.h
interface.o: interface.c interface.h grille.h
sauvegarde.o: sauvegarde.c sauvegarde.h grille.h

clean:
	rm -f *.o zip
