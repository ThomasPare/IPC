/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include "zone.h"
#define CLE 5678

/*
 * 
 */
int main(int argc, char** argv) {
    
    key_t key;
    
    key = ftok("bidon", CLE);

    return (EXIT_SUCCESS);
}