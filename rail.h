#pragma once

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1 };

enum { GAUCHE = 0, DROITE = 1 };

enum { MAX_ROV = 2 };

typedef struct {
	char lettres[MAX_RAIL];
}Rail;

/**
* @brief Initialise le rail.
* @param[in,out] r le rail à initialiser.
**/
int initRail(Rail* r);

/**
* @brief Ajoute un caractère au rail
* @param[in] rail le rail de jeu.
* @param[in] l le caractere à ajouter
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE) le cote duquel on ajoute l
* @return la lettre qui "tombe" du rail
**/
char ajouteRail(Rail* rail, const char l, int sens);

/**
* @brief affiche un rail
* @param[in] rail le rail.
**/
void afficherRail(Rail* rail);

/**
* @brief Ajoute un mot au rail.
* @param[in] rail le rail de jeu.
* @param[in] m le mot à ajouter.
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE) le cote duquel on ajoute m.
* @return la lettre qui tombe du rail.
**/
char* ajouteMotRail(Rail* rail, const char* m, int sens);

/**
* @brief Recupere les nb lettres du rail au sens donné.
* @param[in] rail le rail de jeu.
* @param[in] nb le nombre de caractere sur le rail à récupérer sur l'extrémité.
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE)
* @return les lettres à l'extrémité du rail.
**/
char* recupMotRail(Rail* rail, int nb, int sens);

/**
* @brief Crée l'inverse d'un rail.
* @param[in] rail le rail dont on veut connaitre l'inverse.
* @return l'inverse du rail.
**/
Rail inverseRail(const Rail* rail);

/**
* @brief Teste les fonctions spécifiques du composant rail.
*/
void test_Rail();
