/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 18 septembre 2018, 10:48
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

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;


int main(int argc, char *argv[]) {
    int retourSocket;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    datePerso date;   
    int tailleClient;
    int retour;
    int retourAccept;


    printf("serveur TCP sur port 7777 attend un REEL\n");
    retourSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(retourSocket==-1)
    {
        printf("pb sendto : %s \n",strerror(errno));
        exit(errno);
    }

    /* Infos du serveur */
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777); //numero de port du serveur 
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

    /* Definition de la taille de la file */
    retour = listen(retourSocket, 10);
    if(retour==-1)
    {
        printf("pb listen : %s \n",strerror(errno));
        exit(errno);
    }


    /* Accept de la connexion */
    retourAccept = accept(retourSocket, (struct sockaddr*) &infosClient, &tailleClient);
    if(retourAccept==-1)
    {
        printf("pb accept : %s \n",strerror(errno));
        exit(errno);
    }

    /* Attente de data client */
    retour = read(retourAccept, &date, sizeof (date));
    if(retour==-1)
    {
        printf("pb read : %s \n",strerror(errno));
        exit(errno);
    }

    /* Affichage data client */
    printf("message client %s : %s %i/%i/%i\n", inet_ntoa(infosClient.sin_addr), date.jourDeLaSemaine, date.jour, date.mois, date.annee);

    
    close(retourAccept);

    close(retourSocket);

    return EXIT_SUCCESS;
}

