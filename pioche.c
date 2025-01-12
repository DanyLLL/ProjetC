#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "pioche.h"
#pragma warning(disable : 4996)

void initPioche(Pioche* pioche) {
	pioche->nb = 0;
	pioche->chevalets = (char*)malloc(sizeof(char)); // On alloue la mémoire nécessaire.
}

void ajoutePioche(Pioche* pioche, char lettre){
	assert(pioche->nb < NB_CHEVALET);
	pioche->chevalets = (char*)realloc(pioche->chevalets, sizeof(char) * (pioche->nb + 1)); // On realloue la mémoire nécessaire.
	pioche->chevalets[pioche->nb] = lettre;
	pioche->nb++;
	pioche->chevalets[pioche->nb] = '\0';
}

char retirePioche(Pioche* pioche, int indice) {
	char lettre = pioche->chevalets[indice];
	for (int i = indice; i < pioche->nb - 1; i++) {
		pioche->chevalets[i] = pioche->chevalets[i + 1]; // On décale tous les élements pour écraser le chevalet à l'indice donné.
	}
	pioche->nb = pioche->nb - 1;
	char* test_allocation = (char*)realloc(pioche->chevalets, sizeof(char) * (pioche->nb + 1));
	if (test_allocation) {
		pioche->chevalets = test_allocation;
	}
	pioche->chevalets[pioche->nb] = '\0';
	return lettre;
}


void preparePiocheJeu(Pioche* pioche) {
	assert(pioche->nb >= 0); 

	// On remplit la pioche en fonction du paquet défini (cf sujet)
	
	for (int i = 0; i < NB_A; i = i + 1) {
		ajoutePioche(pioche, 'A');
	}
	ajoutePioche(pioche, 'B');
	for (int i = 0; i < NB_C; i = i + 1) {
		ajoutePioche(pioche, 'C');
	}
	for (int i = 0; i < NB_D; i = i + 1) {
		ajoutePioche(pioche, 'D');
	}
	for (int i = 0; i < NB_E; i = i + 1) {
		ajoutePioche(pioche, 'E');
	}
	ajoutePioche(pioche, 'F');
	ajoutePioche(pioche, 'G');
	ajoutePioche(pioche, 'H');
	for (int i = 0; i < NB_I; i = i + 1) {
		ajoutePioche(pioche, 'I');
	}
	ajoutePioche(pioche, 'J');
	for (int i = 0; i < NB_L; i = i + 1) {
		ajoutePioche(pioche, 'L');
	}
	for (int i = 0; i < NB_M; i = i + 1) {
		ajoutePioche(pioche, 'M');
	}
	for (int i = 0; i < NB_N; i = i + 1) {
		ajoutePioche(pioche, 'N');
	}
	for (int i = 0; i < NB_O; i = i + 1) {
		ajoutePioche(pioche, 'O');
	}
	for (int i = 0; i < NB_P; i = i + 1) {
		ajoutePioche(pioche, 'P');
	}
	ajoutePioche(pioche, 'Q');
	for (int i = 0; i < NB_R; i = i + 1) {
		ajoutePioche(pioche, 'R');
	}
	for (int i = 0; i < NB_S; i = i + 1) {
		ajoutePioche(pioche, 'S');
	}
	for (int i = 0; i < NB_T; i = i + 1) {
		ajoutePioche(pioche, 'T');
	}
	for (int i = 0; i < NB_U; i = i + 1) {
		ajoutePioche(pioche, 'U');
	}
	for (int i = 0; i < NB_V; i = i + 1) {
		ajoutePioche(pioche, 'V');
	}
}
