#include "rail.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int initRail(Rail* r)
{
    for (int i = 0; i <= Last; i++)
        r->lettres[i] = ' ';
    return 0;
}


void ajtRail(Rail* r, const char l, int sens) {
    if (sens == GAUCHE) {
        // Décaler toutes les lettres vers la droite
        for (int i = Last; i > 0; i--) {
            r->lettres[i] = r->lettres[i - 1];
        }
        r->lettres[0] = l; // Ajouter à la première position
    }
    else if (sens == DROITE) {
        // Décaler toutes les lettres vers la gauche
        for (int i = 0; i < Last; i++) {
            r->lettres[i] = r->lettres[i + 1];
        }
        r->lettres[Last] = l; // Ajouter à la dernière position
    }

}


void affRail(Rail* r)
{
    printf("R : ");
    // Affichage côté recto (de 0 à 8)
    for (int i = 0; i <= Last; i++) {
        printf("%c", r->lettres[i]);

    }
    // Affichage de la séparation entre recto et verso
    printf(" \nV : ");
    // Affichage côté verso (de 8 à 0)
    for (int i = Last; i >= 0; i--) {
        printf("%c", r->lettres[i]);

    }
    printf("\n");
}


void ajtMotRail(Rail* r, const char* m, int sens) {
    int longueur = strlen(m);
    if (sens == GAUCHE) {
        for (int i = longueur - 1; i >= 0; i--) {
            ajtRail(r, m[i], GAUCHE); // Insérer de gauche à droite
        }
    }
    else if (sens == DROITE) {
        for (int i = 0; i < longueur; i++) {
            ajtRail(r, m[i], DROITE); // Insérer de droite à gauche
        }
    }
}




