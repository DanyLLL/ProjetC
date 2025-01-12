#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "partie.h"
#include "mot.h"

#pragma warning(disable : 4996)


void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail) {
    // Tri puis affichage des mains et du rail.
    qsort(mainJ1->chevalets, strlen(mainJ1->chevalets), sizeof(char), triAlphabetique);
    qsort(mainJ2->chevalets, strlen(mainJ2->chevalets), sizeof(char), triAlphabetique);
    printf("\n1 : %s\n", mainJ1->chevalets);
    printf("2 : %s\n", mainJ2->chevalets);
    afficherRail(rail);
}


int proposeJouer(const char* joueur, char* RoV, char* mot) {
    printf("\n%s>", joueur);
    scanf("%s %s", RoV, mot);
    return coupValide(RoV, mot);
}

int proposeRetraitChevalet(Main* mainJ, Pioche* pioche, const char* joueur) {
    printf("\n-%s> ", joueur);
    char lettre[2];
    scanf("%s", lettre);
    if (strlen(lettre) == 1 && motJouable(lettre, mainJ) == 0) { // S'il s'agit bien d'une seule lettre et qu'elle est dans la main du joueur.
        return 0;
    }
    return 1;
}

int gereTours(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche) {
    char mot[MAX_MOT];
    char RoV[MAX_ROV];
    Rail railVerso;
    initRail(&railVerso);
    Rail railVersoAnt;
    initRail(&railVersoAnt);
    if (proposeJouer(joueur, RoV, mot) == 0) {
        if (strcmp(joueur, "1") == 0){ // Il s'agit du joueur 1.
            if (strcmp(RoV, "R") == 0) { // Le joueur joue 1 le recto.
                if (coupLegal(mainJ1,mainJ2,mainJ1Ant, mainJ2Ant,rail,railAnt, mot,RoV) == 0) {
                    if (estOcto(concatEntreEtHorsParentheses(mot)) == 0) { // S'il s'agit d'un octo (mot de 8 lettres).
                        afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                        while (proposeRetraitChevalet(mainJ1, pioche, joueur) == 1) { // Il peut retirer un des chevalets de sa main.
                        }
                    }
                    return 0;
                }
                return 1;
            }
            else if (strcmp(RoV, "V") == 0) { // Le joueur 1 joue le verso.
                railVerso = inverseRail(rail); // On inverse le rail pour le verso.
                if (coupLegal(mainJ1, mainJ2, mainJ1Ant, mainJ2Ant, &railVerso,railAnt, mot,RoV) == 0) {
                    railVerso = inverseRail(&railVerso); // On reinverse le rail pour pouvoir le copier coller correctement dans le rail de jeu.
                    strcpy(rail->lettres, &railVerso.lettres);
                    if (estOcto(concatEntreEtHorsParentheses(mot)) == 0) { // S'il s'agit d'un octo (mot de 8 lettres).
                        afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                        while (proposeRetraitChevalet(mainJ1, pioche, joueur) == 1) { // Il peut retirer un des chevalets de sa main.
                        }
                    }
                    return 0;
                }
                return 1;
            }
            else if (strcmp(RoV, "-") == 0) { // Le joueur 1 pioche.
                if (strlen(mot) == 1 && motJouable(mot, mainJ1) == 0) { // S'il s'agit bien d'une seule lettre et qu'elle est dans la main du joueur.
                    srand(time(NULL));
                    int i1 = rand() % (pioche->nb - 1);
                    ajouteMain(mainJ1, pioche->chevalets[i1]); // On ajoute à la main du joueur une lettre aléatoire de la pioche.
                    retirePioche(pioche, i1); // On retire cette lettre de la pioche.
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else if (strcmp(RoV, "r") == 0) { // Le joueur 1 signale en recto.
                if(signalementValide(pioche, mainJ1, mainJ1Ant, railAnt, mot, "1") == 0) {
                    afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                    return 1;
                }
            }
            else if (strcmp(RoV, "v") == 0) { // Le joueur 1 signale en verso.
                railVersoAnt = inverseRail(railAnt);
                if (signalementValide(pioche, mainJ1, mainJ1Ant, &railVersoAnt, mot, "1") == 0) {
                    afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                    return 1;
                }
            }
        }
        else if (strcmp(joueur,"2") == 0) { // Il s'agit du joueur 2.
            if (strcmp(RoV, "R") == 0) { // Le joueur 2 joue le recto.
                if (coupLegal(mainJ2, mainJ1,mainJ1Ant,mainJ2Ant, rail,railAnt, mot, RoV) == 0) {
                    if (estOcto(concatEntreEtHorsParentheses(mot)) == 0) {
                        afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                        while (proposeRetraitChevalet(mainJ2, pioche, joueur) == 1) {
                        }
                    }
                    return 0;
                }
                return 1;
            }
            else if (strcmp(RoV, "V") == 0) { // Le joueur 2 joue le verso.
                railVerso = inverseRail(rail); // On inverse le rail pour le verso.
                if (coupLegal(mainJ2, mainJ1,mainJ1Ant,mainJ2Ant, &railVerso,railAnt, mot, RoV) == 0) {
                    railVerso = inverseRail(&railVerso); // On reinverse le rail pour pouvoir le copier coller correctement dans le rail de jeu.
                    strcpy(rail->lettres, &railVerso.lettres);
                    if (estOcto(concatEntreEtHorsParentheses(mot)) == 0) { // S'il s'agit d'un octo (mot de 8 lettres).
                        afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                        while (proposeRetraitChevalet(mainJ2, pioche, joueur) == 1) { // Il peut retirer un des chevalets de sa main.
                        }
                    }
                    return 0;
                }
                return 1;
            }
            else if (strcmp(RoV, "-") == 0) { // Le joueur 2 pioche.
                if (strlen(mot) == 1 && motJouable(mot, mainJ2) == 0) { // S'il s'agit bien d'une seule lettre et qu'elle est dans la main du joueur.
                    srand(time(NULL));
                    int i1 = rand() % (pioche->nb - 1);
                    ajouteMain(mainJ2, pioche->chevalets[i1]); // On ajoute à la main du joueur une lettre aléatoire de la pioche.
                    retirePioche(pioche, i1); // On retire cette lettre de la pioche.
                    return 0;
                }
                else {
                    return 1;
                }
            }
            else if (strcmp(RoV, "r") == 0) {  // Le joueur 2 signale en recto.
                if (signalementValide(pioche, mainJ2, mainJ1Ant, railAnt, mot, "2") == 0) {
                    afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                    return 1;
                }
            }
            else if (strcmp(RoV, "v") == 0) { // Le joueur 2 signale en verso.
                railVersoAnt = inverseRail(railAnt);
                if (signalementValide(pioche, mainJ2, mainJ1Ant, &railVersoAnt, mot, "2") == 0) {
                    afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
                    return 1;
                }
            }
        }
    }
}

void deroulePartie(Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail,Rail* railAnt, Pioche* pioche) {
    assert(mainJ1->ordre != NULL && mainJ2->ordre != NULL);
    while (mainJ1->nb != 0 || mainJ2->nb != 0) {
        if (mainJ1->ordre == 1) {
            while (gereTours(mainJ1, mainJ2,mainJ1Ant,mainJ2Ant, "1", rail,railAnt, pioche) == 1) {
            }
            if (mainJ1->nb == 0 || mainJ2->nb == 0) break; // Si la partie est finie.
            afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
            while (gereTours(mainJ1, mainJ2, mainJ1Ant, mainJ2Ant, "2", rail, railAnt, pioche) == 1) {
            }
            if (mainJ1->nb == 0 || mainJ2->nb == 0) break; // Si la partie est finie.
            afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
        }
        else {
            while (gereTours(mainJ1, mainJ2, mainJ1Ant, mainJ2Ant, "2", rail, railAnt, pioche) == 1) {
            }
            if (mainJ1->nb == 0 || mainJ2->nb == 0) break; // Si la partie est finie.
            afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
            while (gereTours(mainJ1, mainJ2, mainJ1Ant, mainJ2Ant, "1", rail, railAnt, pioche) == 1) {
            }
            if (mainJ1->nb == 0 || mainJ2->nb == 0) break; // Si la partie est finie.
            afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
        }
    }
}

void lancerPartie(Pioche* pioche, Main* mainJ1, Main* mainJ2, Main* mainJ1Ant, Main* mainJ2Ant, Rail* rail,Rail* railAnt) {
    preparePiocheJeu(pioche);
    prepareMainsJeu(pioche, mainJ1, mainJ2);
    deterOrdreJeu(mainJ1, mainJ2, rail);
    afficheSituationCouranteJeu(mainJ1, mainJ2, rail);
    deroulePartie(mainJ1, mainJ2, mainJ1Ant, mainJ2Ant, rail,railAnt, pioche);
}
