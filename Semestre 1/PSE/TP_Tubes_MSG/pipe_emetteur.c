#include <stdio.h>
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* mknod */
#include <sys/types.h>	/* open */
#include <fcntl.h>
#include <unistd.h>	/* close , write */
#include <sys/time.h>
#include <string.h>
#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif
#include <pipe_messages.h>

#define TUBE_NOMME "tube_tp_5"

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;
     char message[MESSAGES_TAILLE] ;

    int fd_tube;
    int i;

    struct timeval temps ;
    double temps_debut;
    double temps_fin;

     /*----------*/


     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Emetteur dans la communication par flot\n\n" , nomprog );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }
     strcpy( nomprog , tab_arg[0] );

     /* Creation du tube nomme */
    if( mknod( TUBE_NOMME, S_IFIFO | 0666 , 0 ) )
    {
        perror("Erreur durant la creation du tube nomme");
        exit(-2);
    }

    fprintf(stderr, "Tube cree avec succes\n");

    /* Ouverture du tube nomme en ecriture seule */
    if( (fd_tube = open( TUBE_NOMME, O_WRONLY, 0 )) == -1 )
    {
        perror("Probleme durant l'ouverture du tube nomme");
        exit(-1);
    }

    fprintf(stderr, "\n---------- Debut emission %s ----------\n" , nomprog ) ;

    /* Recuperation de l'heure actuelle avec precision de l’ordre de la microseconde */
    gettimeofday(&temps, NULL);
    temps_debut = temps.tv_sec+(temps.tv_usec/1000000.0);


    /* Remplissage du message avec des Y */
    pipe_remplir( message , 'Y') ;

    /* Ecriture du message MESSAGES_NB fois dans le tube nomme */
    for(i=0; i<MESSAGES_NB; i++)
    {
        write( fd_tube, &message, MESSAGES_TAILLE);
    }

    /* Recuperation de l'heure actuelle avec precision de l’ordre de la microseconde */
    gettimeofday(&temps, NULL);
    temps_fin = temps.tv_sec+(temps.tv_usec/1000000.0);

    fprintf(stderr, "\nTemps d'emission           =  %.6lf secondes", temps_fin - temps_debut);
    fprintf(stderr, "\nTemps d'emission / message =  %.6lf secondes\n", (temps_fin - temps_debut) / MESSAGES_NB);
    fprintf(stderr, "\n----------- Fin emission %s -----------\n\n" , nomprog ) ;

    /* Fermeture du tube nomme */
    close( fd_tube );

     exit(0);
}
 
