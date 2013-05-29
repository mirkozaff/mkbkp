#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funzioni.h"

int main(int argc, char *argv[]){

    /* flag della getopt */
    int f_flag = 0, c_flag = 0, x_flag = 0, t_flag = 0; 
    int c;
    
    while ((c = getopt (argc, argv, "f:cxt")) != -1){
        switch (c) {
           case 'f':
             f_flag = 1;
             break;
           case 'c':
             c_flag = 1;
             break;
           case 'x':
             x_flag = 1;
             break;
           case 't':
             t_flag = 1;
             break;
           default:
             print_usage();
             exit(EXIT_FAILURE);
        }
    }   
    
    if(f_flag == 1){
        printf("f\n");
    }
    if(c_flag == 1){
        
    }
    if(x_flag == 1){
        
        printf("x\n");
    }
    if(t_flag == 1){
        printf("t\n");
    }
    
    //archivia(argv[1], argv[2]);
    estrai(argv[1], argv[2]);
            
    
    return 0;
}