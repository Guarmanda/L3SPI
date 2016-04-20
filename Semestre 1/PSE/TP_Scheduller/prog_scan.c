#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <commun.h>

int
main( int argc , char * argv[] ) 
{
  char nomprog[MAX_STRING] ;
  char marque[2] ;
  int nb = 0 ; 
  int i = 0 ; 

  if( argc != 2 ) 
    {
      printf( "Programme pour test scheduller lisant <nb> caracteres au clavier\n" ) ; 
      printf( "Usage : %s <nb>\n" , argv[0] ) ; 
      exit(-1) ; 
    }

  strcpy( nomprog , argv[0] ) ; 
  nb = atoi(argv[1] ) ;
  
  printf( "=====  Debut de %s (nb = %d) =====\n" ,
	  nomprog , nb ) ;

  sleep(1) ; 

  for( i=0 ; i<nb ; i++ ) 
    {
      scanf( "%s" , marque ) ;
      printf( "%c\n" , marque[0] ) ; fflush(stdout) ; 
    }

  printf( "\n======  Fin de %s (nb = %d) ======\n" ,
	  nomprog , nb ) ;
  
  return(0) ;
}
