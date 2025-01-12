#pragma once
#include "mainj.h"
#include "rail.h"

enum { MAX_MOT_DEP = 5, MAX_MOT = 15 ,MAX_HORS_PARENTHESES = 6, MIN_HORS_PARENTHESES = 1,MIN_ENTRE_PARENTHESES = 2, MAX_ENTRE_PARENTHESES = 7,MAX_LIGNE = 256};

/**
* @brief Vérifie si a est plus proche de A alphabétiquement que b.
*/
int triAlphabetique(const void* a, const void* b);


/**
* @brief Vérifie si le mot existe dans un dictionnaire donné
*/
int motExiste(const char* mot, const char* dico);

/**
* @brief Vérifie si le joueur a dans sa main les lettres nécessaires pour constituer le mot et retire les lettres concernées de la main.
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
* @brief Sépare la partie hors et entre parenthèses du coup joué.
*/
const char* extraireParenthesesEtMot(const char* chaine, char** entreParenthese, char** horsParenthese);
/**
* @brief Détermine l'ordre de jeu.
*/
void deterOrdreJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

/**
* @brief Concatène la partie hors et entre parenthèses du coup joué.
*/
char* concatEntreEtHorsParentheses(const char* chaine);

/**
* @brief Vérifie si le mot est un octo (mot de longueur de 8).
*/
int estOcto(const char* mot);

/**
* @brief Vérifie si le joueur a dans sa main les lettres nécessaires pour constituer le mot sans retirer les lettres concernées de la main.
*/
int mainContientMot(const char* mot, Main* main);

/**
* @brief Vérifie si le coup du joueur est valide aux règles du jeu.
*/
int coupValide(const char* RoV, const char* mot);


/**
* @brief Vérifie si un coup est légal.
*/
int coupLegal(Main* mainJCourant, Main* mainJAdverse, Main* mainJCourantAnt, Main* mainJAdverseAnt, Rail* rail, Rail* railAnt, const char* motJ, const char* RoV);


/**
* @brief Vérifie si un signalement est valide en recto.
*/
int signalementValide(Pioche* pioche, Main* mainJCourant, Main* mainJAdverse, Rail* railAnt, const char* motJ, const char* joueur);
