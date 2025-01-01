#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "pioche.h"
#include "partie.h"
#include "mainj.h"
#pragma warning(disable : 4996)

int main(){
	Pioche pioche;
	Main joueur1;
	Main joueur2;
	initPioche(&pioche);
	initMain(&joueur1);
	initMain(&joueur2);
	lancerPartie(&pioche,&joueur1,&joueur2);
}
	