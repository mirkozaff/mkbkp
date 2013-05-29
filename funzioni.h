#ifndef FUNZIONI_H
#define	FUNZIONI_H

/**
 * Definizione di boolean.
 **/
typedef enum {FALSE = 0, TRUE = 1} boolean;


void copyFile(char *path_from, char *path_to);

void archivia(char *path_from, char *path_to);

void estrai(char *path_from, char *path_to);

#endif	/* FUNZIONI_H */

