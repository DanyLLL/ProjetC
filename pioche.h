#pragma once

enum {
	/**
	* @brief Nombre de chevalets distincts .
	*/
	NB_CHEVALET = 88
};


enum {NB_A = 9,NB_C = 2,NB_D = 3,NB_E = 14,NB_I = 7,NB_L = 5, NB_M = 3, NB_N = 6, NB_O = 5, NB_P = 2,NB_R = 6,NB_S = 7,NB_T = 6,NB_U = 5,NB_V = 2};

/**
 * @brief Type Pioche .
*/
typedef struct {
	int nb; /// < Nombre de chevalets dans la pioche .
	int ordre; /// < Ordre de jeu du joueur .
	char* chevalets; /// < Chevalets dans la pioche .
} Pioche;

/**
* @brief Initialise la pioche.
* @param[in,out] pioche
*/
void initPioche(Pioche* pioche);

/**
* @brief Ajoute une lettre à la pioche.
* @param[in,out] pioche
* @param[in] lettre
*/
void ajoutePioche(Pioche* pioche, char lettre);

/**
* @brief Retire la lettre à un indice donné de la pioche.
* @param[in,out] pioche
* @param[in] indice
* @return la lettre retiree
*/
char retirePioche(Pioche* pioche,int indice);

/**
* @brief Prépare les différentes lettres nécessaires pour l'Octo-verso.
* @param[in,out] pioche
*/
void preparePiocheJeu(Pioche* pioche);


void test_pioche();
