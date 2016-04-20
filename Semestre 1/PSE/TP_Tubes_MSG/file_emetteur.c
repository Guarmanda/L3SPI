#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include "file_messages.h"



/**
 * Verrouille le fichier dans son ensemble
 * Renvoie CORRECT si le fichier à pu être verrouillé, ERREUR sinon
 */
int verrouille_buffer(const int fd, int pid){

	/* Création du verrou interne */
	struct flock verrou;
	verrou.l_whence = 0;
    verrou.l_start  = 0;
	verrou.l_len    = 0;
	verrou.l_pid    = pid;
	verrou.l_type   = F_WRLCK;
    

    if( fcntl( fd, F_SETLKW, &verrou)==-1){
        return(-1);
	}

    return(0);
}

/**
 * Leve le verrou du fichier
 * Renvoie CORRECT, ERREUR si echec
 */
int deverrouille_buffer(const int fd, int pid){


    /* Création du verrou interne */
    struct flock verrou;
    verrou.l_whence = 0;
    verrou.l_start  = 0;
    verrou.l_len    = 0;
    verrou.l_pid    = pid;
    verrou.l_type   = F_UNLCK;
    
    if( fcntl( fd, F_SETLK, &verrou)==-1){
        return(-1);
	}

    return(0);
}

int 
main( int nb_arg , char * tab_arg[] )
{     
    char nomprog[128] ;
    
	char message[MESSAGES_TAILLE];
	char buffer[6]="buffer";
	int fd_buffer;
	int no_err = 0;
	int pid;
	
	
	int i;
	
    /*-----*/

    strcpy( nomprog , tab_arg[0] );

    if( nb_arg != 1 )
    {
		fprintf( stdout , "%s - Emetteur dans la communication par fichier\n\n" , nomprog ) ;
		fprintf( stdout , "Usage : %s \n" , nomprog ) ;
		exit(1) ; 
    }
	
	pid = getpid();
	
	if((fd_buffer=open(buffer,O_WRONLY,0666))==-1){
		fprintf(stderr, "%s : Probleme durant l'ouverture du fichier %s.\n",
		nomprog, buffer);
		exit(-1);
	}
    
    
    for(i=0 ; i<MESSAGES_NB ; i++){
		
		if( (no_err=verrouille_buffer( fd_buffer, pid))){
			printf("Erreur dans le verrouillage du fichier.\n");
			return no_err;
		}
		
		file_remplir(message, 'a');
		printf("#\tDébut de l'écriture\t#\n");
		
		write(fd_buffer, message, MESSAGES_TAILLE);
		
		if( (no_err=deverrouille_buffer( fd_buffer, pid))){
			printf("Erreur dans le verrouillage du fichier.\n");
			return no_err;
		}
	}
	
	

    
    exit(0);
}
