#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mot.h"
#pragma warning(disable : 4996)


int triAlphabetique(const void* a, const void* b) {
    char charA = *(char*)a;
    char charB = *(char*)b;
    return (charA - charB);
}



int motExiste(const char* mot, const char* dico) {
    // Ouvre le fichier en mode lecture
    FILE* f = fopen(dico, "r");
    if (f == NULL) {
        printf("Fichier non accessible\n");
        return 1; // Erreur, fichier inaccessible
    }

    char ligne[MAX_LIGNE];
    while (fgets(ligne, sizeof(ligne), f)) {
        // Supprime le caractère de fin de ligne '\n'
        ligne[strcspn(ligne, "\n")] = '\0';
        if (strcmp(ligne, mot) == 0) {
            fclose(f);
            return 0;  // Mot trouvé
        }
    }
    fclose(f);
    return 1;  // Mot non trouvé
}



int motJouable(const char* mot, Main* mainJ) {
    char* chevaletTemp = malloc((strlen(mainJ->chevalets) + 1) * sizeof(char));
    if (!chevaletTemp) {
        return 1; // Échec de l'allocation mémoire
    }
    strcpy(chevaletTemp, mainJ->chevalets);

    // Vérifier si le mot est jouable
    for (int i = 0; i < strlen(mot); i++) {
        int lettreTrouvee = 0;
        for (int j = 0; j < strlen(mainJ->chevalets) + 1; j++) {
            if (chevaletTemp[j] == mot[i]) {
                lettreTrouvee = 1;
                chevaletTemp[j] = '*'; // '*' pour marquer la lettre comme utilisée
                break;
            }
        }
        if (lettreTrouvee == 0) {
            free(chevaletTemp); // Libérer la mémoire allouée
            return 1; // Mot non jouable
        }
    }

    // Si le mot est jouable, retirer les lettres de la main réelle
    for (int i = 0; i < strlen(mot); i++) {
        for (int j = strlen(mainJ->chevalets) - 1; j >= 0; j--) {
            if (mainJ->chevalets[j] == mot[i]) {
                retireMain(mainJ, j);
                break;  // Après avoir retiré une lettre, ajuster l'indice
            }
        }
    }
    free(chevaletTemp); // Libérer la mémoire allouée après utilisation
    return 0; // Mot jouable
}



int comparerProximiteA(const char* a, const char* b) {
    const char* mot1 = *(const char**)a;
    const char* mot2 = *(const char**)b;

    while (*mot1 != '\0' && *mot2 != '\0') {
        int distance1 = *mot1 - 'A';
        int distance2 = *mot2 - 'A';

        if (distance1 < 0) distance1 = -distance1;
        if (distance2 < 0) distance2 = -distance2;

        if (distance1 != distance2) {
            return distance1 - distance2;
        }

        mot1++;
        mot2++;
    }

    return (*mot1 == '\0') - (*mot2 == '\0');
}



int joueurPlusProcheDeA(const char* motJ1, const char* motJ2) {
    assert(motJ1 != NULL && motJ2 != NULL);
    const char* mots[] = { motJ1, motJ2 };
    qsort(mots, 2, sizeof(const char*), comparerProximiteA);
    if (motJ1 == mots[0]) {
        return 1;
    }
    else {
        return 2;
    }
}



char* concateneMotProcheDeA(const char* motJ1, const char* motJ2) {
    assert(motJ1 != NULL && motJ2 != NULL);
    const char* mots[] = { motJ1, motJ2 };
    qsort(mots, 2, sizeof(const char*), comparerProximiteA);
    size_t tailleNouvelleChaine = strlen(mots[0]) + strlen(mots[1]) + 1;
    char* resultat = (char*)malloc(tailleNouvelleChaine);
    if (resultat == NULL) {
        return NULL;
    }
    strcpy(resultat, mots[0]);
    strcat(resultat, mots[1]);

    return resultat;
}



const char* extraireParenthesesEtMot(const char* chaine, char** entreParenthese, char** horsParenthese) {
    *entreParenthese = malloc(sizeof(char));
    (*entreParenthese)[0] = '\0';
    *horsParenthese = malloc(sizeof(char));
    (*horsParenthese)[0] = '\0';

    int entreParentheses = 0;
    int parenthesesVues = -1; // -1: indéterminé, 0: horsParenthese d'abord, 1: entreParentheses d'abord

    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == '(') {
            entreParentheses = 1; // Début du contenu entre parenthèses
            if (parenthesesVues == -1) {
                parenthesesVues = 1; // Les parenthèses viennent d'abord
            }
        }
        else if (chaine[i] == ')') {
            entreParentheses = 0; // Fin du contenu entre parenthèses
        }
        else {
            char** target = entreParentheses ? entreParenthese : horsParenthese;
            if (!entreParentheses && parenthesesVues == -1) {
                parenthesesVues = 0; // horsParentheses vient d'abord
            }
            size_t len = strlen(*target);
            *target = realloc(*target, len + 2); // Redimensionner pour un nouveau caractère
            (*target)[len] = chaine[i];
            (*target)[len + 1] = '\0';
        }
    }

    return (parenthesesVues == 0) ? GAUCHE : DROITE;
}



void deterOrdreJeu(Main* mainJ1, Main* mainJ2, Rail* rail) {
    char mot_dep_J1[MAX_MOT_DEP];
    char mot_dep_J2[MAX_MOT_DEP];
    int motJ1Valide = 0;
    int motJ2Valide = 0;
    while (motJ1Valide == 0) {
        printf("1> ");
        scanf("%s", mot_dep_J1);
        if (strlen(mot_dep_J1) == MAX_MOT_DEP - 1 && motExiste(mot_dep_J1, "ods4.txt") == 0 && motJouable(mot_dep_J1, mainJ1) == 0) {
            motJ1Valide = 1;
        }
    }
    while (motJ2Valide == 0) {
        printf("2> ");
        scanf("%s", mot_dep_J2);
        if (strlen(mot_dep_J2) == MAX_MOT_DEP - 1 && motExiste(mot_dep_J2, "ods4.txt") == 0 && motJouable(mot_dep_J2, mainJ2) == 0 && strcmp(mot_dep_J1,mot_dep_J2) == 1) {
            motJ2Valide = 1;
        }
    }
    ajouteMotRail(rail, concateneMotProcheDeA(mot_dep_J1, mot_dep_J2), 0);
    if (joueurPlusProcheDeA(mot_dep_J1, mot_dep_J2) == 1) {
        mainJ1->ordre = 1;
        mainJ2->ordre = 2;
    }
    else {
        mainJ2->ordre = 1;
        mainJ1->ordre = 2;
    }
}



char* concatEntreEtHorsParentheses(const char* chaine) {
    if (!chaine) return NULL;

    char* resultat = malloc(strlen(chaine) + 1);
    int indexRes = 0, dansParentheses = 0;

    for (int i = 0; chaine[i]; i++) {
        if (chaine[i] == '(')
            dansParentheses = 1;
        else if (chaine[i] == ')')
            dansParentheses = 0;
        else if (dansParentheses || chaine[i] != '(')
            resultat[indexRes++] = chaine[i];
    }
    resultat[indexRes] = '\0';
    return resultat;
}



int estOcto(const char* mot) {
    if (strlen(mot) == 8) {
        return 0;
    }
    return 1;
}



int mainContientMot(const char* mot, Main* main) {
    // Copie temporaire du chevalet pour éviter de modifier la main réelle
    char* chevaletTemp = malloc((strlen(main->chevalets) + 1) * sizeof(char));
    if (!chevaletTemp) {
        return 1; // Échec de l'allocation mémoire
    }
    strcpy(chevaletTemp, main->chevalets);

    // Vérifie si chaque lettre du mot est présente dans le chevalet
    for (int i = 0; i < strlen(mot); i++) {
        int lettreTrouvee = 0;
        for (int j = 0; j < strlen(chevaletTemp); j++) {
            if (chevaletTemp[j] == mot[i]) {
                lettreTrouvee = 1;
                chevaletTemp[j] = '*'; // '*' pour marquer la lettre comme utilisée
                break;
            }
        }
        if (lettreTrouvee == 0) {
            free(chevaletTemp);
            return 1; // Lettre manquante, mot non formable
        }
    }

    free(chevaletTemp);
    return 0; // Toutes les lettres sont présentes
}



int motLegal(const char* mot,const char* entreParentheses,const char* horsParentheses) {
    if (strlen(horsParentheses) <= MAX_HORS_PARENTHESES && strlen(horsParentheses) >= MIN_HORS_PARENTHESES){
        if (strlen(entreParentheses) >= MIN_ENTRE_PARENTHESES && strlen(entreParentheses) <= MAX_ENTRE_PARENTHESES && strlen(concatEntreEtHorsParentheses(mot)) <= MAX_RAIL) {
            return 0;
        }
    }
    else {
        return 1;
    }
}



int coupValide(const char* RoV, const char* mot) {
    if (strlen(RoV) == 1 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0 || strcmp(RoV, "r") == 0 || strcmp(RoV, "v") == 0 || strcmp(RoV, "-") == 0)) {
        return 0;
    }
    else {
        return 1;
    }
}



int coupLegal(Main* mainJCourant,Main* mainJAdverse,Main* mainJCourantAnt,Main* mainJAdverseAnt,Rail* rail,Rail* railAnt,const char* motJ,const char* RoV) {
    char* entreParentheses = NULL;
    char* horsParentheses = NULL;
    extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses);
    if (motLegal(motJ, entreParentheses, horsParentheses) == 0) {
        if (motExiste(concatEntreEtHorsParentheses(motJ), "ods4.txt") == 0) {
            if (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses))) == 0) {
                strcpy(mainJCourantAnt->chevalets, mainJCourant->chevalets);
                strcpy(mainJAdverseAnt->chevalets, mainJAdverse->chevalets);
                strcpy(railAnt->lettres, rail->lettres);
                printf("%s %s aa \n", mainJCourantAnt->chevalets, mainJAdverseAnt->chevalets);
                if (motJouable(horsParentheses, mainJCourant) == 0) {
                    if (extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses) == GAUCHE) {
                        for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                            ajouteMain(mainJAdverse, ajouteRail(rail, horsParentheses[i], GAUCHE));
                        }
                        return 0;
                    }
                    else if (extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses) == DROITE) {
                        for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                            ajouteMain(mainJAdverse, ajouteRail(rail, horsParentheses[i], DROITE));
                        }
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}




int signalementValide(Pioche* pioche,Main* mainJCourant,Main* mainJAdverseAnt, Rail* railAnt,const char* motJ,const char* joueur) {
    char* entreParentheses = NULL;
    char* horsParentheses = NULL;
    extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses);
    if (motLegal(motJ, entreParentheses, horsParentheses) == 0) {
        printf("%s %s\n", mainJAdverseAnt->chevalets, railAnt->lettres);
        if (strcmp(entreParentheses, recupMotRail(railAnt, strlen(entreParentheses), extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses))) == 0) {
            if (mainContientMot(horsParentheses, mainJAdverseAnt) == 0) {
                if (estOcto(concatEntreEtHorsParentheses(motJ)) == 0) {
                    while (proposeRetraitChevalet(mainJCourant, pioche, joueur) == 1) {
                    }
                    return 0;
                }
            }
        }
    }
}
