#pragma once
#include "pioche.h"
#include "mainj.h"
#include "rail.h"

/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
*/
void lancerPartie(Pioche* pioche, Main* J1, Main* J2, Rail* rail);

/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
*/
void deroulePartie(Main* J1, Main* J2);

/**
* @brief Affiche les mains des joueurs et l'état du rail.
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

