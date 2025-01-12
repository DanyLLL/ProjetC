#pragma once

enum { MAX_RAIL = 8, Last = MAX_RAIL - 1 };

enum { GAUCHE = 0, DROITE = 1 };

enum { MAX_ROV = 2 };

typedef struct {
	char lettres[MAX_RAIL];
}Rail;

/**
* @brief initialise le rail 
* @param[in,out] r le rail a initialisé
**/
int initRail(Rail* r);

/**
* @brief ajoute une caractere au rail
* @param[in] r le rail
* @param[in] l le caractere a ajouter
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE) le cote duquel on ajoute l
* @return le caractere qui "tombe" du rail
**/
char ajouteRail(Rail* r, const char l, int sens);

/**
* @brief affiche un rail
* @param[in] r le rail
**/
void afficherRail(Rail* r);

/**
* @brief ajoute un mot au rail
* @param[in] r le rail
* @param[in] m le mot a ajouter
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE) le cote duquel on ajoute m
* @return le mot qui "tombe" du rail
**/
char* ajouteMotRail(Rail* r, const char* m, int sens);

/**
* @brief recupere le mot sur le rail
* @param[in] r le rail
* @param[in] nb le nombre de caractere sur le rail
* @param[in] sens (0 ou 1 donc GAUCHE OU DROITE)
* @return le mot sur le rail
**/
char* recupMotRail(Rail* rail, int nb, int sens);

/**
* @brief cree l inverse d'un rail
* @param[in] r le rail dont on veut connaitre l inverse
* @return l'inverse du rail 
**/
Rail inverseRail(const Rail* rail);

void test_Rail();

