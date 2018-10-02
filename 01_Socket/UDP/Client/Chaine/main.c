/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 18 septembre 2018, 09:00
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
}datePerso;

/*
 * 
 */
int main(int argc, char** argv) {
    
    int socketClient;
    struct sockaddr_in infoServeur;
    datePerso chaineAEnvoyer;    
    chaineAEnvoyer.jour = 6;
    chaineAEnvoyer.mois = 9;
    chaineAEnvoyer.annee = 1999;
    strcpy(chaineAEnvoyer.jourDeLaSemaine,"lundi");   
    int retour;
    
    socketClient=socket(PF_INET , SOCK_STREAM, IPPROTO_TCP);
    if(socketClient==-1)
    {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }
    
    infoServeur.sin_family=AF_INET;
    infoServeur.sin_port=htons(4444);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.83");
    
    retour=connect(socketClient, (struct sockaddr *)&infoServeur, sizeof(infoServeur));
    if(retour==-1)
    {
        printf("pb connect : %s \n", strerror(errno));
        exit(errno);
    }
    
    retour=sendto(socketClient, &chaineAEnvoyer, sizeof(chaineAEnvoyer), 0, (struct sockaddr *)&infoServeur, sizeof(infoServeur));       
    
    if(retour==-1)
    {
        printf("pb sendto : %s \n",strerror(errno));
        exit(errno);
    }
    

    return (EXIT_SUCCESS);
}

