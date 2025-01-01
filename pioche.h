#pragma once

enum {
	/**
	* @brief Nombre de chevalets distincts .
	*/
	NB_CHEVALET = 88
};

/**
 * @brief Type Pioche .
*/
typedef struct {
	int nb; /// < Nombre de chevalets dans la pioche .
	char* chevalets; /// < Chevalets dans la pioche .
} Pioche;

/**
* @brief Initialise la pioche.
*/
void initPioche(Pioche* pioche);

/**
* @brief Ajoute une lettre � la pioche.
*/
void ajoutePioche(Pioche* pioche, char lettre);

/**
* @brief Retire la lettre � un indice donn� de la pioche.
*/
char retirePioche(Pioche* pioche,int indice);

/**
* @brief Pr�pare les diff�rentes lettres n�cessaires pour l'Octo-verso.
*/
void preparePiocheJeu(Pioche* pioche);