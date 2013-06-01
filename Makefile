#
# Makefile mkbkp
# Sistema operativo Linux con compilatore gcc 4.7.3
#
mkbkp: mkbkp.o funzioni.o
	gcc -o mkbkp mkbkp.o funzioni.o
#
mkbkp.o: mkbkp.c funzioni.h
	gcc -c mkbkp.c
#
funzioni.o: funzioni.c
	gcc -c funzioni.c
