/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 18 septembre 2018, 08:58
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    int socketClient;
    struct sockaddr_in infoServeur;
    float reelAEnvoyer=21.2;
    float reelRecu;
    int tailleStructure;
    int retour;
    
    socketClient=socket(PF_INET , SOCK_STREAM, IPPROTO_TCP);
    if(socketClient==-1)
    {
        printf("pb socket : %s \n", strerror(errno));
        exit(errno);
    }
    
    infoServeur.sin_family=AF_INET;
    infoServeur.sin_port=htons(3333);
    infoServeur.sin_addr.s_addr=inet_addr("172.18.58.83");
    
    retour=sendto(socketClient, &reelAEnvoyer, sizeof(reelAEnvoyer), 0, (struct sockaddr *)&infoServeur, sizeof(infoServeur));       
    
    if(retour==-1)
    {
        printf("pb sendto : %s \n",strerror(errno));
        exit(errno);
    }

    tailleStructure=sizeof(infoServeur);
    retour=recvfrom(socketClient, &reelRecu, sizeof(reelRecu), 0, (struct sockaddr *)&infoServeur, &tailleStructure);
    
    if(retour==-1)
    {
        printf("pb recvfrom: %s \n",strerror(errno));
    }  
    //afficher l'entier du serveur
    printf("message reçu : %f \n", reelRecu);

    return (EXIT_SUCCESS);
}

