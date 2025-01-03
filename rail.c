#include "rail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mainj.h"


int initRail(Rail* rail)
{
    for (int i = 0; i <= Last; i++)
        rail->lettres[i] = ' ';
    return 0;
}


void ajtRail(Rail* rail, const char l, int sens) {
    if (sens == GAUCHE) {
        // Décaler toutes les lettres vers la droite
        for (int i = Last; i > 0; i--) {
            rail->lettres[i] = rail->lettres[i - 1];
        }
        rail->lettres[0] = l; // Ajouter à la première position
    }
    else if (sens == DROITE) {
        // Décaler toutes les lettres vers la gauche
        for (int i = 0; i < Last; i++) {
            rail->lettres[i] = rail->lettres[i + 1];
        }
        rail->lettres[Last] = l; // Ajouter à la dernière position
    }

}


void affRail(Rail* rail)
{
    printf("R : ");
    // Affichage côté recto (de 0 à 8)
    for (int i = 0; i <= Last; i++) {
        printf("%c", rail->lettres[i]);

    }
    // Affichage de la séparation entre recto et verso
    printf(" \nV : ");
    // Affichage côté verso (de 8 à 0)
    for (int i = Last; i >= 0; i--) {
        printf("%c", rail->lettres[i]);

    }
    printf("\n");
}


void ajtMotRail(Rail* rail, const char* m, int sens) {
    int longueur = strlen(m);
    if (sens == GAUCHE) {
        for (int i = longueur - 1; i >= 0; i--) {
            ajtRail(rail, m[i], GAUCHE); // Insérer de gauche à droite
        }
    }
    else if (sens == DROITE) {
        for (int i = 0; i < longueur; i++) {
            ajtRail(rail, m[i], DROITE); // Insérer de droite à gauche
        }
    }
}

char* recupMotRail(Rail* rail, int nb, int sens) {
    // Valider les arguments
    if (nb <= 0 || nb > MAX_RAIL) {
        return NULL; // Retourner NULL si le nombre de caractères est invalide
    }

    // Allouer de la mémoire pour le mot récupéré
    char* mot = (char*)malloc((nb + 1) * sizeof(char));
    if (!mot) {
        return NULL; // Retourner NULL si l'allocation échoue
    }

    // Lire les caractères selon le sens
    if (sens == GAUCHE) {
        for (int i = 0; i < nb; i++) {
            mot[i] = rail->lettres[i]; // Lire depuis le début
        }
    }
    else if (sens == DROITE) {
        for (int i = 0; i < nb; i++) {
            mot[i] = rail->lettres[Last - i]; // Lire depuis la fin
        }
    }

    mot[nb] = '\0'; // Ajouter le caractère de fin de chaîne
    return mot;
}




