#pragma once
#include "pioche.h"
#include "mainj.h"
#include "rail.h"

/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
*/
void lancerPartie(Pioche* pioche, Main* J1, Main* J2, Rail* rail,Rail* railAnt);

/**
* @brief Vérifie si le coup du joueur est valide aux règles du jeu.
*/
int coupValide(const char* RoV, const char* mot);

/**
* @brief Permet à un joueur de jouer un tour.
*/
int jouerTour(const char* joueur, char* RoV, char* mot);

/**
* @brief Vérifie si un coup est légal.
*/
int coupLegal(const char* motJ, const char* horsParentheses, const char* entreParentheses);

/**
* @brief Gère les tours du jeu.
*/

int gereTours(Main* J1, Main* J2, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
*/
void deroulePartie(Main* J1, Main* J2, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Affiche les mains des joueurs et l'état du rail.
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);
