/**
 *  Anno Accademico: 2012-2013
 *  Corso di Studio: Informatica
 *  Titolo del progetto: Modifica utility di base di GNU/Linux
 *  Autori: Zaffaroni Mirko n° 151818
 *	Bonetta Giovanni n° 152122
 **/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdarg.h>
#include <unistd.h>
#include <syslog.h>
#include "funzioni.h"

char *inizioFile = "bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit*****InIzIoFiLe*****bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit\n";
char *fineFile = "bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit*****FiNeFiLe*****bv4e#vbw3eui°#vnwbùntoib3vset5oi@òjb5voit\n";

void archiviaFile(char *path_from, char *archivio){
    
    FILE *file_from, *file_to;
    char ch;

    /* open source file */
    if((file_from = fopen(path_from, "rb")) == NULL) {
        syslog(LOG_ERR, "Non posso aprire il file sorgente.\n");
        printf("Non posso aprire il file sorgente.\n");
        exit(1);
    }

    /* open destination file */
    if((file_to = fopen(archivio, "ab")) == NULL) {
        syslog(LOG_ERR, "Non posso aprire il file di destinazione.\n");
        printf("Non posso aprire il file di destinazione.\n");
        exit(1);
    }
    
    syslog(LOG_INFO, "Creazione archivio iniziata");
            
    /* Scrivo le stringhe di riconoscimento di inizio file* ed il nome del file */
    fputs(inizioFile, file_to);
    fputs(path_from, file_to);
    fputs("\n", file_to);
    fputs(inizioFile, file_to);
   

    /* copia del file */
    while(!feof(file_from)) {
        ch = fgetc(file_from);
        if(ferror(file_from)) {
            syslog(LOG_ERR, "Errore lettura file sorgente.\n");
            printf("Errore lettura file sorgente.\n");
            exit(1);
        }
        if(!feof(file_from)){
            fputc(ch, file_to);
        }
        if(ferror(file_to)) {
            syslog(LOG_ERR, "Errore lettura file destinazione.\n");
            printf("Errore scrittura file destinazione.\n");
            exit(1);
        }
    }
    
    /* Scrivo la stringa di riconoscimento di fine file*/
    fputs(fineFile, file_to);

    if(fclose(file_from)==EOF) {
        syslog(LOG_ERR, "Errore chiusura file sorgente.\n");
        printf("Errore chiusura file sorgente.\n");
        exit(1);
    }

    if(fclose(file_to)==EOF) {
        syslog(LOG_ERR, "Errore chiusura file destinazione.\n");
        printf("Errore chiusura file destinazione.\n");
        exit(1);
    }
    
}

void listaFileArchivio(char *archivio){
    
    FILE *file_from, *file_to;
    char ch;
    /* Stringa temporanea di appoggio per i controlli */
    char temp[110];
    /* nome del file che contenuto nell'archivio */
    char filename[40];
    /* Contatori di controllo per le stringe */
    int count = 0, count2 = 0, count3 = 0;    

    /* Apertura file sorgente */
    if((file_from = fopen(archivio, "rb")) == NULL) {
        printf("Non posso aprire il file sorgente.\n");
        syslog(LOG_ERR, "Non posso aprire il file sorgente.\n");
        exit(1);
    }   
    
    ch = fgetc(file_from); 
    syslog(LOG_INFO, "Creazione lista file archivio iniziata");
    printf("File archivio: \n");
    
    /* lettura dell'archivio */
    while(!feof(file_from)) {
        
        if(ferror(file_from)) {
            printf("Errore lettura file sorgente.\n");
            syslog(LOG_ERR, "Errore lettura file sorgente.\n");
            exit(1);
        }
        /* Scorro finchè non verifico la stringa di controllo */
        while(ch == inizioFile[count] && count < strlen(inizioFile)-1){
            count++;
            ch = fgetc(file_from);            
        }
        
        /* risetto il contatore a 0*/
        count = 0;
        
        if(ch == inizioFile[strlen(inizioFile)-1]){
            
            ch = fgetc(file_from);
            
            while(ch != '\n'){                
                filename[count3] = ch;
                count3++;
                ch = fgetc(file_from);
            }

            filename[count3] = '\0';
            printf("%s\n", filename);
            ch = fgetc(file_from);
            
            /* Scorro finchè non verifico la stringa di controllo */
            while(ch == inizioFile[count] && count < strlen(inizioFile)-1){
                count++;
                ch = fgetc(file_from);            
            }
            
            if(ch == inizioFile[strlen(inizioFile)-1]){
                
                ch = fgetc(file_from);
                
                /* leggo il file nell'archivio fino a quando non trovo la stringa di controllo per la fine */
                while(strcmp(temp, fineFile) != 0){
                    
                    if(ch == fineFile[count2]){
                        temp[count2] = ch;
                        count2++;
                        ch = fgetc(file_from);
                    }
                    else {
                        if(count2 > 0){
                            /* resetto il contatore a 0*/
                            count2 = 0;
                        }
                        ch = fgetc(file_from);
                    }
                }
            }
                
                /* resetto i miei valori di controllo*/
                bzero(temp, count2);
                bzero(filename, count3);
                count3 = 0;
                count2 = 0;
                count = 0;
        }
        else {
            printf("Errore nell'archivio.\n");
            syslog(LOG_ERR, "Errore nell'archivio.\n");
            exit(1);
        }
  }
 
    if(fclose(file_from) == EOF) {
        printf("Errore chiusura file sorgente.\n");
        syslog(LOG_ERR, "Errore chiusura file sorgente.\n");
        exit(1);
    }
}


void estrai(char * archivia){
    FILE *file_from, *file_to;
    char ch;
    /* Stringa temporanea di appoggio per i controlli */
    char temp[110];
    /* nome del file che estraggo */
    char filename[40];
    /* Contatori di controllo per le stringe */
    int count = 0, count2 = 0, count3 = 0;    

    /* Apertura file sorgente */
    if((file_from = fopen(archivia, "rb")) == NULL) {
        syslog(LOG_ERR, "Non posso aprire il file sorgente.\n");
        printf("Non posso aprire il file sorgente.\n");
        exit(1);
    }   
    
    ch = fgetc(file_from); 
    syslog(LOG_INFO, "Estrazione archivio iniziata");
    
    /* copia del file */
    while(!feof(file_from)) {
        
        if(ferror(file_from)) {
            syslog(LOG_ERR, "Errore lettura file sorgente.\n");
            printf("Errore lettura file sorgente.\n");
            exit(1);
        }
        
        /* Scorro finchè non verifico la stringa di controllo */
        while(ch == inizioFile[count] && count < strlen(inizioFile)-1){
            count++;
            ch = fgetc(file_from);            
        }
        
        /* risetto il contatore a 0*/
        count = 0;
        
        if(ch == inizioFile[strlen(inizioFile)-1]){
            
            ch = fgetc(file_from);
            
            while(ch != '\n'){                
                filename[count3] = ch;
                count3++;
                ch = fgetc(file_from);
            }
            filename[count3] = '\0';
            
            /* apro il file di destinazione */
            if((file_to = fopen(filename, "wb")) == NULL) {
                syslog(LOG_ERR, "Non posso aprire il file di destinazione.\n");
                printf("Non posso aprire il file di destinazione.\n");
                exit(1);
            }
  
            ch = fgetc(file_from);
            /* Scorro finchè non verifico la stringa di controllo */
            while(ch == inizioFile[count] && count < strlen(inizioFile)-1){
                count++;
                ch = fgetc(file_from);            
            }
            
            if(ch == inizioFile[strlen(inizioFile)-1]){
                
                ch = fgetc(file_from);
                /* inserisco i file fino a quando non trovo la stringa di controllo per la fine */
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
                            /* resetto il contatore a 0*/
                            count2 = 0;
                        }
                        
                        fputc(ch, file_to);
                        if(ferror(file_to)) {
                            syslog(LOG_ERR, "Errore scrittura file destinazione.\n");
                            printf("Errore scrittura file destinazione.\n");
                            exit(1);
                        }
                        ch = fgetc(file_from);
                    }
                }
                
                /* resetto i miei valori di controllo*/
                bzero(temp, count2);
                bzero(filename, count3);
                count3 = 0;
                count2 = 0;
                count = 0;
            }
        }
        else {
            syslog(LOG_ERR, "Errore nell'archivio.\n");
            printf("Errore nell'archivio.\n");
            exit(1);
        }
        if(fclose(file_to) == EOF) {
            syslog(LOG_ERR, "Errore chiusura file destinazione.\n");
            printf("Errore chiusura file destinazione.\n");
            exit(1);
        }
  }
 
    if(fclose(file_from) == EOF) {
        syslog(LOG_ERR, "Errore chiusura file sorgente.\n");
        printf("Errore chiusura file sorgente.\n");
        exit(1);
    }
}

boolean is_file(const char* path){
    struct stat buf;
    stat(path, &buf);
    if(S_ISREG(buf.st_mode))
        return TRUE;
    else
        return FALSE;
}

boolean is_dir(const char* path){
    struct stat buf;
    stat(path, &buf);
    if(S_ISDIR(buf.st_mode))
        return TRUE;
    else
        return FALSE;
}

void print_usage() {
    printf("Utilizzo: -c -t  -f <archivio> (char* path, ...)\n");
    printf("Utilizzo: -x -t  -f <archivio>\n");
}

void archiviaDir(char *dir, char *archivio){
    
    DIR * d;
	struct dirent *entry;
    
	if((d = opendir(dir)) == NULL) {
        syslog(LOG_ERR, "Non riesco ad aprire %s per la lettura: \n", dir);
        fprintf(stderr,"Non riesco ad aprire %s per la lettura: \n", dir);
        exit(-1); 
    }
    
    chdir(dir);
    
    while ((entry = readdir(d)) != NULL) {
        
        if(strcmp(".", entry -> d_name) == 0 || strcmp("..", entry -> d_name) == 0){
            continue;
        }
        if(is_file(entry -> d_name)){
            archiviaFile(entry -> d_name, archivio);
        }
        if(is_dir(entry -> d_name)){
            archiviaDir(entry -> d_name, archivio);
        }
    }
    
    closedir(d);
}

char *superStringsCat(char *String1, ...){
    
	va_list List;	
	va_start (List, String1);
	
	unsigned int Size;
	
	Size = strlen (String1) + 1;
	
	char *s;
	s = String1;
	
	do
	{
		Size += strlen (s) + 1;
	}while ((s = va_arg (List, char*)) != NULL);
	
	char *Merge;
	Merge = (char*)malloc (sizeof (char) * Size);
	char *sMerge = Merge;

	va_end (List);
	va_start (List, String1);

	s = String1;
	
	do
	{
		strcpy (Merge, s);
		Merge += strlen (s);
	}while ((s = va_arg (List, char*)) != NULL);
	
	va_end (List);
	
	return sMerge;
}