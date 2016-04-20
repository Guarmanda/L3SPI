#include <proc.h>

int
main( int argc , char * argv[] ) 
{
  
  int nb_procs = 0 ; 
  int i = 0 ; 
  int id_proc = -1 ; 
  proc_t * tab_proc = NULL; 

  if( argc != 2 ) 
    {
      printf( " Programme de test du TDA proc\n" );
      printf( " usage : %s <nb proc>\n" , argv[0] );
     exit(0); 
    }

  nb_procs = atoi(argv[1]) ; 
  srandom(getpid()) ;
 
  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  /* Creations des processus */
  if( ( tab_proc = malloc( sizeof(proc_t) * nb_procs ) ) == NULL ) 
    {
      char msgerr[MAX_STRING] ;
      sprintf( msgerr , "Pb malloc (%lu octets demandes)\n" , (unsigned long int)( sizeof(proc_t) * nb_procs) );
      perror(msgerr) ; 
      exit(-1)  ; 
    }
  for( i=0 ; i<nb_procs ; i++ )
    {
      proc_pid_ecrire( &(tab_proc[i]) ,  1000+i ) ; 
      proc_fini_faux( &(tab_proc[i]) ) ;
    }
  
  /* Tests des fonctions */

  printf(" Affichage des processus\n"); 
  proc_liste_afficher( tab_proc , nb_procs ) ; 

  printf("Recherches positives des %d processus\n" , nb_procs ); 
  for( i=0 ; i<nb_procs ; i++ )
    {
      if( proc_liste_rechercher( tab_proc , nb_procs , 
				 proc_pid_lire(tab_proc[i]) , 
				 &id_proc ) )
	printf( "OK : Processus %d trouve a l'indice %d\n" , 
		proc_pid_lire(tab_proc[i]) , id_proc ) ;
      else
	printf( "KO !!! : Processus %d pas trouve\n" , 
		proc_pid_lire(tab_proc[i]) ) ;
    }

  printf("Recherche negative du processus 9999\n" ); 
  if( proc_liste_rechercher( tab_proc , nb_procs , 9999 , &id_proc ) )
    printf( "KO !!! : Processus 9999 trouve a l'indice %d\n" , 
	    id_proc ) ;
  else
    printf( "OK : Processus 9999 pas trouve\n" ) ;

 printf( "Test sur indication que tous les processus sont termines\n" ) ;
 if( proc_liste_sont_finis( tab_proc , nb_procs ) )
   printf( "KO \n") ;
 else
   printf("OK\n"); 
 
 id_proc = random()%nb_procs ; 
 printf( "On indique que le processus %d a termine \n" , id_proc ) ;
 proc_fini_vrai(&(tab_proc[id_proc]) ); 

 printf( "Test individuel sur terminaison des processus\n" ) ;
 for( i=0 ; i<nb_procs ; i++ )
   { 
     if( proc_est_fini(tab_proc[i]) )
       {
	 if( i == id_proc )
	   printf( "processus %d termine --> OK\n" , i ) ;
	 else
	   printf("processus %d termine --> KO !!!\n" , i );
       }	 
     else
       printf("processus %d en cours --> OK\n" , i ); 
   }
 
 printf( "On indique que tous les processus sont termines \n" ) ;
 for( i=0 ; i<nb_procs ; i++ )
   { 
     proc_fini_vrai(&(tab_proc[i])) ; 
   }
  
 printf( "Test sur indication que tous les processus sont termines\n" ) ;
 if( proc_liste_sont_finis( tab_proc , nb_procs ) )
   printf( "OK\n") ;
 else
   printf("KO !!!\n"); 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );
 
 return(0) ;
}

