#pragma once
#include "mainj.h"


/**
* @brief V�rifie si le mot existe dans un dictionnaire donn�
*/
int motExiste(const char* mot);

/**
* @brief V�rifie si le mot est jouable, c'est-�-dire si le joueur a dans sa main les lettres n�cessaires pour constituer le mot.
*/
int motJouable(const char* mot, Main* mainJ);

/**
* @brief Compare la proximit� � la lettre A d'un motJ1 avec un motJ2. 
*/
int comparerProximiteA(const char* motJ1, const char* motJ2);

/**
* @brief V�rifie lequel des deux mots est le plus proche de A.
*/
char* motPlusProcheDeA(const char* motJ1, const char* motJ2);

/**
* @brief D�termine l'ordre de jeu.
*/
int deterOrdreJeu(Main* mainJ1, Main* mainJ2);

