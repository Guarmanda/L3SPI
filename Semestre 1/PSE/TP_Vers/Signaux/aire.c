#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>

/*
 * Variables utilisées par le handler et le main
 */
ver_t vers[26];
int nb_vers;
char fich_vers[128] ;
char fich_terrain[128] ;
char marque = 'A';
int nb_lig, nb_col;

coord_t * liste_voisins;
int nb_voisins, ind_libre;

/*
 * HANDLERS
 */
void handler(int sig, siginfo_t *inf){
	
	int i,ind_libre;
	ver_t ver ;
	booleen_t verEnVie = FAUX;
	coord_t * liste_voisins = NULL ;
	int nb_voisins = 8 ;
	
	/* Ouverture du fichier terrain */
	int fd_terrain = open(fich_terrain,O_RDWR,0644);
	
	/* Récupération des dimensions  du terrain */
	terrain_dim_lire(fd_terrain, &nb_lig, &nb_col);
	
	for(i=0; (i<nb_vers) && (!verEnVie); i++) //tour a tour dans l'ordre croissant des vers
		if (inf->si_pid == vers[i].pid) //Discrimination des vers sur leur pid
			verEnVie = VRAI;
	i--;
	
	if(verEnVie){	
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
 * MAIN
 */
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_terrain[128];
     char fich_vers[128];
     char Nom_Prog[256];

     if( nb_arg != 4 ){
		fprintf( stderr , "Usage : %s <fichier terrain> <fichier des vers> <nb vers>\n", 
			tab_arg[0] );
		exit(-1);
     }
	 /* Récupération des paramètres */
     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     strcpy( fich_vers , tab_arg[2] );


     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

	 vers_fichier_aire_ecrire( fich_vers,getpid());


     /* Redirection des signaux */
     struct sigaction s_action, s_action_pre;
     s_action.sa_flags   =SA_SIGINFO;
     s_action.sa_handler =handler;
     sigemptyset(&s_action.sa_mask);
     sigaction(SIGUSR1, &s_action, NULL);
     
	 while(1)
		pause();
	 
	 sigaction(SIGUSR1, &s_action_pre, NULL);
 
     printf("\n\n\t----- Fin du jeu -----\n\n");

     exit(0);
}

