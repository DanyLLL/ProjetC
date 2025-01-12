#pragma once
#include "mainj.h"
#include "rail.h"

enum { MAX_MOT_DEP = 5, MAX_MOT = 15 ,MAX_HORS_PARENTHESES = 6, MIN_HORS_PARENTHESES = 1,MIN_ENTRE_PARENTHESES = 2, MAX_ENTRE_PARENTHESES = 7,MAX_LIGNE = 256};

int triAlphabetique(const void* a, const void* b);


/**
* @brief Vérifie si le mot existe dans un dictionnaire donné
*/
int motExiste(const char* mot, const char* dico);

/**
* @brief Vérifie si le mot est jouable, c'est-à-dire si le joueur a dans sa main les lettres nécessaires pour constituer le mot.
*/
int motJouable(const char* mot, Main* mainJ);

/**
* @brief Compare la proximité à la lettre A d'un motJ1 avec un motJ2.
*/
int comparerProximiteA(const char* motJ1, const char* motJ2);

/**
* @brief Vérifie lequel des deux mots est le plus proche de A.
*/
int joueurPlusProcheDeA(const char* motJ1, const char* motJ2);

/**
* @brief Concatène les deux mots en commençant par celui le plus proche de A.
*/
char* concateneMotProcheDeA(const char* motJ1, const char* motJ2);

/**
* @brief 
*/
const char* extraireParenthesesEtMot(const char* chaine, char** entreParenthese, char** horsParenthese);
/**
* @brief Détermine l'ordre de jeu.
*/
void deterOrdreJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

char* concatParenthesesEtHors(const char* chaine);

/**
* @brief Vérifie si un coup est légal.
*/
int coupLegal(Main* mainJCourant, Main* mainJAdverse, Main* mainJCourantAnt, Main* mainJAdverseAnt, Rail* rail, Rail* railAnt, const char* motJ, const char* RoV);


int estOcto(const char* mot);

int mainContientMot(const char* mot, Main* main);

int signalementValide(Pioche* pioche, Main* mainJCourant, Main* mainJAdverse, Rail* railAnt, const char* motJ, const char* joueur);
