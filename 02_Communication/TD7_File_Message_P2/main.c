/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 2 octobre 2018, 09:46
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <error.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "zone.h"
#define CLE 5678

/*
 * 
 */
float randomC() {
    return ((char) ('A' + ((char) 24.0 * (rand() / (RAND_MAX + 0.1)))));
}

int main(int argc, char *argv[]) {

    struct donnees maFile;
    int idFile;
    unsigned int val = 0;   

    // Obtention de la clé
    key_t key;
    if ((key = ftok("/tmp/bidon", 5678)) == -1) {
        perror("ftok");
        exit(2);
    }
    /* obtention de la file pour la clé key */
    idFile = msgget(key, 0666 | IPC_CREAT);
    if (idFile == -1) {
        printf("pb creation file : %s\n", strerror(errno));
        exit(1);
    }

    while (1) {

        maFile.texte[0] = randomC(); /* tirage au sort d'un caractère */
        maFile.type = 3; /* affectation du type içi 3 */
        printf("type = %ld message = %s\n",maFile.type, maFile.texte);  /* affichage du message */
        msgsnd(idFile, (void*) &maFile, sizeof (char), IPC_NOWAIT); /* envoi du message dans la file */
        sleep(1);

    }

    return EXIT_SUCCESS;
}
