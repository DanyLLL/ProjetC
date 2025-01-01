#pragma once

typedef struct {
	int valeur;
	struct Maillon* suivant;
}Maillon;

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1 };

enum { GAUCHE = 0, DROITE = 1 };

typedef struct {
	char lettres[MAX_RAIL];
	int debut;
	int fin;
}Rail;

int initRail(Rail* r);

void ajtRail(Rail* r, const char l, int sens);

void affRail(Rail* r);

void ajtMotRail(Rail* r, const char* m, int sens);
