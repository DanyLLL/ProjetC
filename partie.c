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
    deroulePartie(J1, J2, rail);
}

void afficheSituationCouranteJeu(Main* mainJ1, Main* mainJ2, Rail* rail) {
    qsort(mainJ1->chevalets, strlen(mainJ1->chevalets), sizeof(char), triAlphabetique);
    qsort(mainJ2->chevalets, strlen(mainJ2->chevalets), sizeof(char), triAlphabetique);
    printf("\n1 : %s\n", mainJ1->chevalets);
    printf("2 : %s\n", mainJ2->chevalets);
    affRail(rail);
}

int coupValide(const char* RoV, const char* mot) {
    if (strlen(RoV) == 1 && strlen(mot) >= 6 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0)) {
        return 0;
    }
    else {
        return 1;
    }
}

int jouerTour(const char* joueur, char* RoV, char* mot) {
    printf("\n%s>", joueur);
    scanf("%s %s", RoV, mot);
    return coupValide(RoV, mot);
}

int gereTours(Main* J1, Main* J2,const char* joueur,Rail* rail) {
    char mot_J1[MAX_MOT], mot_J2[MAX_MOT];
    char RoV[MAX_ROV];
    while (1){
        if (joueur == "1") {
            if (jouerTour(joueur, RoV, mot_J1) == 0) {
                char* entreParentheses = NULL;
                char* horsParentheses = NULL;
                if (strcmp(RoV, "R") == 0) {
                    if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J1), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), GAUCHE)) == 0)) {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J2, ajtRail(rail, horsParentheses[i], GAUCHE));
                                    }
                                    printf("1 : %s\n", J1->chevalets);
                                    printf("2 : %s\n", J2->chevalets);
                                    return 0;
                                }
                                else {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J1, horsParentheses[i]);
                                    }
                                    qsort(J1->chevalets, strlen(J1->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                            else {
                                return 1;
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J1), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), DROITE)) == 0)) {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J2, ajtRail(rail, horsParentheses[i], DROITE));
                                    }
                                    printf("1 : %s AAAAAA\n", J1->chevalets);
                                    printf("2 : %s\n", J2->chevalets);
                                    return 0;
                                }
                                else {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J1, horsParentheses[i]);
                                    }
                                    qsort(J1->chevalets, strlen(J1->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
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
                else if (strcmp(RoV, "V") == 0) {
                    Rail railVerso;
                    initRail(&railVerso);
                    railVerso = inverseRail(rail);
                    if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J1), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), GAUCHE)) == 0)) {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J2, ajtRail(&railVerso, horsParentheses[i], GAUCHE));
                                    }
                                    railVerso = inverseRail(&railVerso);
                                    strcpy(rail->lettres, railVerso.lettres);
                                    return 0;
                                }
                                else {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J1, horsParentheses[i]);
                                    }
                                    qsort(J1->chevalets, strlen(J1->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                        else {
                            return 1;
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J1, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J1), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J1) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), DROITE)) == 0)) {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J2, ajtRail(&railVerso, horsParentheses[i], DROITE));
                                    }
                                    railVerso = inverseRail(&railVerso);
                                    strcpy(rail->lettres, railVerso.lettres);
                                    return 0;
                                }
                                else {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J1, horsParentheses[i]);
                                    }
                                    qsort(J1->chevalets, strlen(J1->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                        else {
                            return 1;
                        }
                    }
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
            if (jouerTour(joueur, RoV, mot_J2) == 0) {
                char* entreParentheses = NULL;
                char* horsParentheses = NULL;
                if (strcmp(RoV, "R") == 0) {
                    if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J2), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), GAUCHE)) == 0)) {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J1, ajtRail(rail, horsParentheses[i], GAUCHE));
                                    }
                                    return 0;
                                }
                                else {
                                    for (int i = 0; i <= strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J2, horsParentheses[i]);
                                    }
                                    qsort(J2->chevalets, strlen(J2->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J2), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), DROITE)) == 0)) {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J1, ajtRail(rail, horsParentheses[i], DROITE));
                                    }
                                    return 0;
                                }
                                else {
                                    for (int i = 0; i <= strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J2, horsParentheses[i]);
                                    }
                                    qsort(J2->chevalets, strlen(J2->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                    }
                }
                else if (strcmp(RoV, "V") == 0) {
                    Rail railVerso;
                    initRail(&railVerso);
                    railVerso = inverseRail(rail);
                    if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == GAUCHE) { //Le mot du joueur est rentré par la gauche
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J2), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), GAUCHE)) == 0)) {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J1, ajtRail(&railVerso, horsParentheses[i], GAUCHE));
                                    }
                                    railVerso = inverseRail(&railVerso);
                                    strcpy(rail->lettres, railVerso.lettres);
                                    return 0;
                                }
                                else {
                                    for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                                        ajouteMain(J2, horsParentheses[i]);
                                    }
                                    qsort(J2->chevalets, strlen(J2->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                    }
                    else if (extraireParenthesesEtMot(mot_J2, &entreParentheses, &horsParentheses) == DROITE) { //Le mot du joueur est rentré par la droite
                        if (strlen(horsParentheses) >= 1 && strlen(entreParentheses) >= 2) {
                            if (motExiste(concatParenthesesEtHors(mot_J2), "ods4.txt") == 0 && (strcmp(mot_J1, mot_J2) == 1)) {
                                if ((motJouable(horsParentheses, J2) == 0) && (strcmp(entreParentheses, recupMotRail(&railVerso, strlen(entreParentheses), DROITE)) == 0)) {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J1, ajtRail(&railVerso, horsParentheses[i], DROITE));
                                    }
                                    railVerso = inverseRail(&railVerso);
                                    strcpy(rail->lettres, railVerso.lettres);
                                    return 0;
                                }
                                else {
                                    for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                                        ajouteMain(J2, horsParentheses[i]);
                                    }
                                    qsort(J2->chevalets, strlen(J2->chevalets), sizeof(char), triAlphabetique);
                                    return 1;
                                }
                            }
                        }
                    }
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

void deroulePartie(Main* J1, Main* J2,Rail* rail) {
    assert(J1->ordre != NULL && J2->ordre != NULL);
    int ordre;
    while (J1->nb != 0 || J2->nb != 0) {
        if (J1->ordre == 1) {
            while (gereTours(J1, J2, "1",rail) != 0) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
                while (gereTours(J1, J2, "2", rail) != 0) {
                }
                afficheSituationCouranteJeu(J1, J2, rail);
        }
        else {
            while (gereTours(J1, J2, "2", rail) != 0) {
            }
            afficheSituationCouranteJeu(J1, J2, rail);
                while (gereTours(J1, J2, "1", rail) != 0) {
                }
                afficheSituationCouranteJeu(J1, J2, rail);
        }
    }
}



