#pragma once

#include "mot.h"
/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
* @param[in,out] pioche la pioche de jeu.
* @param[in,out] mainJ1 la main du joueur 1.
* @param[in,out] mainJ2 la main du joueur 2.
* @param[in,out] mainJ1Ant la main du joueur 1 au tour précédent.
* @param[in,out] mainJ2Ant la main du joueur 2 au tour précédent.
* @param[in,out] rail le rail de jeu.
* @param[in,out] railAnt le rail de jeu au tour précédent.
*/
void lancerPartie(Pioche* pioche, Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt);


/**
* @brief Propose à un joueur de jouer un tour.
* @param[in] joueur le joueur dont c'est le tour.
* @param[in] RoV le premier caractere du coup
* @param[in] mot le mot proposé.
* @return 0 si le coup est valide 1 sinon
*/
int proposeJouer(const char* joueur, char* RoV, char* mot);

/**
* @brief Propose à un joueur de retirer un des chevalets de sa main.
* @param[in,out] pioche la pioche de jeu.
* @param[in,out] mainJ la main du joueur qui retire un chevalet de sa main.
* @param[in] joueur 1 ou 2
* return 0 si le chevalet a été retiré correctement 1 sinon
*/
int proposeRetraitChevalet(Main* mainJ, Pioche* pioche, const char* joueur);

/**
* @brief Gère les tours du jeu.
* @param[in,out] mainJ1 la main du joueur 1.
* @param[in,out] mainJ2 la main du joueur 2.
* @param[in] mainJ1Ant la main du joueur 1 au tour précédent.
* @param[in] mainJ2Ant la main du joueur 2 au tour précédent.
* @param[in] joueur le joueur dont c'est le tour.
* @param[in,out] rail le rail de jeu.
* @param[in] railAnt le rail de jeu au tour précédent.
* @param[in,out] pioche la pioche de jeu.
* @return 0 si le tour se passe bien 1 sinon
*/
int gereTours(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
* @param[in,out] mainJ1 la main du joueur 1.
* @param[in,out] mainJ2 la main du joueur 2.
* @param[in] mainJ1Ant la main du joueur 1 au tour précédent.
* @param[in] mainJ2Ant la main du joueur 2 au tour précédent.
* @param[in,out] rail le rail de jeu.
* @param[in] railAnt le rail de jeu au tour précédent.
* @param[in,out] pioche la pioche de jeu.
*/
void deroulePartie(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail, Rail* railAnt, Pioche* pioche);

/**
* @brief Affiche les mains des joueurs et l'état du rail.
* @param[in] mainJ1 la main du joueur 1.
* @param[in] mainJ2 la main du joueur 2.
* @param[in] rail le rail de jeu.
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);
