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
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int retourSocket;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    float reelRecu;
    float reelAEnvoyer;
    int tailleClient;
    int retour;
    int retourAccept;


    printf("serveur TCP sur port 6666 attend un REEL\n");
    retourSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(retourSocket==-1)
    {
        printf("pb sendto : %s \n",strerror(errno));
        exit(errno);
    }

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(6666); //numero de port du serveur 
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY); // adresse IP du serveur

    /* Infos Client */
    tailleClient = sizeof (infosClient);

    /* Bind */
    retour = bind(retourSocket, (struct sockaddr*) &infosServeur, sizeof (infosServeur));
    
    if(retour==-1)
    {
        printf("pb bind : %s \n",strerror(errno));
        exit(errno);
    }
    
    /* Attente de data client */
    retour = read(retourAccept, &reelRecu, sizeof (reelRecu));
    if(retour==-1)
    {
        printf("pb read : %s \n",strerror(errno));
        exit(errno);
    }

    /* Affichage data client */
    printf("message client %s : %f\n", inet_ntoa(infosClient.sin_addr), reelRecu);

    reelAEnvoyer = -reelRecu;
    retour = write(retourAccept, &reelAEnvoyer, sizeof (reelAEnvoyer));
    close(retourAccept);

    close(retourSocket);

    return EXIT_SUCCESS;
}

