#pragma once
#include "pioche.h"
#include "mainj.h"
/**
* @brief Lance toutes les fonctions permettant de lancer la partie.
*/
void lancerPartie(Pioche* pioche, Main* J1, Main* J2);

void deroulePartie(Main* J1, Main* J2);

void afficheSituationCouranteJeu(Main* J1, Main* J2);