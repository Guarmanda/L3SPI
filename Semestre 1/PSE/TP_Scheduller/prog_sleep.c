#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <commun.h>

int
main( int argc , char * argv[] ) 
{
  char nomprog[MAX_STRING] ;
  char marque ;
  int nbsec = 0 ; 
  int i = 0 ; 

  if( argc != 3 ) 
    {
      printf( "Programme pour test scheduller ayant comme identifiant un caractere <marque> et faisant une pause de <nb secondes>\n" ) ; 
      printf( "Usage : %s <marque> <nb secondes>\n" , argv[0] ) ; 
      exit(-1) ; 
    }

  strcpy( nomprog , argv[0] ) ; 
  marque = argv[1][0]  ; 
  nbsec = atoi(argv[2] ) ;
  
/*   printf( "=====  Debut de %s %c (pause %d) =====\n" ,  */
/* 	  nomprog , marque , nbsec ) ;  */

  sleep(1) ; 

  for( i=0 ; i<nbsec ; i++ ) 
    {
      write( 1 , &marque , 1 ) ;
      sleep(1) ;
    }

/*   printf( "\n======  Fin de %s %c (pause %d) ======\n" ,  */
/* 	  nomprog , marque , nbsec ) ;  */
  
  return(0) ;
}
