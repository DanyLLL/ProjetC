#include <string.h>
#include "pioche.h"
#include "partie.h"
#include "mainj.h"
#include "rail.h"
#include "mot.h"
#pragma warning(disable : 4996)

int main() {
	Pioche pioche;
	Main joueur1;
	Main joueur2;
	Rail rail;
	Rail railAnt;
	initPioche(&pioche);
	initMain(&joueur1);
	initMain(&joueur2);
	initRail(&rail);
	initRail(&railAnt);
	lancerPartie(&pioche, &joueur1, &joueur2, &rail,&railAnt);
}
