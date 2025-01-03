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


char ajtRail(Rail* r, const char l, int sens) {
    char tombe = ' ';
    if (sens == GAUCHE) {
        // Décaler toutes les lettres vers la droite
        tombe = r->lettres[Last];
        for (int i = Last; i > 0; i--) {
            r->lettres[i] = r->lettres[i - 1];
        }

        r->lettres[0] = l; // Ajouter à la première position
    }
    else if (sens == DROITE) {
        char tombe = r->lettres[0]; // Conserver l'élément qui "tombe" à gauche
        // Décaler toutes les lettres vers la gauche
        for (int i = 0; i < Last; i++) {
            r->lettres[i] = r->lettres[i + 1];
        }
        // Ajouter la nouvelle lettre à la fin (sens de lecture conservé)
        r->lettres[Last] = l;
        return tombe;
    }
}


void affRail(Rail* rail){
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


char* ajtMotRail(Rail* r, const char* m, int sens) {
    int longueur = strlen(m);
    char* tombe = (char*)malloc(longueur + sizeof(char));
    int ind = 0;
    if (sens == GAUCHE) {
        for (int i = longueur - 1; i >= 0; i--) {
            tombe[ind++] = ajtRail(r, m[i], GAUCHE);

        }
    }
    else if (sens == DROITE) {
        for (int i = 0; i < longueur; i++) {
            tombe[ind++] = ajtRail(r, m[i], DROITE);
        }

    }
    tombe[ind] = '\0';
    return tombe;
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
            mot[i] = rail->lettres[Last - (nb - 1) + i];
        }
    }

    printf("mot %s\n", mot);
    mot[nb] = '\0'; // Ajouter le caractère de fin de chaîne
    return mot;
}





