/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 19 septembre 2018, 08:37
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

/*
 * 
 */
int main(int argc, char** argv) {
    FILE *fic;
    char lettre[100];
    char dest[100];
    int nb;
    char lettrenom;
    int i;

    //Ouverture du fichier
    fic = fopen("/home/USERS/ELEVES/SNIR2017/dlevillain/SNIR2/IPC/01-Socket/TCP/Serveur/Serveur_TCP_PageWEB/index.html", "r");

    for (i = 0; i <= 7; i++) {
        lettrenom = fgetc(fic);
        while (lettrenom != '\n') {
            lettre[nb] = lettrenom;
            nb++;
            lettrenom = fgetc(fic);
        }
        lettre[nb] = '\0';
        printf("%s\n", lettre);
        strcpy(lettre, "");
        nb = 0;
    }
}