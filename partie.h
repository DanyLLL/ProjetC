#pragma once
#include "mot.h"

/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
*/
void lancerPartie(Pioche* pioche, Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt);



/**
* @brief Propose à un joueur de jouer un tour.
*/
int proposeJouer(const char* joueur, char* RoV, char* mot);



/**
* @brief Propose à un joueur de retirer un des chevalets de sa main.
*/
int proposeRetraitChevalet(Main* mainJ, Pioche* pioche, const char* joueur);



/**
* @brief Gère les tours du jeu.
*/
int gereTours(Main* mainJ1, Main* mainJ2,Main* mainJ1Ant,Main* mainJ2Ant, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche);



/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
*/
void deroulePartie(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt, Pioche* pioche);



/**
* @brief Affiche les mains des joueurs et l'état du rail.
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);
