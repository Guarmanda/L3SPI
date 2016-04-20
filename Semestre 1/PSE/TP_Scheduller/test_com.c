#include <com.h>

int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ;

  if( argc != 2 ) 
    {
      printf( " Programme de test du TDA com\n" );
      printf( " usage : %s <fichier liste des commandes>\n" , argv[0] );
     exit(0); 
    }

  char ListeCommandes[MAX_STRING] ; /* Nom du fichier des commandes */
  strcpy( ListeCommandes , argv[1] ) ;
  
  char *** commandes = NULL ; /* Liste des commandes */
  int nb_commandes = 0 ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  if( ( cr = com_fichier_charger( &commandes , /* tableau commandes a remplir */
				  &nb_commandes , 
				  ListeCommandes ) ) )
    {
      printf( "Pb sur chargement liste de commandes, cr = %d\n" , cr ) ; 
      exit(-1) ; 
    }


  com_liste_afficher(commandes ,  nb_commandes )  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );
 
 return(0) ;
}

