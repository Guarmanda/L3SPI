#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>


ver_t ver;


int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128];
     char fich_terrain[128];
     char fich_vers[128];
     case_t marque;
     pid_t pid_aire;
     int noerr;
     int fd_vers;


     if( nb_arg != 5 ){
	  fprintf( stderr , "Usage : %s <marque> <signal> <fichier terrain> <fichier vers>\n", 
		   tab_arg[0] );
	  exit(-1);
     }
     /* Récupération des paramètres */
     strcpy( nomprog , tab_arg[0] );
     marque = tab_arg[1];
     strcpy( fich_terrain , tab_arg[3] );
     strcpy( fich_vers , tab_arg[4] );

	 vers_fichier_aire_lire(fich_vers,&pid_aire );

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

     /* Initialisation des information du ver */
     ver.marque = marque;
     ver.pid = getpid();
     ver.sig = atoi(tab_arg[2]);



	 /* Demande de communication du ver avec l'aire */
     while(1){
         printf("=[ ver %c ]=> Le ver demande à jouer\n", marque );
         if( kill(pid_aire, SIGUSR1) != 0){      
             fprintf(stderr, "Erreur : Impossible de communiquer avec l'aire.\n");
             exit(ERREUR);
		 }
		 sleep(random() % TEMPS_MOYEN);
     }

     printf( "\n\n--- Arret ver %c (%d) [%d] ---\n\n" ,
	     ver.marque , ver.pid , ver.sig );
  
     exit(0);
}
