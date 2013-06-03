#
#  Anno Accademico: 2012-2013
#  Corso di Studio: Informatica
#  Titolo del progetto: Modifica utility di base di GNU/Linux
#  Autori: Zaffaroni Mirko n° 151818
#	   Bonetta Giovanni n° 152122
#
# Makefile mkbkp
# Sistema operativo Linux con compilatore gcc 4.7.3
#
mkbkp: mkbkp.o funzioni.o
	gcc -o mkbkp mkbkp.o funzioni.o
#
mkbkp.o: mkbkp.c
	gcc -c mkbkp.c
#
funzioni.o: funzioni.c
	gcc -c funzioni.c
