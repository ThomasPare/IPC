/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 18 septembre 2018, 11:00
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
    int socketServeur;
    int socketDeux;
    int tailleStructure;
    int retourListen;
    int retourWrite;
    int retourB;
    struct sockaddr_in adresse;
    struct sockaddr_in infoClient;
    FILE *fic;
    char lettre[100];
    char dest[100];
    int nb;
    char lettrenom;
    int i;

    //Ouverture du fichier
    fic = fopen("/home/USERS/ELEVES/SNIR2017/dlevillain/SNIR2/IPC/01-Socket/TCP/Serveur/Serveur_TCP_PageWEB/index.html", "r");
    
    for(i=0; i<=7; i++)
    {
        lettrenom=fgetc(fic);
        while (lettrenom!='\n')
        {
            lettre[nb]=lettrenom;
            nb++;
            lettrenom=fgetc(fic);
        }
        lettre[nb]='\0';
        strcpy(lettre,"");
        strcpy(dest, lettre);
        printf("%s\n",lettre);
        nb=0;
    }
    //Création de la socket TCP
    socketServeur = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketServeur == -1) {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }

    //Init des informations
    adresse.sin_family = AF_INET;
    adresse.sin_port = htons(8888);
    adresse.sin_addr.s_addr = htonl(INADDR_ANY);

    retourB = bind(socketServeur, (struct sockaddr*) &adresse, sizeof (adresse)); //attachement ip-port

    if (retourB == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(0);
    }


    //définie la taille de la file de connexion
    retourListen = listen(socketServeur, 10);

    if (retourListen == -1) {
        printf("pb listen: %s \n", strerror(errno));
    }


    tailleStructure = sizeof (infoClient);

    while (1) {

        socketDeux = accept(socketServeur, (struct sockaddr *) &infoClient, &tailleStructure);

        if (socketDeux == -1) {
            printf("pb accept: %s \n", strerror(errno));
        }


        //reçoit l'entier du client
       /* retourRead = read(socketDeux, &valeurRecue, sizeof (valeurRecue));


        if (retourRead == -1) {
            printf("pb read: %s \n", strerror(errno));
        }

        //affiche la valeur reçu
        printf("message du client %s Réponse : %d\n", inet_ntoa(infoClient.sin_addr), valeurRecue);

        valeurRetour = -valeurRecue;*/
        printf("%s",dest);
        //Envoi de la valeurRetour au client
        retourWrite = write(socketDeux,dest,strlen(dest));

        if (retourWrite == -1) {
            printf("pb write : %s \n", strerror(errno));
            exit(errno);
        }

        close(socketDeux);

    }

    close(socketServeur);

    return (EXIT_SUCCESS);
}

