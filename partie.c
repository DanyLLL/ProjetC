#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "partie.h"
#include "mainj.h"
#include "mot.h"
#include "rail.h"

#pragma warning(disable : 4996)

void lancerPartie(Pioche* pioche, Main* J1, Main* J2,Rail* rail) {
	preparePiocheJeu(pioche);
	prepareMainsJeu(pioche, J1, J2);
	deterOrdreJeu(J1, J2,rail);
	afficheSituationCouranteJeu(J1, J2,rail);
	deroulePartie(J1, J2);
}

void deroulePartie(Main* J1, Main* J2) {
}

void afficheSituationCouranteJeu(Main* mainJ1,Main* mainJ2,Rail* rail) {
	printf("\n1 : %s\n", mainJ1->chevalets);
	printf("2 : %s\n", mainJ2->chevalets);
	affRail(rail);
}

