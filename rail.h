#pragma once

#include "chevalet.h"

typedef struct {
	int valeur;
	struct Maillon* suivant;
}Maillon;

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1};

enum { GAUCHE = 0, DROITE = 1 };

typedef struct {
	char lettres[MAX_RAIL];
	int debut;
	int fin;
}Rail;

int initRail(Rail* r);


void ajtRail(Rail* r, const char l, int sens);


void affRail(Rail* r);

void ajtMotRail1(Rail* r, const char* m, int sens);

void ajtMotRail2(Rail* r, const char* m, int sens);

void triRail(Rail* r);

void triRail2(Rail* r);