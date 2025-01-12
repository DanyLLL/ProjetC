#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "mot.h"
#pragma warning(disable : 4996)

void initMain(Main* main) {
	main->nb = 0;
	main->chevalets = (char*)malloc(sizeof(char)); // On alloue la mémoire nécessaire.
}

void ajouteMain(Main* main, char lettre) {
	main->chevalets = (char*)realloc(main->chevalets, sizeof(char) * (main->nb + 2)); // On realloue la mémoire.
	main->chevalets[main->nb] = lettre; // Ajoute la lettre
	main->nb++;
	main->chevalets[main->nb] = '\0';
}

char retireMain(Main* main, int indice) {
	char lettre = main->chevalets[indice];
	for (int i = indice; i < main->nb - 1; i++) {
		main->chevalets[i] = main->chevalets[i + 1]; // On décale tous les chevalets afin d'écraser celui à l'indice donné.
	}
	main->nb = main->nb - 1;
	char* test_allocation = (char*)realloc(main->chevalets, sizeof(char) * (main->nb + 2)); // On realloue la mémoire.
	if (test_allocation) {
		main->chevalets = test_allocation;
	}
	main->chevalets[main->nb] = '\0';
	return lettre;
}


void prepareMainsJeu(Pioche* pioche, Main* mainJ1, Main* mainJ2) {
	ajouteMain(mainJ1, 'A');   // A
	ajouteMain(mainJ1, 'C');  // C
	ajouteMain(mainJ1, 'E');  // E
	ajouteMain(mainJ1, 'E');  // E
	ajouteMain(mainJ1, 'E');  // E
	ajouteMain(mainJ1, 'L');  // L
	ajouteMain(mainJ1, 'M');  // M
	ajouteMain(mainJ1, 'N');  // N
	ajouteMain(mainJ1, 'R');  // R
	ajouteMain(mainJ1, 'S');  // S
	ajouteMain(mainJ1, 'U');  // U
	ajouteMain(mainJ1, 'V');  // V

	ajouteMain(mainJ2, 'A');  // A
	ajouteMain(mainJ2, 'B');  // B
	ajouteMain(mainJ2, 'D');  // D
	ajouteMain(mainJ2, 'E');  // E
	ajouteMain(mainJ2, 'I');  // I
	ajouteMain(mainJ2, 'L');  // L
	ajouteMain(mainJ2, 'N');  // N
	ajouteMain(mainJ2, 'O');  // O
	ajouteMain(mainJ2, 'R');  // R
	ajouteMain(mainJ2, 'R');  // R
	ajouteMain(mainJ2, 'T');  // T
	ajouteMain(mainJ2, 'U');  // U
	srand(time(NULL));
	/*for (int i = 0; i < 12;) {
		int i1 = rand() % (pioche->nb - 1);
		int i2 = rand() % (pioche->nb - 1);
		if (i1 != i2 && i1 < pioche->nb && i2 < pioche->nb) {
			ajouteMain(mainJ1, pioche->chevalets[i1]);
			retirePioche(pioche, i1);
			ajouteMain(mainJ2, pioche->chevalets[i2]);
			retirePioche(pioche, i2);
			i = i + 1;
		}
	}*/
	qsort(mainJ1->chevalets, strlen(mainJ1->chevalets), sizeof(char), triAlphabetique); // On trie avant l'affichage.
	qsort(mainJ2->chevalets, strlen(mainJ2->chevalets), sizeof(char), triAlphabetique);
	printf("1 : %s\n", mainJ1->chevalets);
	printf("2 : %s\n\n", mainJ2->chevalets);
}

void test_Mainj(){
	Main m;
	initMain(&m);
	ajouteMain(&m, 'A');
	assert(retireMain(&m, 0) == 'A');
	ajouteMain(&m, 'B');
	assert(retireMain(&m, 0) == 'B');
	ajouteMain(&m, 'A');
	assert(retireMain(&m, 0) == 'F');
	ajouteMain(&m, 'B');
	assert(retireMain(&m, 0) == 'X');

}
