#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include "utilities.h"

/***********
 * FONCTIONS ACTIVES / PASSIVES
 **********/

struct timespec timespec_passive_t0;
struct timespec timespec_passive_dt;
struct timespec *tab_passive = NULL;
int numeroIte_passive = 0;

struct timespec ma_fonction_active(struct timespec *t0, struct timespec *dt, int numeroIte)
{
	struct timespec ti;
	struct timespec res; 
	struct timespec res1;
	struct timespec res2; 
	clock_gettime(CLOCK_MONOTONIC, &ti);
	res = multiplicationEntier(dt, numeroIte);
	res1 = addition(t0, &res);
	res2 = soustraction(&res1, &ti);
	return res2;
}

void ma_fonction_passive(int sig, siginfo_t *si, void *uc)
{
	struct timespec ti;
	struct timespec res1;
	struct timespec res2;
	clock_gettime(CLOCK_MONOTONIC, &ti);

	res1 = multiplicationEntier(&timespec_passive_dt,numeroIte_passive+1);
	res2 = addition(&timespec_passive_t0, &res1);
	if(numeroIte_passive < si->si_value.sival_int)
	{
		tab_passive[numeroIte_passive] = soustraction(&res2, &ti);
	}
	numeroIte_passive+=1;
}


/***********
 * FONCTION MAIN
 **********/

int main(int argc, char *argv[])
{	
	// Valeurs par défaut
	int active = 0; // actif ou passif ?
	int taille = 20; // taille echantillon
	int sortie = 0; // sortie
	int dt = 10000; // periode
	int verbose = 0; // mode verbose
	char sortieS[10];
	char attenteS[10];
	FILE *fout;	
	int i = 0;
	
	// Lecture des arguments
	if(argc < 5 || argc > 6)
	{
		printf("Ce programme permet de calculer le décalage d'une fonction dans le temps.\n");
		printf("Utilisation : %s <nombre de tests> <attente> <periode> <sortie> [--verbose] \n", argv[0]);
		printf("<attente> : 0 = passive, 1 = active \n");
		printf("<periode> : temps en microsecondes entre deux tests \n");
		printf("<sortie>  : 0 = stdout, 1 = fichier \n");
		return 0;
	}
	else
	{
		taille = atoi(argv[1]);
		active = atoi(argv[2]);
		dt = atoi(argv[3]);
		sortie = atoi(argv[4]);
	}
	if(argc == 6)
	{	
		if(!strcmp("--v", argv[5]) || !strcmp("--verbose", argv[5])) 
		{
			verbose = 1;

			if(active) {
				strcpy(attenteS, "Active");
			} else {
				strcpy(attenteS, "Passive");
			}
			if(sortie) {
				strcpy(sortieS, "Fichier");
			} else {
				strcpy(sortieS, "Stdout");
			}
		}		
	}
	if(sortie) {
		fout = fopen("out_file.txt", "a");
	} else {
		fout = stdout;	
	}
	struct timespec tab[taille];
	
	// Debut programme
	fprintf(fout, "=============== DEBUT ===============\n");
	if(verbose)
	{
		fprintf(fout, "Lancement du test avec les configurations suivantes : \n");
		fprintf(fout, "Nombre de tests : %d \n", taille);
		fprintf(fout, "Periode         : %d \n", dt);
		fprintf(fout, "Attente         : %s \n", attenteS);
		fprintf(fout, "Sortie          : %s \n", sortieS);
	}

	if(active) 
	{	
		struct timespec debut;
		struct timespec reference;
		struct timespec maintenant;
		struct timespec dtt;
		struct timespec res;

		dtt.tv_sec = (dt*1000)/1000000000;
		dtt.tv_nsec = (dt*1000)%1000000000;
		if(clock_gettime(CLOCK_MONOTONIC, &debut)) { 
			perror("Probleme de clock_gettime !\n");
			return 1;
		}
		
		// Initialisation du temps référence (t0)
		reference.tv_sec = debut.tv_sec;
		reference.tv_nsec = debut.tv_nsec;
		
		// Boucle active
		while(i<taille)
		{
			clock_gettime(CLOCK_MONOTONIC, &maintenant);
			res = soustraction(&debut, &maintenant);
			if(estPlusGrand(&res, &dtt))
			{
				tab[i] = ma_fonction_active(&reference, &dtt, i+1);
				debut.tv_sec = maintenant.tv_sec;
				debut.tv_nsec = maintenant.tv_nsec;
				i++;	
			}
		}
		
		// Affichage
		affiche(tab, taille, fout);
	}
	else 
	{				
		timespec_passive_dt.tv_sec = (dt*1000)/1000000000;
		timespec_passive_dt.tv_nsec = (dt*1000)%1000000000;
		tab_passive = tab;
		
		// Creation du Sigaction
		struct sigaction sa;
		memset(&sa, '\0', sizeof(sa));
		sa.sa_sigaction = ma_fonction_passive;
		sa.sa_flags = SA_SIGINFO;
		if(sigaction(SIGALRM, &sa, NULL)) {
			perror("Probleme de sigaction !\n");
			return 1;
		}
		
		// Creation du timer
		timer_t timerid;
		struct sigevent sevp;
		sevp.sigev_notify = SIGEV_SIGNAL;
		sevp.sigev_signo = SIGALRM;
		sevp.sigev_value.sival_int = taille;
		if(timer_create(CLOCK_MONOTONIC, &sevp, &timerid)) {
			perror("Probleme de timer_create !\n");
			return 1;
		}
		
		// Creation de l'intervalle	
		struct itimerspec its;
		its.it_value.tv_sec = (dt*1000)/1000000000;
		its.it_value.tv_nsec = (dt*1000)%1000000000;
		its.it_interval.tv_sec = its.it_value.tv_sec;
		its.it_interval.tv_nsec = its.it_value.tv_nsec;
		if(timer_settime(timerid, 0, &its, NULL)) {
			perror("Probleme de timer_settime !\n");
			return 1;
		}
		
		//Initialisation du temps référence (t0)
		if(clock_gettime(CLOCK_MONOTONIC, &timespec_passive_t0)) { 
			perror("Probleme de clock_gettime !\n");
			return 1;
		}
		
		// Boucle passive
		while(numeroIte_passive<taille)
		{
			pause();
		}
		
		//Arreter timer
		its.it_value.tv_sec = 0;
		its.it_value.tv_nsec = 0;
		its.it_interval.tv_sec = 0;
		its.it_interval.tv_nsec = 0;
		if(timer_settime(timerid, 0, &its, NULL)) {
			perror("Probleme de timer_settime !\n");
			return 1;
		}
			
		//Affichage
		affiche(tab, taille, fout);
	}
	
	fprintf(fout, "================ FIN ================\n\n");
	fclose(fout);	
	return 0;
}
