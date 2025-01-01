#pragma once
#include "mainj.h"
#include "rail.h"

/**
* @brief Vérifie si le mot existe dans un dictionnaire donné
*/
int motExiste(const char* mot);

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
* @brief Détermine l'ordre de jeu.
*/
int deterOrdreJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

