#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "funzioni.h"

char *inizioFile = "bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit*****InIzIoFiLe*****bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit\n";
char *fineFile = "bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit*****FiNeFiLe*****bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit\n";

void archivia(char *path_from, char *path_to){
    
    FILE *file_from, *file_to;
    char ch;

    /* open source file */
    if((file_from = fopen(path_from, "rb")) == NULL) {
        printf("Cannot open source file.\n");
        exit(1);
    }

    /* open destination file */
    if((file_to = fopen(path_to, "a")) == NULL) {
        printf("Cannot open destination file.\n");
        exit(1);
    }
    
    /* Scrivo la stringa di riconoscimento di inizio file*/
    fputs(inizioFile, file_to);

    /* copy the file */
    while(!feof(file_from)) {
        ch = fgetc(file_from);
        if(ferror(file_from)) {
            printf("Error reading source file.\n");
            exit(1);
        }
        if(!feof(file_from)){
            fputc(ch, file_to);
        }
        if(ferror(file_to)) {
            printf("Error writing destination file.\n");
            exit(1);
        }
    }
    
    /* Scrivo la stringa di riconoscimento di fine file*/
    fputs(fineFile, file_to);

    if(fclose(file_from)==EOF) {
        printf("Error closing source file.\n");
        exit(1);
    }

    if(fclose(file_to)==EOF) {
        printf("Error closing destination file.\n");
        exit(1);
    }
    
}

void estrai(char *path_from, char *path_to){
    
    FILE *file_from, *file_to;
    char ch;
    char temp[110];
    int count = 0, count2 = 0;
    
    
    

    /* open source file */
    if((file_from = fopen(path_from, "rb")) == NULL) {
        printf("Non posso aprire il file sorgente.\n");
        exit(1);
    }

    /* open destination file */
    if((file_to = fopen(path_to, "wb")) == NULL) {
        printf("Non posso aprire il file destinazione.\n");
        exit(1);
    }
        
    /* copy the file */
    while(!feof(file_from)) {
        ch = fgetc(file_from);
        if(ferror(file_from)) {
            printf("Errore lettura file sorgente.\n");
            exit(1);
        }
        while(ch == inizioFile[count] && count < strlen(inizioFile)-1){
            count++;
            ch = fgetc(file_from);            
        }
        
        if(ch == inizioFile[strlen(inizioFile)-1]){
            
            ch = fgetc(file_from);
            while(strcmp(temp, fineFile) != 0){
                
                if(ch == fineFile[count2]){
                    temp[count2] = ch;
                    count2++;
                    ch = fgetc(file_from);
                }
                else {
                    if(count2 > 0){
                        int i = 0;
                        for(i; i < count2; i++){
                            fputc(temp[i], file_to);
                        } 
                        count2 = 0;
                    }
                    fputc(ch, file_to);
                    if(ferror(file_to)) {
                        printf("Errore scrittura file destinazione.\n");
                        exit(1);
                    }
                    ch = fgetc(file_from);
                }
            }
        }
        else {
            printf("Errore nell'archivio.\n");
            exit(1);
        }
    }
 
    if(fclose(file_from) == EOF) {
        printf("Errore chiusura file sorgente.\n");
        exit(1);
    }

    if(fclose(file_to) == EOF) {
        printf("Errore chiusura file destinazione.\n");
        exit(1);
    }
}


void print_usage() {
    printf("Utilizzo: -f -c -x -t <archivio>\n");
}