#pragma once
#include "mainj.h"



enum { MAX_MOT_DEP = 5, MAX_MOT = 15 ,MAX_HORS_PARENTHESES = 6, MIN_HORS_PARENTHESES = 1,MIN_ENTRE_PARENTHESES = 2, MAX_ENTRE_PARENTHESES = 7,MAX_LIGNE = 256};

/**
* @brief Vérifie si a est plus proche de A alphabétiquement que b.
* @param[in] a 
* @param[in] b 
* @return 
*/
int triAlphabetique(const void* a, const void* b);


/**
* @brief Vérifie si le mot existe dans un dictionnaire donné
* @param[in] mot le mot a tester
* @param[in] dico le dictionnaire
* @return 0 si oui 1 si non
*/
int motExiste(const char* mot, const char* dico);

/**
* @brief Vérifie si le joueur a dans sa main les lettres nécessaires pour constituer le mot et retire les lettres concernées de la main.
* @param[in] mot a tester
* @param[in,out] mainJ la main qu on teste et ajuste si le mot est jouable
* @return 0 si oui 1 si non
*/
int motJouable(const char* mot, Main* mainJ);

/**
* @brief Compare la proximité à la lettre A d'un motJ1 avec un motJ2.
** @param[in] motJ1
* @param[in] motJ2
* @return -1 si non, 1 si oui et 0 si le mot ont la meme proximite
*/
int comparerProximiteA(const char* motJ1, const char* motJ2);

/**
* @brief Vérifie lequel des deux mots est le plus proche de A.
** @param[in] motJ1
* @param[in] motJ2
* @return 1 si le joueur 1 est le plus proche, 2 si non
*/
int joueurPlusProcheDeA(const char* motJ1, const char* motJ2);

/**
* @brief Concatène les deux mots en commençant par celui le plus proche de A.
** @param[in] motJ1
* @param[in] motJ2
* @return la concatenation des deux mots
*/
char* concateneMotProcheDeA(const char* motJ1, const char* motJ2);

/**
* @brief Sépare la partie hors et entre parenthèses du coup joué.
* @param[in] chaine le coup du joueur
* @param[in,out] entreParenthese mot vide qu on va remplir des caractere entre parentheses
* @param[in,out] horsParenthses mot vide qu on va remplir des caractere entre parentheses
* @return 0 si le mot doit aller a gauche sinon 1 donc droite
*/
const char* extraireParenthesesEtMot(const char* chaine, char** entreParenthese, char** horsParenthese);


/**
* @brief Détermine l'ordre de jeu.
*  @param[in,out] mainJ1 la main du joueur 1 dont on va indiquer l ordre dans la partie
*  @param[in,out] mainJ2 la main du joueur 2 dont on va indiquer l ordre dans la partie
*  @param[in,out] rail le rail dont on va ajouter la concatenation des mots
*/
void deterOrdreJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

/**
* @brief Concatène la partie hors et entre parenthèses du coup joué.
* @param[in] chaine le coup du joueur
* @return le mot du coup sans les parentheses
*/
char* concatEntreEtHorsParentheses(const char* chaine);

/**
* @brief Vérifie si le mot est un octo (mot de longueur de 8).
* @param[in] mot le mot joue
* @return 0 si il est octo 1 si non
*/
int estOcto(const char* mot);

/**
* @brief Vérifie si le joueur a dans sa main les lettres nécessaires pour constituer le mot sans retirer les lettres concernées de la main.
* @param[in] mot le coup du joueur
* @param[in] main la main du joueur
* @return 0 si oui 1 si non
*/
int mainContientMot(const char* mot, Main* main);

/**
* @brief Vérifie si le coup du joueur est valide aux règles du jeu.
* @param[in] RoV le premier caractere du coup du joueur
* @param[in] mot le mot joué
* @return 0 si le coup est valide 1 si non
*/
int coupValide(const char* RoV, const char* mot);


/**
* @brief Vérifie si un coup est légal.
* @param[in,out] mainJCourant 
* @param[in,out] mainJAdverse 
* @param[in] mainJCourantAnt 
* @param[in] mainJAdverseAnt
* @param[in,out] rail
* @param[in] railAnt 
* @param[in] MotJ 
* @param[in] RoV 
* @return 0 si le coup est legal 1 si non
*/
int coupLegal(Main* mainJCourant, Main* mainJAdverse, Main* mainJCourantAnt, Main* mainJAdverseAnt, Rail* rail, Rail* railAnt, const char* motJ, const char* RoV);


/**
* @brief Vérifie si un signalement est valide en recto.
* @param[in,out] pioche
* @param[in,out] mainJCourant
* @param[in,out] mainJAdverse
* @param[in] railAnt
* @param[in] motJ
* @param[in] joueur
* @return 0 si le signalement est valide 1 si non
*/
int signalementValide(Pioche* pioche, Main* mainJCourant, Main* mainJAdverse, Rail* railAnt, const char* motJ, const char* joueur);
