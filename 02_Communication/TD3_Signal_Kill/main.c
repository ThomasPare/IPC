/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 25 septembre 2018, 08:17
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

// fonction de traitement du signal SIGUSR1

void affichage(int sig){

    static int cpt = 0;

    cpt++;
    if(cpt == 2){
    printf("%d : signal %d recu par le processus %d\n", cpt, sig, getpid());
    }
}

int main(int argc, char *argv[]) {
    int pid1;
	int pid2;
	int pid3;
	int retour;

	pid1 = getpid();
	(void) signal(SIGUSR1, affichage); // redirection des signaux SIGUSR1 vers la fonction affichage
	printf ("Père   p1 pid = %d\n", pid1);
	pid2 = fork();
	if ( pid2 == 0 )
	{       // Enfant P2
		pid3 = fork();
		if (pid3 == 0){
			// Enfant P3
			printf ( "Enfant p3 pid = %d ppid = %d\n", getpid(), getppid());

			printf ("P3 envoie un signal USR1 à P1\n");
			retour = kill(pid1, SIGUSR1);
			if (retour !=0) {
				printf("Erreur avec kill");
			}
                        printf("Le processus P3 attend un signal\n");
			pause(); // attente d'un signal
			printf ("Fin de processus  P3\n");
                }
		else{
			// Enfant P2
			printf ( "Enfant p2 pid = %d ppid = %d\n", getpid(), getppid());
                        printf("Le processus P2 attend un signal SIGUSR1\n");
                        pause();

			printf ("P2 envoie un signal USR1 à P1\n");
			retour = kill(pid1, SIGUSR1); // envoi d'un signal USR1 au père P1
                        if (retour !=0) {
                                printf("Erreur avec kill");
                        }

			printf ("P2 envoie un signal USR1 à P3\n");
                        retour = kill(pid3, SIGUSR1); // envoi d'un signal USR1 a enfant P3
			if (retour !=0) {
                                printf("Erreur avec kill");
                        }
			printf ("Fin de processus P2\n");
                }
	}
	else
	{	// Père P1
                printf("Le processus P1 attend un premier signal SIGUSR1\n");
		pause();
                printf ("P1 envoie un signal USR1 à P2\n");
		retour = kill(pid2, SIGUSR1); // envoi d'un signal USR1 a enfant 2
                printf("Le processus P1 attend un deuxième signal SIGUSR1\n");
		pause();
		printf ("Fin de processus P1\n");
	}
	return EXIT_SUCCESS;
}

