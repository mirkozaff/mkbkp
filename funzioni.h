#ifndef FUNZIONI_H
#define	FUNZIONI_H

/**
 * Definizione di boolean.
 **/
typedef enum {FALSE = 0, TRUE = 1} boolean;


/**
 * Crea un archivio se non esiste, altrimenti aggiunge il file
 * passato come argomento in append all'archivio salvando
 * nome del file e codifica 
 **/
void archiviaFile(char *path_from, char *archivio);


/**
 * Estrae l'archivio passato come argomento
 * nella directory corrente di lavoro
 **/
void estrai(char *archivio);


/**
 * Crea una lista di tutti gli elementi
 * dell'archivio visualizzabile a video
 **/
void listaFileArchivio(char * archivio);


/*
 * Controlla se il path passato corrisponde ad un file
 * TRUE se lo è
 * FALSE altrimenti
 */
boolean is_file(const char* path);


/*
 * Controlla se il path passato corrisponde ad una directory
 * TRUE se lo è
 * FALSE altrimenti
 */
boolean is_dir(const char* path);


/**
 * Concatena tutte le stringe prese in argomento,
 *  finchè non trova la stringa a NULL
 **/
char *superStringsCat(char *String1, ...);

#endif	/* FUNZIONI_H */

