Test : Outil.o Alex.o Asynt.o Erreur.o main.c
	gcc Outil.o Alex.o Asynt.o Erreur.o main.c -lm -o Test

Outil.o : Outil.c
	gcc -c Outil.c -o Outil.o
Alex.o : Alex.c
	gcc -c Alex.c -o Alex.o
Asynt.o : Asynt.c
	gcc -c Asynt.c -o Asynt.o
Erreur.o : Erreur.c
	gcc -c Erreur.c -o Erreur.o


all : Test  
	
clean : 
	rm *.o
	rm Test
