#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "commun.h"
#include "terrain.h"
#include "vers.h"
#include "jeu.h"

#define MAX_VOISINS 8
#define DEFAULT_PERMISSIONS 0755


ver_t vers[26];
int nb_vers = 0;
char fich_vers[128] ;
char fich_terrain[128] ;
char marque = 'A';

void handler(int sig, siginfo_t *inf){
	
	int nb_lig = 10;
	int nb_col = 10;
	int i,ind_libre;
	ver_t ver ;
	booleen_t verExiste = FAUX;
	coord_t * liste_voisins = NULL ;
	int nb_voisins = MAX_VOISINS ;
	
	int fd_terrain = open(fich_terrain,O_RDWR,DEFAULT_PERMISSIONS);
	
	
	for(i=0; (i<nb_vers) && (!verExiste); i++) //tour a tour dans l'ordre croissant des vers
		if (inf->si_pid == vers[i].pid) //Discrimination des vers sur leur pid
			verExiste = VRAI;
	i--;
	
	if(verExiste){
		
		if(vers[i].actif){
			
			terrain_voisins_rechercher( fd_terrain,vers[i].tete,&liste_voisins,&nb_voisins ) ;
			terrain_case_libre_rechercher(fd_terrain,liste_voisins,nb_voisins,&ind_libre);
			
			if(ind_libre !=-1){
				vers[i].tete = liste_voisins[ind_libre];
				terrain_marque_ecrire(fd_terrain,liste_voisins[ind_libre],vers[i].marque);
			}else
				vers[i].actif=FAUX;	
			system("clear");
			terrain_afficher(fd_terrain);	
		}else{
			printf("\nVer %c mort\n",vers[i].marque);
			kill(vers[i].pid,SIGKILL);
		}
	}else{ //nouveau ver
		
		ver.pid = inf->si_pid;
		ver.actif = VRAI;
		ver.marque = marque;
		if(!jeu_ver_initialiser(fd_terrain, nb_lig,nb_col,&ver)){ 
			vers[nb_vers]=ver;
			terrain_marque_ecrire(fd_terrain,ver.tete,ver.marque);
			marque++;
			nb_vers++;
		}else{
			printf("\nVer %c mort\n",vers[i].marque);
			kill(ver.pid,SIGKILL);
		}
	}
}


/*
	* FONCTIONS LOCALES
	*/

int
main( int nb_arg , char * tab_arg[] ){
			
	char Nom_Prog[256];
 

	if( nb_arg != 4 ){
		fprintf( stderr , "Usage : %s <fichier terrain> <fichier des vers> <nb vers>\n", 
				tab_arg[0] );
		exit(-1);
	}

	strcpy( Nom_Prog , tab_arg[0] );
	strcpy( fich_terrain , tab_arg[1] );
	strcpy( fich_vers , tab_arg[2] );

	
	vers_fichier_aire_ecrire( fich_vers,getpid());
	
	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());


	/*Redirection des handlers*/
	struct sigaction action,old_action;
	action.sa_flags = SA_SIGINFO;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	sigaction(SIGUSR1,&action,&old_action);
	
	while(1)
		pause();
	
	sigaction(SIGUSR1,&old_action,NULL);
	
					printf("\n\n\t----- Fin du jeu -----\n\n");

					exit(0);
}

