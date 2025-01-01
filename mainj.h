#pragma once

#include "pioche.h"

/**
 * @brief Type Main.
 */
typedef Pioche Main;

/**
* @brief Initialise la main du joueur.
*/
void initMain(Main* main);

/**
* @brief Ajoute une lettre � la main du joueur.
*/
void ajouteMain(Main* main, char lettre);

/**
* @brief Retire la lettre � un indice donn� de la main.
*/
char retireMain(Main* main, int indice);

/**
* @brief Pr�pare les deux mains n�cessaires pour l'Octo-verso.
*/
void prepareMainsJeu(Pioche* pioche,Main* mainJ1,Main* mainJ2);