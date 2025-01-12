#pragma once

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1 };

enum { GAUCHE = 0, DROITE = 1 };

enum { MAX_ROV = 2 };

typedef struct {
	char lettres[MAX_RAIL];
	int debut;
	int fin;
}Rail;



/**
* @brief Initialise le rail.
*/
int initRail(Rail* r);



/**
* @brief Ajoute une lettre au rail en fonction du sens.
*/
char ajouteRail(Rail* r, const char l, int sens);



/**
* @brief Affiche le recto et le verso du rail.
*/
void afficherRail(Rail* r);



/**
* @brief Ajoute un mot au rail en fonction du sens.
*/
char* ajouteMotRail(Rail* r, const char* m, int sens);

/**
* @brief Récupère nb lettres à l'extrémité du rail en fonction du sens.
*/
char* recupMotRail(Rail* rail, int nb, int sens);

/**
* @brief Inverse le rail.
*/
Rail inverseRail(const Rail* rail);
