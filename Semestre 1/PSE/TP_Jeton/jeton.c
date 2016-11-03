#include <stdio.h>
#include <signal.h> 
#include <errno.h>
#include <unistd.h>  /* write, getpid, pause */
#include <stdlib.h>

/*
 * Les affichages sont faits sur la sortie erreur 
 * qui est supposee ne pas etre redirigee
 */

/*=====
 * Variables Globales 
 *=====
 */

int Jeton ;

/*
 * Handler pour initialiser le 1er processus
 * qui activera le 1er jeton 
 */
void hand_usr1( int sig ) 
{
  fprintf( stderr, "Signal SIGUSR1 recu\n");
  fprintf( stderr, "Mise en circulation du jeton\n");

  /* Initialisation du jeton */
  Jeton = 1;

  /* 1ere ecriture du jeton dans l'anneau */
  write( STDOUT_FILENO , &Jeton, sizeof(Jeton) ) ;
}

/*
 * Programme principal pour la circulation du Jeton 
 */

int main(int nb_arg , char * tab_arg[])
{

  struct sigaction action ;

  /*----------*/

  if( nb_arg != 1 ) 
    {
      fprintf(stderr , "Jeton circulant sur l'anneau de processus:\n" ) ;
      fprintf(stderr , "   - le jeton est un entier\n" ) ;
      fprintf(stderr , "   - il est incremente de 1 quand il arrive sur un nouveau processus\n" ) ;      
      fprintf(stderr , "   - quand il a fait un tour, on affiche sa valeur\n" ) ;
      fprintf(stderr , "usage : %s\n" , tab_arg[0] ) ;
      exit(-1) ;
    }

  /* Capture du signal SIGUSR1 */
  action.sa_flags = 0 ; 
  action.sa_handler = hand_usr1 ;
  sigemptyset(&action.sa_mask) ;
  sigaction( SIGUSR1 , &action , NULL ) ;

  /*
   * La lecture est bloquante pour tous les processus de l anneau 
   * SAUF pour le 1er : il est interrompu par SIGUSR1, sans reprise des appels systeme
   * donc, le 1er, read renvoie -1 et errno == EINTR
   */

  if( (read( STDIN_FILENO , &Jeton , sizeof(Jeton)) == -1) &&
      (errno == EINTR) )
    {
      /* On est dans le Processus initiateur 
       * On reprend ici apres l'execution du handler de SIGUSR1
       * et le read qui est KO
       */
      
      /* Quand on relit le Jeton ==> le jeton a fait un tour */
      read( STDIN_FILENO , &Jeton , sizeof(Jeton)) ;
      fprintf(stderr , "Initiateur : 1er Tour --> detection de  %d processus dans l'anneau \n" , Jeton ) ;

      /* On refait un 2ieme tour */
      write( STDOUT_FILENO , &Jeton , sizeof(Jeton)) ;
      read( STDIN_FILENO , &Jeton , sizeof(Jeton)) ;
      fprintf(stderr , "Initiateur : 2ieme Tour --> detection de  %d processus dans l'anneau \n" , Jeton ) ;
      
      pause();
    }
  else
    {
      /* On est dans un Processus de l'anneau 
       * On reprend ici avec le read OK 
       */

     fprintf(stderr , "Processus %d : 1er Tour --> reception jeton[%d] du precedent\n" , 
	     getpid() , Jeton ) ;

      /* Incrementation de la valeur du jeton */
      Jeton++;
      
      /* Passage du jeton au processus suivant dans l anneau */
      write( STDOUT_FILENO , &Jeton , sizeof(Jeton)) ;
      fprintf(stderr , "Processus %d : 1er Tour --> passage jeton[%d] au suivant\n" , 
	      getpid() , Jeton ) ;
      
      /* Quand on relit le Jeton ==> le jeton a fait un tour */
      read( STDIN_FILENO , &Jeton , sizeof(Jeton)) ;
      fprintf(stderr , "Processus %d : 2ieme Tour --> detection de %d processus dans l'anneau \n" , 
	      getpid() , Jeton ) ;
      write( STDOUT_FILENO , &Jeton , sizeof(Jeton)) ;

      pause();
    }
  
  exit(0);
}
