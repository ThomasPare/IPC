/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: tpare
 *
 * Created on 19 septembre 2018, 09:03
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pid1, pid2, pid3, pid4, pid5, pid6, pid7;
    pid1 = getpid();
    pid3 = fork();
    if (pid3 == 0) //enfant de P1 nommé P3
    {
        
        pid2 = fork();
        if (pid2 == 0) //enfant de P3 nommé P2
        {
            printf("p2 : pid=%d ppid=%d \n", getpid(), getppid());
            int pid = wait(NULL);            
        } else {
            pid4 = fork();
            if (pid4 == 0) //enfant de P3 nommé P4
            {
                printf("p4 : pid=%d ppid=%d \n", getpid(), getppid());
                int pid = wait(NULL);
            } else {
                pid5 = fork();
                if (pid5 == 0) //enfant de P3 nommé P5
                {
                    printf("p5 : pid=%d ppid=%d \n", getpid(), getppid());
                    int pid = wait(NULL);
                    pid6 = fork();
                    if(pid6 == 0)
                    {
                        printf("p6 : pid=%d ppid=%d \n", getpid(), getppid());
                        int pid = wait(NULL);
                    }else {
                        pid7 = fork();
                        if(pid7 == 0)
                        {
                            printf("p7 : pid=%d ppid=%d \n", getpid(), getppid());
                            int pid = wait(NULL);
                        }
                    }
                }
            }
        }
    }else{
        printf("p1 : pid=%d ppid=%d \n", getpid(), getppid());
        int pid = wait(NULL);
        printf("fin de : %d \n", pid);
    }

    return EXIT_SUCCESS;
}

