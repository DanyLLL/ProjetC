#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "partie.h"
#include "mainj.h"
#include "mot.h"
#include "rail.h"

#pragma warning(disable : 4996)


void lancerPartie(Pioche* pioche, Main* J1, Main* J2, Rail* rail) {
    preparePiocheJeu(pioche);
    prepareMainsJeu(pioche, J1, J2);
    deterOrdreJeu(J1, J2, rail);
    afficheSituationCouranteJeu(J1, J2, rail);
    deroulePartie(J1, J2);
}

void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail) {
    printf("\n1 : %s\n", mainJ1->chevalets);
    printf("2 : %s\n", mainJ2->chevalets);
    affRail(rail);
}

int coupValide(const char* RoV, const char* mot) {
    return strlen(RoV) == 1 && strlen(mot) >= 6 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0);
}

void jouerTour(const char* joueur, char* RoV, char* mot) {
    printf("\n%s>", joueur);
    scanf("%s %s", RoV, mot);
    printf("\n%s %s\n", RoV, mot);
}

void gereTours(Main* J1, Main* J2) {
    char mot_J1[MAX_MOT], mot_J2[MAX_MOT];
    char RoVJ1[MAX_ROV], RoVJ2[MAX_ROV];
    int joueurCourant = J1->ordre == 1 ? 1 : 2;

    while (J1->nb != 0 || J2->nb != 0)
        if (joueurCourant == 1)
            jouerTour("1", RoVJ1, mot_J1);
            if (coupValide(RoVJ1, mot_J1))
                jouerTour("2", RoVJ2, mot_J2);
                if (coupValide(RoVJ2, mot_J2))
                    if (strcmp(RoVJ1, "R") == 0 && strcmp(RoVJ2, "R") == 0)
                        printf("premiere issue\n");
                    else if (strcmp(RoVJ1, "R") == 0 && strcmp(RoVJ2, "V") == 0)
                        printf("seconde issue\n");
                    else if (strcmp(RoVJ1, "V") == 0 && strcmp(RoVJ2, "R") == 0)
                        printf("troisieme issue\n");
                    else
                        printf("quatrieme issue\n");
        else
            jouerTour("2", RoVJ2, mot_J2);
            if (coupValide(RoVJ2, mot_J2))
                jouerTour("1", RoVJ1, mot_J1);
                if (coupValide(RoVJ1, mot_J1))
                    if (strcmp(RoVJ2, "V") == 0 && strcmp(RoVJ1, "V") == 0)
                        printf("cinquieme issue\n");
                    else if (strcmp(RoVJ2, "V") == 0 && strcmp(RoVJ1, "R") == 0)
                        printf("sixieme issue\n");
                    else if (strcmp(RoVJ2, "R") == 0 && strcmp(RoVJ1, "V") == 0) 
                        printf("septieme issue\n");
                    else
                        printf("huitieme issue\n");
        joueurCourant = 3 - joueurCourant;
}

void deroulePartie(Main* J1, Main* J2) {
    assert(J1->ordre != NULL && J2->ordre != NULL);
    gereTours(J1, J2);
}



