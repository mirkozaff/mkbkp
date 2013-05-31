#ifndef FUNZIONI_H
#define	FUNZIONI_H

/**
 * Definizione di boolean.
 **/
typedef enum {FALSE = 0, TRUE = 1} boolean;

void archiviaFile(char *path_from, char *archivio);

void estrai(char *archivio);

void listaFileArchivio(char * archivio);

boolean is_file(const char* path);

boolean is_dir(const char* path);

char *superStringsCat(char *String1, ...);

#endif	/* FUNZIONI_H */

