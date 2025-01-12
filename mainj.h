#pragma once

#include "pioche.h"
#include "rail.h"
/**
 * @brief Type Main.
 */
typedef Pioche Main;

/**
* @brief Initialise la main du joueur.
* @param[in,out] main la main à initialiser.
*/
void initMain(Main* main);

/**
* @brief Ajoute une lettre à la main du joueur.
* @param[in,out] main la main dont on ajoute une lettre.
* @param[in] lettre la lettre ajoutée.
*/
void ajouteMain(Main* main, char lettre);

/**
* @brief Retire la lettre à un indice donné de la main.
* @param[in,out] main la main dont on retire une lettre.
* @param[in] indice l'indice auquel on souhaite retirer la lettre.
* @return la lettre retirée.
*/
char retireMain(Main* main, int indice);

/**
* @brief Prépare les deux mains nécessaires pour l'Octo-verso.
* @param[in,out] pioche la pioche du jeu.
* @param[in,out] mainJ1 la main du joueur 1.
* @param[in,out] mainJ2 la main du joueur 2.
*/
void prepareMainsJeu(Pioche* pioche, Main* mainJ1, Main* mainJ2);

/**
* @brief Teste les fonctions spécifiques du composant mainj.
*/
void test_Mainj();
