#pragma once

#include "pioche.h"
#include "rail.h"
/**
 * @brief Type Main.
 */
typedef Pioche Main;

/**
* @brief Initialise la main du joueur.
* @param[in,out] main
*/
void initMain(Main* main);

/**
* @brief Ajoute une lettre à la main du joueur.
* @param[in,out] main
* @param[in] lettre
*/
void ajouteMain(Main* main, char lettre);

/**
* @brief Retire la lettre à un indice donné de la main.
* @param[in,out] main
* @param[in] indice
* @return la lettre retiree
*/
char retireMain(Main* main, int indice);

/**
* @brief Prépare les deux mains nécessaires pour l'Octo-verso.
* @param[in,out] pioche
* @param[in,out] mainJ1
* @param[in,out] mainJ2
*/
void prepareMainsJeu(Pioche* pioche,Main* mainJ1,Main* mainJ2);

void test_Mainj();
