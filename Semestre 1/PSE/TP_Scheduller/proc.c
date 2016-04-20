#include <proc.h>

extern 
pid_t proc_pid_lire( const proc_t proc )
{
  return( proc.pid ) ;
}

extern 
booleen_t proc_est_fini( const proc_t proc )
{
  return( proc.fini ) ;
} 

extern 
err_t proc_pid_ecrire( proc_t * const proc , const pid_t pid )
{
  (*proc).pid = pid ;
  return(OK) ; 
}

extern 
err_t proc_fini_positionner( proc_t * const proc , 
			     const booleen_t position)
{
 (*proc).fini =  position;
  return(OK) ; 
} 

extern 
err_t proc_fini_vrai( proc_t * const proc )
{
  return( proc_fini_positionner( proc , VRAI ) );
} 

extern 
err_t proc_fini_faux( proc_t * const proc )
{
  return( proc_fini_positionner( proc , FAUX ) );
} 

extern
void proc_afficher( const proc_t proc) 
{
  printf( "pid: %d , etat: %s" , 
	  proc.pid , ( proc.fini ? "FINI" : "EN COURS") ) ; 
  fflush(stdout) ; 
}

extern
void proc_liste_afficher( const proc_t * const tab_procs , /* tableau des processus */
			 const int nb_procs ) /* Nb de processus */
{
  int i = 0 ; 

  for( i=0 ; i<nb_procs ; i++ ) 
    {
      proc_afficher( tab_procs[i] ) ; 
      printf("\n") ;
    }
}

extern 
booleen_t proc_liste_rechercher( const proc_t * const tab_procs , 
				 const int nb_procs , 
				 const pid_t pid, 
				 int * id_proc ) 
{
  int i = 0 ;
  booleen_t trouve = FAUX ;

  (*id_proc) = -1 ;
  while( (i<nb_procs) && (!trouve) )
    {
      if( tab_procs[i].pid == pid )
	trouve = VRAI ; 
      else
	i++ ; 
    }
  if( trouve ) 
    (*id_proc) = i ;

  return(trouve) ; 
}




extern
booleen_t proc_liste_sont_finis( const proc_t * const tab_procs , 
				 const int nb_procs )
{
  booleen_t tous_finis = VRAI ;
  int i = 0 ; 
  
  for( i=0 , tous_finis = VRAI ; (i<nb_procs)  && (tous_finis==VRAI) ; i++ ) 
    {
      if( ! tab_procs[i].fini )
	tous_finis = FAUX ; 
    }
  return(tous_finis) ; 
}


