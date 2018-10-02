/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 25 septembre 2018, 10:53
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
int main(int argc, char** argv) { 

    int pid1, pid2;
    int nbOctets;
    int descTube[2];
    int descTube2[2];
    const char chaine[] = "Bonjour papa";
    const char chaine2[] = "Bonjour fils";
    char buffer[BUFSIZ];    
    pid1 = getpid();
    memset(buffer, '\0', BUFSIZ);

    if (pipe(descTube) == 0) {
        if (pipe(descTube2) == 0) {

            pid2 = fork(); //duplication du processus

            if (pid2 == 0) //process fils p2
            {
                sleep(2);
                nbOctets = write(descTube2[1], chaine2, strlen(chaine));
                printf("%d octet ecrits\n", nbOctets);
                
                printf("Je suis le fils\n");
                nbOctets = read(descTube[0], buffer, BUFSIZ);
                printf("Octet lus: %d: %s\n", nbOctets, buffer);
            } else //je suis dans le process pere p1
            {
                printf("Je suis le pere\n");
                nbOctets = read(descTube2[0], buffer, BUFSIZ);
                printf("Octet lus: %d: %s\n", nbOctets, buffer);
                
                sleep(2);
                nbOctets = write(descTube[1], chaine, strlen(chaine));
                printf("%d octet ecrits\n", nbOctets);

            }
        }
    }

    exit(EXIT_SUCCESS);

}

