#include <string.h>
#include "partie.h"
#pragma warning(disable : 4996)

int main() {
	Pioche pioche;
	Main joueur1;
	Main joueur2;
	Main joueur1Ant;
	Main joueur2Ant;
	Rail rail;
	Rail railAnt;
	initPioche(&pioche);
	initMain(&joueur1);
	initMain(&joueur2);
	initMain(&joueur1Ant);
	initMain(&joueur2Ant);
	initRail(&rail);
	initRail(&railAnt);
	lancerPartie(&pioche, &joueur1, &joueur2,&joueur1Ant,&joueur2Ant, &rail,&railAnt);
}
