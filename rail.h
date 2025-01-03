#pragma once

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1 };

enum { GAUCHE = 0, DROITE = 1 };

enum { MAX_ROV = 2 };

typedef struct {
	char lettres[MAX_RAIL];
	int debut;
	int fin;
}Rail;

int initRail(Rail* r);

void ajtRail(Rail* r, const char l, int sens);

void affRail(Rail* r);

void ajtMotRail(Rail* r, const char* m, int sens);

char* recupMotRail(Rail* rail, int nb, int sens);
