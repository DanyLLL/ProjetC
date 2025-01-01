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
        // D�caler toutes les lettres vers la droite
        for (int i = Last; i > 0; i--) {
            r->lettres[i] = r->lettres[i - 1];
        }
        r->lettres[0] = l; // Ajouter � la premi�re position
    }
    else if (sens == DROITE) {
        // D�caler toutes les lettres vers la gauche
        for (int i = 0; i < Last; i++) {
            r->lettres[i] = r->lettres[i + 1];
        }
        r->lettres[Last] = l; // Ajouter � la derni�re position
    }

}


void affRail(Rail* r)
{ 
	printf("R : ");
    // Affichage c�t� recto (de 0 � 8)
    for (int i = 0; i <= Last; i++) {
         printf("%c", r->lettres[i]);
        
    }
    // Affichage de la s�paration entre recto et verso
    printf(" \nV : ");
    // Affichage c�t� verso (de 8 � 0)
    for (int i = Last; i >= 0; i--) {
           printf("%c", r->lettres[i]);
      
    }
    printf("\n");
}


void ajtMotRail1(Rail* r, const char* m, int sens) {
    int longueur = strlen(m);
    if (sens == GAUCHE) {
        for (int i = longueur - 1; i >= 0; i--) {
            ajtRail(r, m[i], GAUCHE); // Ins�rer de gauche � droite
        }
    }
    else if (sens == DROITE) {
        for (int i = 0; i<longueur; i++) {
            ajtRail(r, m[i], DROITE); // Ins�rer de droite � gauche
        }
    }
}

void ajtMotRail2(Rail* r, const char* m, int sens) {
    int longueur = strlen(m);
    if (sens == GAUCHE) { 
         for (int i = longueur - 1; i >= 0; i--) {
            ajtRail(r, m[i], GAUCHE); // Ins�rer de gauche � droite
        }
    }
    else if (sens == DROITE) { 
        for (int i = longueur - 1; i >= 0; i--) {
            ajtRail(r, m[i], DROITE); // Ins�rer de droite � gauche
        }
    }
}




int char_cmp(const void* a, const void* b) {
    // Comparateur pour qsort : compare deux caract�res
    return (*(char*)a - *(char*)b);
}

int str_cmp(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

void triRail(Rail* r) {
    // Tri des lettres dans le rail avec qsort
    qsort(r->lettres, MAX_RAIL, sizeof(char), char_cmp);
    affRail(r);
}

void triRail2(Rail* r) {
    // Tri des lettres dans le rail avec qsort
    qsort(r->lettres, MAX_RAIL, sizeof(char), str_cmp);
    affRail(r);
}
    



