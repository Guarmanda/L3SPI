#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>

#define NB_ARGUMENTS 4
#define ERROR -1
#define ERROR_EXEC 127
#define MAX_SIZE_COMMAND 64
#define CORBEILLE "/dev/null"


int CompareIntBis(const int *a, const int *b){
	if (*a<*b)
		return -1;
	if (*a>*b)
		return 1;
	return 0;
}

int CompareInt(const void *a1, const void *b1){
	const int * a2 = a1;
	const int * b2 = b1;
	return CompareIntBis(a2, b2);
}


int main(int argc, char *argv[]){

	if(argc != NB_ARGUMENTS){
		printf("\n\nUsage : %s <K> <commande> <nb_processus>\n\n",argv[0]);
		exit(ERROR);
	}

	// R�cup�ration des arguments
	int K=atoi(argv[1]); // Nombre de fois que la commande est executee par un processus
	char commande[MAX_SIZE_COMMAND];
	strcpy(commande, argv[2]); // Commande execut�e par le(s) processus
	int nb_proc=atoi(argv[3]); // Nombre de processus executant la commande

	// Variables
	struct timeval timevalDebut, timevalFin;
	int cr;
	float tab[nb_proc];
	int cptProcessus, cptExecutions;
	float Mi=0; // Temps d'execution moyen d'une commande
	float Ti=0; // Temps d'execution d'un processus
	int tube[2];
	int output, fd;

	// Initialisation de tab � 0
	for(cptProcessus=0; cptProcessus<nb_proc; cptProcessus++){
		tab[cptProcessus] = 0;
	}

	pipe(tube);

	for(cptProcessus=0; cptProcessus<nb_proc; cptProcessus++)
		switch(fork()){
			case ERROR: // Erreur fork
					perror("\nErreur fork\n");
					exit(ERROR);

			case 0: // Fils
					for (cptExecutions=0; cptExecutions<K; cptExecutions++){
						// On ferme l'extremite de lecture du tube car le fils ne lit pas dedans
						close(tube[0]);

						// Acquisition de la date de debut
						gettimeofday(&timevalDebut, NULL);

						// Execution commande dans un petit-fils
						switch(fork()){
							case ERROR: // Erreur fork
                                    perror("\nErreur fork\n");
                                    exit(ERROR);

							case 0: // Petit-fils

									// Redirection de la sortie des commandes
									if((fd = open(CORBEILLE, O_WRONLY, 0666))==ERROR){
										fprintf(stderr, "\nErreur open\n");
										exit(ERROR);
									}
									close(1);
									dup(fd);
									close(2);
									dup(fd);
									close(fd);

									// Recouvrement du processus petit fils par la commande
									execlp(commande, commande, NULL);
									fprintf(stderr, "\n\nProbleme de recouvrement\n\n");
									exit(ERROR_EXEC);

							default: // Attend la fin de l'execution
									wait(&cr);
						}

						// Acquisition de la date de fin d'execution des commandes
						gettimeofday(&timevalFin, NULL);

						// Test des erreurs
						if(WIFEXITED(cr))
							if(WEXITSTATUS(cr) != 0){
								if(WEXITSTATUS(cr) == ERROR_EXEC){
									fprintf(stderr,"\n\n%s interrompue par un probleme de recouvrement\n\n", commande);
									exit(ERROR);
								}
								fprintf(stderr, "\n\n%s interrompue par exit %d\n\n", commande, WEXITSTATUS(cr));
								exit(ERROR);
							}

						if(WIFSIGNALED(cr)){
							fprintf(stderr, "\n\n%s interrompue par le signal %d\n\n", commande, WTERMSIG(cr));
							exit(ERROR);
						}

						// Calcul du temps ecoule
						Ti+= timevalFin.tv_sec*1000 - timevalDebut.tv_sec*1000 + timevalFin.tv_usec/1000 - timevalDebut.tv_usec/1000;
					}
					Mi= Ti/K; // temps moyen d'execution

					// transmission au pere
					write(tube[1], &Mi, sizeof(float));
					close(tube[1]);
					exit(0);
		}

	// Le pere n'ecrit pas dans le tube
	close(tube[1]);

	// Acquisition du temps moyen total des commandes
	for(cptProcessus=0; cptProcessus<nb_proc; cptProcessus++){
		read(tube[0], &tab[cptProcessus], sizeof(float));
	}
	close(tube[0]);

	// Tri du tableau tab
	qsort(tab, nb_proc, sizeof(float), CompareInt);

	// Affichage du resultat
	output = nb_proc/2;
	if(tab[output] !=0){
		printf("\n\nTemps moyen d'execution de %d fois la commande %s est de %f ms\n\n", K, commande, tab[output]);
		exit(0);
	}

	fprintf(stderr, "\nErreur\n");
	exit(ERROR);
}