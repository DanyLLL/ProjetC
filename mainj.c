#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "mainj.h"
#include "mot.h"
#pragma warning(disable : 4996)

void initMain(Main* main) {
	main->nb = 0;
	main->chevalets = (char*)malloc(sizeof(char));
}

void ajouteMain(Main* main, char lettre) {
	main->chevalets = (char*)realloc(main->chevalets, sizeof(char) * (main->nb + 2));
	main->chevalets[main->nb] = lettre; // Ajoute la lettre
	main->nb++;
	main->chevalets[main->nb] = '\0'; // Ajoute '\0'
}

char retireMain(Main* main, int indice) {
	char lettre = main->chevalets[indice];
	for (int i = indice; i < main->nb - 1; i++) {
		main->chevalets[i] = main->chevalets[i + 1];
	}
	main->nb = main->nb - 1;
	char* test_allocation = (char*)realloc(main->chevalets, sizeof(char) * (main->nb + 2));
	if (test_allocation) {
		main->chevalets = test_allocation;
	}
	main->chevalets[main->nb] = '\0';
	return lettre;
}


void prepareMainsJeu(Pioche* pioche, Main* mainJ1, Main* mainJ2) {

	srand(time(NULL));
	for (int i = 0; i < 12;) {
		int i1 = rand() % (pioche->nb - 1);
		int i2 = rand() % (pioche->nb - 1);
		if (i1 != i2 && i1 < pioche->nb && i2 < pioche->nb) {
			ajouteMain(mainJ1, pioche->chevalets[i1]);
			retirePioche(pioche, i1);
			ajouteMain(mainJ2, pioche->chevalets[i2]);
			retirePioche(pioche, i2);
			i = i + 1;
		}
	}
	qsort(mainJ1->chevalets, strlen(mainJ1->chevalets), sizeof(char), triAlphabetique);
	qsort(mainJ2->chevalets, strlen(mainJ2->chevalets), sizeof(char), triAlphabetique);
	printf("1 : %s\n", mainJ1->chevalets);
	printf("2 : %s\n\n", mainJ2->chevalets);
}
