#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "partie.h"
#include "mainj.h"
#include "mot.h"
#include "rail.h"

#pragma warning(disable : 4996)


void lancerPartie(Pioche* pioche, Main* J1, Main* J2, Rail* rail,Rail* railAnt) {
    preparePiocheJeu(pioche);
    prepareMainsJeu(pioche, J1, J2);
    deterOrdreJeu(J1, J2, rail);
    afficheSituationCouranteJeu(J1, J2, rail);
    deroulePartie(J1, J2, rail,railAnt, pioche);
}

void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail) {
    qsort(mainJ1->chevalets, strlen(mainJ1->chevalets), sizeof(char), triAlphabetique);
    qsort(mainJ2->chevalets, strlen(mainJ2->chevalets), sizeof(char), triAlphabetique);
    printf("\n1 : %s\n", mainJ1->chevalets);
    printf("2 : %s\n", mainJ2->chevalets);
    affRail(rail);
}

int coupValide(const char* RoV, const char* mot) {
    if (strlen(RoV) == 1 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0 || strcmp(RoV, "-") == 0 || strcmp(RoV, "r") == 0 || strcmp(RoV, "v") == 0)) {
        return 0;
    }
    else {
        return 1;
    }
}

int proposeJouer(const char* joueur, char* RoV, char* mot) {
    printf("\n%s>", joueur);
    scanf("%s %s", RoV, mot);
    return coupValide(RoV, mot);
}

int proposeRetraitChevalet(Main* mainJ, Pioche* pioche,const char* joueur) {
    printf("\n-%s> ",joueur);
    char lettre[2];
    scanf("%s",lettre);
    if (strlen(lettre) == 1 && motJouable(lettre,mainJ) == 0) {
        return 0;
    }
    return 1;
}



int gereTours(Main* J1, Main* J2, const char* joueur, Rail* rail, Rail* railAnt, Pioche* pioche) {
    char mot_J1[MAX_MOT], mot_J2[MAX_MOT];
    char RoV[MAX_ROV];
    char* entreParentheses = NULL;
    char* horsParentheses = NULL;
    while (1) {
        if (joueur == "1") {
            if (proposeJouer(joueur, RoV, mot_J1) == 0) {
                if (strcmp(RoV, "R") == 0 ) {
                    if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (coupLegal(mot_J1, &entreParentheses, &horsParentheses) == 0) {
                            if (motJouable(horsParentheses, J1) == 0 && strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), GAUCHE)) == 0) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J2, ajtRail(rail, horsParentheses[i], GAUCHE));
                                }
                                if (estOcto(concatParenthesesEtHors(mot_J1) == 0)) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J1, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J1, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (coupLegal(mot_J1, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), DROITE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J2, ajtRail(rail, horsParentheses[i], DROITE));
                                }
                                if (estOcto(concatParenthesesEtHors(mot_J1)) == 0) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J1, pioche, joueur) == 1) {
                                    }
                                }
                                return 0;
                            }
                            else {
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J1, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                }
                else if (strcmp(RoV, "V") == 0) {
                    Rail railVerso;
                    initRail(&railVerso);
                    railVerso = inverseRail(rail);
                    if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (coupLegal(mot_J1, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), GAUCHE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J2, ajtRail(&railVerso, horsParentheses[i], GAUCHE));
                                }
                                railVerso = inverseRail(&railVerso);
                                strcpy(rail->lettres, railVerso.lettres);
                                if (estOcto(concatParenthesesEtHors(mot_J1) == 0)) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J1, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J1, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (coupLegal(mot_J1, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), DROITE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J2, ajtRail(&railVerso, horsParentheses[i], DROITE));
                                }
                                railVerso = inverseRail(&railVerso);
                                strcpy(rail->lettres, railVerso.lettres);
                                if (estOcto(concatParenthesesEtHors(mot_J1) == 0)) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J1, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J1, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                }
                else if (strcmp(RoV, "-") == 0) {
                    if (strlen(mot_J1) == 1 && motJouable(mot_J1, J1) == 0) {
                        srand(time(NULL));
                        int i1 = rand() % (pioche->nb - 1);
                        ajouteMain(J1, pioche->chevalets[i1]);
                        retirePioche(pioche, i1);
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                else if (strcmp(RoV, "r") == 0) {
                    printf("%s \n", railAnt->lettres);
                }
                else if (strcmp(RoV, "v") == 0) {
                    printf("%s \n", railAnt->lettres);
                }
                else {
                    return 1;
                }
            }
            else {
                return 1;
            }
        }
        else if (joueur == "2") {
            if (proposeJouer(joueur, RoV, mot_J2) == 0) {
                if (strcmp(RoV, "R") == 0) {
                    if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (coupLegal(mot_J2, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), GAUCHE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J1, ajtRail(rail, horsParentheses[i], GAUCHE));
                                }
                                if (estOcto(concatParenthesesEtHors(mot_J2)) == 0) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J2, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = 0; i <= strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J2, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (coupLegal(mot_J2, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), DROITE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J1, ajtRail(rail, horsParentheses[i], DROITE));
                                }
                                if (estOcto(concatParenthesesEtHors(mot_J2)) == 0) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J2, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = 0; i <= strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J2, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                }
                else if (strcmp(RoV, "V") == 0) {
                    Rail railVerso;
                    initRail(&railVerso);
                    railVerso = inverseRail(rail);
                    if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (coupLegal(mot_J2, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), GAUCHE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J1, ajtRail(&railVerso, horsParentheses[i], GAUCHE));
                                }
                                railVerso = inverseRail(&railVerso);
                                strcpy(rail->lettres, railVerso.lettres);
                                if (estOcto(concatParenthesesEtHors(mot_J2)) == 0) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J2, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else {
                                for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                    ajouteMain(J2, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (coupLegal(mot_J2, &entreParentheses, &horsParentheses) == 0) {
                            if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), DROITE)) == 0)) {
                                strcpy(railAnt->lettres, rail->lettres);
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J1, ajtRail(&railVerso, horsParentheses[i], DROITE));
                                }
                                railVerso = inverseRail(&railVerso);
                                strcpy(rail->lettres, railVerso.lettres);
                                if (estOcto(concatParenthesesEtHors(mot_J2)) == 0) {
                                    afficheSituationCouranteJeu(J1, J2, rail);
                                    while (proposeRetraitChevalet(J2, pioche, joueur) == 1) {
                                    }
                                    return 0;
                                }
                                return 0;
                            }
                            else{
                                for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                    ajouteMain(J2, horsParentheses[i]);
                                }
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                }
                else if (strcmp(RoV, "-") == 0) {
                    if (strlen(mot_J2) == 1 && motJouable(mot_J2, J2) == 0) {
                        srand(time(NULL));
                        int i1 = rand() % (pioche->nb - 1);
                        ajouteMain(J2, pioche->chevalets[i1]);
                        retirePioche(pioche, i1);
                        return 0;
                    }
                    else {
                        return 1;
                    }
                }
                else if (strcmp(RoV, "r") == 0) {
                    printf("%s \n", railAnt->lettres);
                }
                else if (strcmp(RoV, "v") == 0) {
                    printf("%s \n", railAnt->lettres);
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
}

void deroulePartie(Main* J1, Main* J2, Rail* rail,Rail* railAnt, Pioche* pioche) {
    assert(J1->ordre != NULL && J2->ordre != NULL);
    int ordre;
    while (J1->nb != 0 || J2->nb != 0) {
        if (J1->ordre == 1) {
            while (gereTours(J1, J2, "1", rail, pioche,railAnt) == 1) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
            while (gereTours(J1, J2, "2", rail, pioche,railAnt) == 1) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
        }
        else {
            while (gereTours(J1, J2, "2", rail, pioche, railAnt) == 1) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
            while (gereTours(J1, J2, "1", rail, pioche, railAnt) == 1) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
        }
    }
}


