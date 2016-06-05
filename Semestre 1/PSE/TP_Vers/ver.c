#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include "jeu.h"
#include "commun.h"
#include "terrain.h"
#include "vers.h"


int
main( int nb_arg , char * tab_arg[] )
{
     char nomprog[128] ;
     char fich_terrain[128] ;
     char fich_vers[128] ;
     case_t marque ;
     pid_t pid_aire ;
    


     ver_t ver ;

     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 5 )
     {
	  fprintf( stderr , "Usage : %s <marque> <signal>(inutilise) <fichier terrain> <fichier vers>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

     /* Nom du programme */
     strcpy( nomprog , tab_arg[0] );

     /* Marque du ver */
     if( strlen(tab_arg[1]) !=1 ) 
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   nomprog , tab_arg[1] );
	  exit(-1) ;
     }
     marque = tab_arg[1][0] ;
 
     /* References des fichiers terrain et vers */
     strcpy( fich_terrain , tab_arg[3] );
     strcpy( fich_vers , tab_arg[4] );
     

	
	 vers_fichier_aire_lire(fich_vers,&pid_aire );
	
	
     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());
	
	ver.sig = SIGUSR1;
	ver.pid = getpid();
	ver.marque = marque;
	while(1){
		printf("\n\n--- Envoie d'un signal par le ver (%d) [%d] ---\n\n" ,
		ver.pid , ver.sig );
		kill(pid_aire,SIGUSR1);
		sleep(random()%3);
	}
	
     printf( "\n\n--- Arret ver %c (%d) [%d] ---\n\n" ,
	     ver.marque , ver.pid , ver.sig );
  
     exit(0);
}
