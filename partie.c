#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "partie.h"
#include "mainj.h"
#include "mot.h"
#include "mainj.h"

#pragma warning(disable : 4996)

void lancerPartie(Pioche* pioche, Main* J1, Main* J2) {
	preparePiocheJeu(pioche);
	prepareMainsJeu(pioche, J1, J2);
	deterOrdreJeu(J1, J2);
	afficheSituationCouranteJeu(J1, J2);
	deroulePartie(J1, J2);
}

void deroulePartie(Main* J1, Main* J2) {
	if (deterOrdreJeu(J1, J2) == 0) {
		printf("1> ");
	}
	else {
		printf("2> ");
	}
}

void afficheSituationCouranteJeu(Main* mainJ1,Main* mainJ2) {
	printf("1 : %s\n", mainJ1->chevalets);
	printf("2 : %s\n", mainJ2->chevalets);
	printf("R : %s\n");
	printf("V : %s\n\n");
}

