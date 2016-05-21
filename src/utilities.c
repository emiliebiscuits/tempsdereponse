#include <stdio.h>
#include <time.h>
#include "utilities.h"

/***********
 * FONCTIONS UTILITAIRES
 **********/

struct timespec soustraction(struct timespec *debut, struct timespec *fin)
{
	struct timespec resultat; 
	if (fin->tv_nsec > debut->tv_nsec) 
	{
		if(fin->tv_sec >= debut->tv_sec)
		{		
			resultat.tv_sec = fin->tv_sec - debut->tv_sec;
			resultat.tv_nsec = fin->tv_nsec - debut->tv_nsec;
		}
		else
		{
			resultat.tv_sec = debut->tv_sec - fin->tv_sec - 1;
			resultat.tv_nsec = -(1000000000 + debut->tv_nsec - fin->tv_nsec);	
		}
	} 
	else if(fin->tv_nsec == debut->tv_nsec)
	{
		resultat.tv_nsec = 0;
		if(fin->tv_sec == debut->tv_sec)
		{
			resultat.tv_sec = 0;
		}
		else
		{
			resultat.tv_sec = fin->tv_sec - debut->tv_sec;
		}
	} 
	else 
	{
		if(fin->tv_sec > debut->tv_sec)
		{
			resultat.tv_sec = fin->tv_sec - debut->tv_sec - 1;
			resultat.tv_nsec = 1000000000 + fin->tv_nsec - debut->tv_nsec;
		}
		else if (fin->tv_sec < debut->tv_sec)
		{
			resultat.tv_sec = -(debut->tv_sec - fin->tv_sec);
			resultat.tv_nsec = debut->tv_nsec - fin->tv_nsec;
		}
		else
		{
			resultat.tv_sec =  0;
			resultat.tv_nsec = -(debut->tv_nsec - fin->tv_nsec);
		}
	}
	return resultat;
}

struct timespec addition(struct timespec *t1, struct timespec *t2)
{
	struct timespec resultat;
	resultat.tv_nsec = t1->tv_nsec + t2->tv_nsec;
	if(resultat.tv_nsec >= 1000000000)
	{
		resultat.tv_sec =  t1->tv_sec + t2->tv_sec + resultat.tv_nsec / 1000000000;
		resultat.tv_nsec = resultat.tv_nsec % 1000000000;
	}
	else
	{
		resultat.tv_sec =  t1->tv_sec + t2->tv_sec;
	}
	return resultat;
}

struct timespec additionEntier(struct timespec *t, int nsec)
{
	struct timespec resultat;
	long long int longChiffre = t->tv_nsec + nsec;
	if(longChiffre >= 1000000000)
	{
		resultat.tv_sec = t->tv_sec + longChiffre/ 1000000000;
		resultat.tv_nsec = longChiffre % 1000000000;
	}
	else
	{
		resultat.tv_sec = t->tv_sec;
		resultat.tv_nsec = longChiffre;
	}
	return resultat;
}

struct timespec multiplicationEntier(struct timespec *t, int entier)
{
	struct timespec resultat;
	resultat.tv_sec = 0;
	resultat.tv_nsec = 0;
	int i = 0;
	for(i=0;i<entier;i++)
	{
		resultat = addition(&resultat, t);
	}
	return resultat;
}

int estPlusGrand(struct timespec *grand, struct timespec *petit)
{
	if(grand->tv_sec > petit->tv_sec)
	{	
		return 1;
	}
	else if(grand->tv_sec < petit->tv_sec)
	{
		return 0;
	}
	else
	{
		if(grand->tv_nsec < petit->tv_nsec)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}	
}

void remplirEchelle(int echelle[], struct timespec *tab, int tailleTab)
{
	int i;
	for(i=0; i<tailleTab; i++)
	{
		if(tab[i].tv_sec < -1) {
			echelle[0]++;		
		} else if ((tab[i].tv_sec == 0 && tab[i].tv_nsec <= -100001000) ||  (tab[i].tv_sec == -1 && tab[i].tv_nsec <= 0)) {
			echelle[1]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec <= -10001000 && tab[i].tv_nsec >= -100000000) {
			echelle[2]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec <= -1001000 && tab[i].tv_nsec >= -10000000) {
			echelle[3]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec <= -101000 && tab[i].tv_nsec >= -1000000) {
			echelle[4]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec <= -1000 && tab[i].tv_nsec >= -100000) {
			echelle[5]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec >= -999 && tab[i].tv_nsec <= 999) {
			echelle[6]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec >= 1000&& tab[i].tv_nsec <= 100000) {
			echelle[7]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec >= 101000 && tab[i].tv_nsec <= 1000000) {
			echelle[8]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec >= 1001000 && tab[i].tv_nsec <= 10000000) {
			echelle[9]++;
		} else if (tab[i].tv_sec == 0 && tab[i].tv_nsec >= 10001000 && tab[i].tv_nsec <= 100000000) {
			echelle[10]++;
		} else if ((tab[i].tv_sec == 0 && tab[i].tv_nsec >= 100001000) ||  (tab[i].tv_sec == 1 && tab[i].tv_nsec >= 0)) {
			echelle[11]++;
		} else if(tab[i].tv_sec > 1) {
			echelle[12]++;
		}
	}
}

void printTimespec(struct timespec *t)
{
	if(t->tv_nsec<0)
	{
		printf("-%lld.%.9ld", (long long)t->tv_sec, -t->tv_nsec);
	}
	else
	{
		printf("%lld.%.9ld", (long long)t->tv_sec, t->tv_nsec);
	}
	printf("\n");
}

void affiche(struct timespec tab[], int tailleTab, FILE* fichier)
{
        int echelle[13] = {0};
        int i; 
       
        remplirEchelle(echelle, tab, tailleTab);
        fprintf(fichier, "-------------------------------------------------------------------------------");
        fprintf(fichier, "\n| -6  | -5  | -4  | -3  | -2  | -1  |  0  |  +1 |  +2 |  +3 |  +4 |  +5 |  +6 |");
        fprintf(fichier, "\n------+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+------\n|");
        for(i=0;i<13;i++)
        {
                fprintf(fichier, "%05d|", echelle[i]);
        }
        fprintf(fichier, "\n-------------------------------------------------------------------------------\n");
}
