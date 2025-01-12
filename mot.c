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
            return 0;  // Le mot a été trouvé
        }
    }
    fclose(f);
    return 1;  // Le mot n'a pas été trouvé
}



int motJouable(const char* mot, Main* mainJ) {
    char* chevaletTemp = malloc((strlen(mainJ->chevalets) + 1) * sizeof(char));
    if (!chevaletTemp) {
        return 1; // Allocation ratée
    }
    strcpy(chevaletTemp, mainJ->chevalets);

    // On vérifie si le mot est jouable
    for (int i = 0; i < strlen(mot); i++) {
        int lettreTrouvee = 0;
        for (int j = 0; j < strlen(mainJ->chevalets) + 1; j++) {
            if (chevaletTemp[j] == mot[i]) {
                lettreTrouvee = 1;
                chevaletTemp[j] = '*'; // '*' pour marquer la lettre comme utilisée et éviter les doublons
                break;
            }
        }
        if (lettreTrouvee == 0) {
            free(chevaletTemp); // On libère la mémoire allouée
            return 1; // Le mot n'est pas jouable
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
        return 1; // motJ1 est plus proche de A
    }
    else {
        return 2; // motJ2 est plus proche de A
    }
}



char* concateneMotProcheDeA(const char* motJ1, const char* motJ2) {
    assert(motJ1 != NULL && motJ2 != NULL);
    const char* mots[] = { motJ1, motJ2 };
    qsort(mots, 2, sizeof(const char*), comparerProximiteA);
    size_t tailleNouvelleChaine = strlen(mots[0]) + strlen(mots[1]) + 1;
    char* resultat = (char*)malloc(tailleNouvelleChaine); // On alloue la mémoire nécessaire
    if (resultat == NULL) {
        return NULL;
    }
    strcpy(resultat, mots[0]);
    strcat(resultat, mots[1]); // On concatène de sorte à avoir le mot le plus proche de A à gauche

    return resultat;
}



const char* extraireParenthesesEtMot(const char* chaine, char** entreParenthese, char** horsParenthese) {
    *entreParenthese = malloc(sizeof(char));
    (*entreParenthese)[0] = '\0';
    *horsParenthese = malloc(sizeof(char));
    (*horsParenthese)[0] = '\0';

    int entreParentheses = 0;
    int parenthesesVues = -1; // -1: indéterminé, 0: vu horsParenthese d'abord, 1: vu entreParentheses d'abord

    for (int i = 0; chaine[i] != '\0'; i++) {
        if (chaine[i] == '(') {
            entreParentheses = 1; // Début du contenu entre parenthèses
            if (parenthesesVues == -1) {
                parenthesesVues = 1; // entre parenthèses vues en premier
            }
        }
        else if (chaine[i] == ')') {
            entreParentheses = 0; // Fin du contenu entre parenthèses
        }
        else {
            char** target = entreParentheses ? entreParenthese : horsParenthese;
            if (!entreParentheses && parenthesesVues == -1) {
                parenthesesVues = 0; // hors parenthèses vues en premier
            }
            size_t len = strlen(*target);
            *target = realloc(*target, len + 2); // // On realloue la mémoire nécessaire
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
        if (strlen(mot_dep_J1) == MAX_MOT_DEP - 1 && motExiste(mot_dep_J1, "ods4.txt") == 0 && motJouable(mot_dep_J1, mainJ1) == 0) { //Si le mot de départ est de 4, qu'il est jouable et qu'il existe dans le dico.
            motJ1Valide = 1;
        }
    }
    while (motJ2Valide == 0) {
        printf("2> ");
        scanf("%s", mot_dep_J2);
        if (strlen(mot_dep_J2) == MAX_MOT_DEP - 1 && motExiste(mot_dep_J2, "ods4.txt") == 0 && motJouable(mot_dep_J2, mainJ2) == 0 && strcmp(mot_dep_J1,mot_dep_J2) == 1) { //Si le mot de départ est de 4, qu'il est jouable et qu'il existe dans le dico.
            motJ2Valide = 1;
        }
    }
    ajouteMotRail(rail, concateneMotProcheDeA(mot_dep_J1, mot_dep_J2), 0); //On ajoute les deux mots dans le rail dans l'ordre alphabétique.
    if (joueurPlusProcheDeA(mot_dep_J1, mot_dep_J2) == 1) { // Détermine qui joue en premier après les mots de départ.
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

    char* resultat = malloc(strlen(chaine) + 1); // On alloue la mémoire nécessaire.
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
    if (strlen(mot) == 8) { // Est-ce un octo ?
        return 0; // C'est un octo.
    }
    return 1; // Ce n'est pas un octo.
}



int mainContientMot(const char* mot, Main* main) {
    // Copie temporaire du chevalet pour éviter de modifier la main réelle.
    char* chevaletTemp = malloc((strlen(main->chevalets) + 1) * sizeof(char));
    if (!chevaletTemp) {
        return 1; // Allocation ratée.
    }
    strcpy(chevaletTemp, main->chevalets);

    // Vérifie si chaque lettre du mot est présente dans la main du joueur
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
            return 1; // Le mot n'est pas jouable.
        }
    }

    free(chevaletTemp);
    return 0; // Toutes les lettres sont présentes, le mot est jouable.
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
    if (strlen(RoV) == 1 && (strcmp(RoV, "R") == 0 || strcmp(RoV, "V") == 0 || strcmp(RoV, "r") == 0 || strcmp(RoV, "v") == 0 || strcmp(RoV, "-") == 0)) { // S'il s'agit d'un des coups possibles du jeu Octo-Verso.
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
    if (motLegal(motJ, entreParentheses, horsParentheses) == 0) { // Si le mot est légal.
        if (motExiste(concatEntreEtHorsParentheses(motJ), "ods4.txt") == 0) { // Si le mot existe.
            if (strcmp(entreParentheses, recupMotRail(rail, strlen(entreParentheses), extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses))) == 0) { // Si l'extrémité du rail correspond aux lettres entre parenthèses
                strcpy(mainJCourantAnt->chevalets, mainJCourant->chevalets); //Ici on enregistre les mains des joueurs et le rail au tour antérieur.
                strcpy(mainJAdverseAnt->chevalets, mainJAdverse->chevalets);
                strcpy(railAnt->lettres, rail->lettres);
                if (motJouable(horsParentheses, mainJCourant) == 0) { // Si le mot est jouable.
                    if (extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses) == GAUCHE) { // Si le mot est inseré par la gauche.
                        for (int i = strlen(horsParentheses) - 1; i >= 0; i = i - 1) {
                            ajouteMain(mainJAdverse, ajouteRail(rail, horsParentheses[i], GAUCHE)); // On ajoute à la main adverse ce qui tombe du rail tout en ajoutant les lettres hors parenthèses.
                        }
                        return 0;
                    }
                    else if (extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses) == DROITE) { // Si le mot est inseré par la droite.
                        for (int i = 0; i < strlen(horsParentheses); i = i + 1) {
                            ajouteMain(mainJAdverse, ajouteRail(rail, horsParentheses[i], DROITE)); //On ajoute à la main adverse ce qui tombe du rail tout en ajoutant les lettres hors parenthèses.
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
    if (motLegal(motJ, entreParentheses, horsParentheses) == 0) { // Si le mot est légal.
        if (strcmp(entreParentheses, recupMotRail(railAnt, strlen(entreParentheses), extraireParenthesesEtMot(motJ, &entreParentheses, &horsParentheses))) == 0) { // Si l'extrémité du rail correspond aux lettres entre parenthèses
            if (mainContientMot(horsParentheses, mainJAdverseAnt) == 0) { // Si le joueur possède bien les lettres pour effectuer le mot.
                if (estOcto(concatEntreEtHorsParentheses(motJ)) == 0) { // S'il s'agit bien d'un octo (mot de 8 lettres).
                    while (proposeRetraitChevalet(mainJCourant, pioche, joueur) == 1) { // Il peut retirer un de ses chevalets.
                    }
                    return 0;
                }
            }
        }
    }
}
