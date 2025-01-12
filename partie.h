#pragma once

#include "mot.h"
/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
* @param[in,out] pioche
* @param[in,out] mainJ1
* @param[in,out] mainJ2
* @param[in,out] mainJ1Ant
* @param[in,out] mainJ2Ant
* @param[in,out] rail
* @param[in,out] railAnt
*/
void lancerPartie(Pioche* pioche, Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt);


/**
* @brief Propose à un joueur de jouer un tour.
* @param[in] joueur
* @param[in] RoV le premier caractere du coup
* @param[in] mot
* @return 0 si le coup est valide 1 si non
*/
int proposeJouer(const char* joueur, char* RoV, char* mot);

/**
* @brief Propose à un joueur de retirer un des chevalets de sa main.
* @param[in,out] pioche
* @param[in,out] mainJ
* @param[in] joueur 1 ou 2
* return 0 si le chevalet est retirable 1 si non
*/
int proposeRetraitChevalet(Main* mainJ, Pioche* pioche, const char* joueur);

/**
* @brief Gère les tours du jeu.
* @param[in,out] mainJ1
* @param[in,out] mainJ2
* @param[in] mainJ1Ant
* @param[in] mainJ2Ant
* @param[in] joueur
* @param[in,out] rail
* @param[in] railAnt
* @param[in,out] pioche
* @return 0 si le tour se passe bien 1 si non
*/
int gereTours(Main* mainJ1, Main* mainJ2,Main* mainJ1Ant,Main* mainJ2Ant, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
* @param[in,out] mainJ1
* @param[in,out] mainJ2
* @param[in] mainJ1Ant
* @param[in] mainJ2Ant
* @param[in] joueur
* @param[in,out] rail
* @param[in] railAnt
* @param[in,out] pioche
*/
void deroulePartie(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Affiche les mains des joueurs et l'état du rail.
* @param[in] mainJ1
* @param[in] mainJ2
* @param[in] rail
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);
