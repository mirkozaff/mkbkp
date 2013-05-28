#include <stdlib.h>
#include <stdio.h>
#include "funzioni.h"

void copyFile(char *path_from, char *path_to){
    
    FILE *file_from, *file_to;
    char ch;

    /* open source file */
    if((file_from = fopen(path_from, "rb")) == NULL) {
      printf("Cannot open source file.\n");
      exit(1);
    }

    /* open destination file */
    if((file_to = fopen(path_to, "wb")) == NULL) {
      printf("Cannot open destination file.\n");
      exit(1);
    }

    /* copy the file */
    while(!feof(file_from)) {
      ch = fgetc(file_from);
      if(ferror(file_from)) {
        printf("Error reading source file.\n");
        exit(1);
      }
      if(!feof(file_from)) fputc(ch, file_from);
      if(ferror(file_from)) {
        printf("Error writing destination file.\n");
        exit(1);
      }
    }

    if(fclose(file_from)==EOF) {
      printf("Error closing source file.\n");
      exit(1);
    }

    if(fclose(file_from)==EOF) {
      printf("Error closing destination file.\n");
      exit(1);
    }
}

void print_usage() {
    printf("Utilizzo: -f -c -x -t <archivio>\n");
}