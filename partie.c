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
    if (strlen(RoV) == 1 && strlen(mot) >= 5 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0)) {
        return 0;
    }
    else {
        return 1;
    }
}

int jouerTour(const char* joueur, char* RoV, char* mot) {
    printf("\n%s>", joueur);
    scanf("%s %s", RoV, mot);
    printf("\n%s %s %d %d\n", RoV, mot, strlen(mot),strlen(RoV));
    return coupValide(RoV, mot);
}

int gereTours(Main* J1, Main* J2,const char* joueur) {
    char mot_J1[MAX_MOT], mot_J2[MAX_MOT];
    char RoV[MAX_ROV];
    while (1){
        if (jouerTour(joueur, RoV, mot_J1) == 0) {
            if (strcmp(RoV, "R") == 0) {
                return 0;
            }
            else if (strcmp(RoV, "V") == 0) {
                return 0;
            }
            else {
                return 1;
            }
        }
        else {
            return 1;
        }
    }
}

void deroulePartie(Main* J1, Main* J2) {
    assert(J1->ordre != NULL && J2->ordre != NULL);
    int ordre;
    while (J1->nb != 0 || J2->nb != 0) {
        if (J1->ordre == 1) {
            while (gereTours(J1, J2, "1") != 0) {
                gereTours(J1, J2, "1");
            }
            while (gereTours(J1, J2, "2") != 0) {
                gereTours(J1, J2, "2");
            }
        }
        else {
            while (gereTours(J1, J2, "2") != 0) {
                gereTours(J1, J2, "2");
            }
            while (gereTours(J1, J2, "1") != 0) {
                gereTours(J1, J2, "1");
            }
        }
    }
}



