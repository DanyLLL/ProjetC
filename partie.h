#pragma once
#include "pioche.h"
#include "mainj.h"
#include "rail.h"

/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
*/
void lancerPartie(Pioche* pioche, Main* J1, Main* J2, Rail* rail);

/**
* @brief Vérifie si le coup du joueur est valide aux règles du jeu.
*/
int coupValide(const char* RoV, const char* mot);

/**
* @brief Permet à un joueur de jouer un tour.
*/
int jouerTour(const char* joueur, char* RoV, char* mot);

/**
* @brief Gère les tours du jeu.
*/
int gereTours(Main* J1, Main* J2, const char* joueur, Rail* rail);

/**
* @brief Déroule la partie après avoir décidé de l'ordre de jeu.
*/
void deroulePartie(J1, J2, rail);

/**
* @brief Affiche les mains des joueurs et l'état du rail.
*/
void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail);

