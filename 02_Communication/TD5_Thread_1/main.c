/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 28 septembre 2018, 08:17
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


typedef struct {
	int v1;
	int v2;
	int v3;
}laStruct;

laStruct entier;

void *fonction_thread_1(void *arg)
{
    printf("dans le thread l'argument était : %d\n", *(int *) arg);
    sleep(3);
    entier.v1=*(int *) arg;
    pthread_exit((void *) "merci pour le temps CPU");
}

void *fonction_thread_2(void *arg)
{
    printf("dans le thread l'argument était : %d\n", *(int *) arg);
    sleep(3);
    entier.v2=*(int *) arg;
    pthread_exit((void *) "merci pour le temps CPU");
}

void *fonction_thread_3(void *arg)
{
    printf("dans le thread l'argument était : %d\n", *(int *) arg);
    sleep(3);
    entier.v3=*(int *) arg;
    pthread_exit((void *) "merci pour le temps CPU");
}

int main(int argc, char** argv) {
    
    int res;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    void *threadResult1;
    void *threadResult2;
    void *threadResult3;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    
    res=pthread_create(&thread1, NULL, fonction_thread_1, (void *) &v1);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    printf("attente de la fin du thread 1...\n");

    res = pthread_join(thread1, &threadResult1);
    if (res != 0) {
        perror("Thread join a echoué");
        exit(EXIT_FAILURE);
    }
    
    res=pthread_create(&thread2, NULL, fonction_thread_2, (void *) &v2);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    printf("attente de la fin du thread 2...\n");

    res = pthread_join(thread2, &threadResult2);
    if (res != 0) {
        perror("Thread join a echoué");
        exit(EXIT_FAILURE);
    }
    
    res=pthread_create(&thread3, NULL, fonction_thread_3, (void *) &v3);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    printf("attente de la fin du thread 3...\n");

    res = pthread_join(thread3, &threadResult3);
    if (res != 0) {
        perror("Thread join a echoué");
        exit(EXIT_FAILURE);
    }
    
    printf("OK, valeur de retour du Thread join 1 :%d\n", entier.v1);
    printf("OK, valeur de retour du Thread join 2 :%d\n", entier.v2);
    printf("OK, valeur de retour du Thread join 3 :%d\n", entier.v3);
    
    return (EXIT_SUCCESS);
}

