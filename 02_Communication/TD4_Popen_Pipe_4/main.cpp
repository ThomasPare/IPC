/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: tpare
 *
 * Created on 26 septembre 2018, 08:41
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */
//handler affichage

void affichage(int sig) {

    static int cpt = 0;

    cpt++;
    if (cpt == 2) {
        printf("%d : signal %d recu par le processus %d\n", cpt, sig, getpid());
    }
}

int main(int argc, char** argv) {
    int pid1, pid2, pid3;
    int retour;
    int descTube[2];
    int pidP3Reception;
    int obtenirPid;
    int nbOctets;

    pid1 = getpid(); //p1
    (void) signal(SIGUSR1, affichage); // redirection des signaux SIGUSR1 vers la fonction affichage
    printf("Père   p1 pid = %d\n", pid1);
    if (pipe(descTube) == 0) {
        pid2 = fork();
        if (pid2 == 0) { //enfant p2
            pid3 = fork();
            if (pid3 == 0) { //enfant p3
                printf("p3 attend un signal\n");
                pause();
                obtenirPid = getpid();
                printf("pid p3 : %d\n", getpid());
                nbOctets = write(descTube[1],&obtenirPid, sizeof(obtenirPid));
                printf("%d octet ecrits\n", nbOctets);
                printf("Fin de processus P3\n");
            } else {
                printf("p2 attend un signal\n");
                pause();
                printf("Fin de processus P2\n");
            }
        } else { //p1
            printf("P1\n");
            sleep(1);
            printf("P1 envoie un signal USR1 à P2\n");
            retour = kill(pid2, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");
            }
            sleep(1);
            printf("P1 envoie un signal USR1 à P3\n");
            retour = kill(pid3, SIGUSR1);
            if (retour != 0) {
                printf("Erreur avec kill");
            }
            nbOctets = read(descTube[0], &pidP3Reception, sizeof(pidP3Reception));
            printf("Octet lus: %d: %d\n", nbOctets, pidP3Reception);
            printf("Fin de processus P1\n");
        }
    }
    return (EXIT_SUCCESS);
}