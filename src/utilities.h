#ifndef UTILITIES_H
#define UTILITIES_H

/***********
 * FONCTIONS UTILITAIRES
 **********/

/* Effectue la soustraction entre deux timespecs */
/* Retourne un timespec */
struct timespec soustraction(struct timespec *debut, struct timespec *fin);

/* Effectue l'addition entre deux timespecs */
/* Retourne un timespec */
struct timespec addition(struct timespec *t1, struct timespec *t2);

/* Effectue l'addition entre un timespec et un entier */
/* Retourne un timespec */
struct timespec additionEntier(struct timespec *t, int nsec);

/* Effectue la multiplication entre un timespec et un entier */
/* Retourne un timespec */
struct timespec multiplicationEntier(struct timespec *t, int entier);

/* Compare deux timespecs */
/* Retourne 1 si "grand" est supérieur à "petit", 0 sinon */
int estPlusGrand(struct timespec *grand, struct timespec *petit);

/* Remplit l'échelle de mesure avec les informations de "tab") */
/* Ne retourne rien, modifie directement "echelle" */
void remplirEchelle(int echelle[], struct timespec *tab, int tailleTab);

/* Permet l'affichage formaté d'un timespec */
/* Ne retourne rien */
void printTimespec(struct timespec *t);

/* Permet l'affichage des résultats sous forme de tableau en stdout ou dans un fichier */
/* "tab" est le tableau des retards, "fichier" est un pointeur sur le fichier d'écriture */
/* Ne retourne rien */
void affiche(struct timespec tab[], int tailleTab, FILE* fichier);

#endif
