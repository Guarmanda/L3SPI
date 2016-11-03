#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

int main(int nb_arg , char * tab_arg[]){

	int tube1[2]; // Connection entre le premier Jeton et la dernier
	int tube2[2]; // Connection entre chacuns des autres Jetons
	int nbFils;
	pid_t fils = 0;



	if( nb_arg != 3 ){
		printf("Usage : Anneau <nombre de jeton> <jeton>\n");
		exit(-1);
	}

	nbFils = atoi(tab_arg[1])-1;

	if( nbFils < 1 ){ //On vérifie la validité du nombre de jeton
		printf("Usage : nombre de jeton DOIT etre supérieur a 1 \n");
		exit(-1);
	}

	printf("\n -- Debut du programme --");
	printf("\n -- Processus %d --\n", getpid());

	pipe(tube1);
	close(0);
	dup(tube1[0]);
	close(tube1[0]);

	pipe(tube2);
	close(1);
	dup(tube2[1]);
	close(tube2[1]);
	

	fils = fork();
	nbFils--;


	while(!fils && nbFils){ 
		//On créé N fils, et duplique tube2 pour créer une connection entre eux
		
		close(0);
		dup(tube2[0]);
		close(tube2[0]);
		close(tube2[1]);

		pipe(tube2);

		close(1);
		dup(tube2[1]);
		close(tube2[1]);
		
		fils = fork();
		nbFils--; //Passage au Jeton suivant
	}

	if(!fils){ //On créé une connection entre le dernier fils et le père avec tube1
		close(0);
		dup(tube2[0]);

		close(tube2[0]);
		close(tube2[1]);
		
		close(1);
		dup(tube1[1]);
		close(tube1[1]);
		nbFils--;
	}

	close(tube1[0]);
	close(tube1[1]);
	

	execlp(tab_arg[2], tab_arg[2], NULL);

	return -1;
}