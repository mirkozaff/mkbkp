/**
 *  Anno Accademico: 2012-2013
 *  Corso di Studio: Informatica
 *  Titolo del progetto: Modifica utility di base di GNU/Linux
 *  Autori: Zaffaroni Mirko n° 151818
 *	Bonetta Giovanni n° 152122
 **/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <syslog.h>
#include "funzioni.h"

int main(int argc, char *argv[]){
    
    openlog(argv[0], LOG_CONS || LOG_PID, LOG_LOCAL0);

    /* flag della getopt */
    int c_flag = 0, x_flag = 0, t_flag = 0; 
    char *f_flag = 0; 
    char abs_path[400];
    int c;
    int i;
    
    /* Prende il path assoluto della cartella di lavoro */
    getcwd(abs_path, 400);
    i = optind;
        
    while ((c = getopt (argc, argv, "f:cxt")) != -1){
        switch (c) {
           case 'f':
             f_flag = optarg;
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
             syslog(LOG_ERR, "Errore di input nel programma");
             exit(EXIT_FAILURE);
        }
    } 
    
    if(f_flag == 0){
        printf("flag -f necessario\n");
        print_usage();
        syslog(LOG_ERR, "Errore di input nel programma");
        exit(EXIT_FAILURE);       
    }    
    
    if(c_flag == 1 && x_flag == 1){
        printf("Non puoi sia creare che estrare l'archivio allo stesso tempo\n");
        print_usage();
        syslog(LOG_ERR, "Errore di input nel programma");
        exit(EXIT_FAILURE);       
    }
    if(t_flag == 1){
        listaFileArchivio(f_flag);
    }
    if(c_flag == 1){
        
        if(argc <= optind){
            print_usage();
            syslog(LOG_ERR, "Errore di input nel programma");
            exit(EXIT_FAILURE);
        }
        
        printf("Archiviazione... \n");
        do{     
            if(is_file(argv[i])){
                archiviaFile(argv[i], f_flag);  
            }
            if(is_dir(argv[i])){
                archiviaDir(argv[i], superStringsCat(abs_path, "/", f_flag, NULL));  
            }
            i++;
        } while(i < argc);
    }
    if(x_flag == 1){
        printf("Estrazione... \n");
        estrai(f_flag);
    }
    
    syslog(LOG_INFO, "Programma eseguito con successo");  
    closelog (); 
    return (EXIT_SUCCESS);
}