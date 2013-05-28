#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main(int argc, char *argv[]){

    /* flag della getopt */
    int f_flag = 0, c_flag = 0, x_flag = 0, t_flag = 0; 
    int c;
    
    printf("c: %d\n", argc);
    while ((c = getopt (argc, argv, "fcxt")) != -1){
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
    printf("c: %d\n", c);
    if(f_flag == 1){
        printf("f\n");
    }
    if(c_flag == 1){
        printf("c\n");
    }
    if(x_flag == 1){
        printf("x\n");
    }
    if(t_flag == 1){
        printf("t\n");
    }
    
         
    
    return 0;
}