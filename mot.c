#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mot.h"
#include "mainj.h"
#include "rail.h"
#pragma warning(disable : 4996)


int motExiste(const char* mot,const char* dico) {
    // Ouvre le fichier en mode lecture
    FILE* f = fopen(dico, "r");
    if (f == NULL) {
        printf("Fichier non accessible\n");
        return 1; // Erreur, fichier inaccessible
    }

    char ligne[256];
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
    for (int i = 0; i < strlen(mot); i++) {
        int lettreTrouvee = 0;
        for (int j = 0; j < strlen(mainJ->chevalets); j++) {
            if (mainJ->chevalets[j] == mot[i]) {
                lettreTrouvee = 1;
            }
        }
        if (!lettreTrouvee) {
            return 0; // Mot non jouable
        }
    }

    // Si toutes les lettres sont trouvées, maintenant on retire les lettres de la main
    for (int i = 0; i < strlen(mot); i++) {
        for (int j = 0; j < strlen(mainJ->chevalets); j++) {
            if (mainJ->chevalets[j] == mot[i]) {
                // Retirer la lettre de la main
                retireMain(mainJ, j);
                break;
            }
        }
    }
    return 1; // Mot jouable
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
    if (motJ1 == mots[0]){
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

void deterOrdreJeu(Main* mainJ1, Main* mainJ2,Rail* rail) {
    char mot_dep_J1[MAX_MOT_DEP];
    char mot_dep_J2[MAX_MOT_DEP];
    int motJ1Valide = 0;
    int motJ2Valide = 0;
    while (motJ1Valide == 0) {
        printf("1> ");
        scanf("%s", mot_dep_J1);
        if (strlen(mot_dep_J1) == 4 && motExiste(mot_dep_J1,"ods4.txt") == 0 && motJouable(mot_dep_J1, mainJ1)) {
            motJ1Valide = 1;
        }
    }
    while (motJ2Valide == 0) {
        printf("2> ");
        scanf("%s", mot_dep_J2);
        if (strlen(mot_dep_J2) == 4 && motExiste(mot_dep_J2, "ods4.txt") == 0 && motJouable(mot_dep_J2, mainJ2)) {
            motJ2Valide = 1;
        }
    }
    ajtMotRail(rail,concateneMotProcheDeA(mot_dep_J1, mot_dep_J2),0);
    if (joueurPlusProcheDeA(mot_dep_J1, mot_dep_J2) == 1) {
        mainJ1->ordre = 1;
        mainJ2->ordre = 2;
    }
    else {
        mainJ2->ordre = 1;
        mainJ1->ordre = 2;
    }
}


