#ifndef _PROC_H_
#define _PROC_H_

#include <stdio.h>
#include <unistd.h>

#include <commun.h>

/*
 * Type d'un processus
 */
typedef struct proc_s
{
  pid_t pid ;		/* Pid */
  booleen_t fini ;	/* Indique s'il est termine */
} proc_t ; 

/*
 * Fonctions 
 */

/* Fonctions Get */
extern 
booleen_t proc_est_fini( const proc_t proc ) ; 

extern 
pid_t proc_pid_lire( const proc_t proc ) ; 

/* Fonctions Set */
extern 
err_t proc_pid_ecrire( proc_t * const proc , const pid_t pid ) ;

extern 
err_t proc_fini_positionner( proc_t * const proc , 
			     const booleen_t position) ; 
extern 
err_t proc_fini_vrai( proc_t * const proc ) ; 

extern 
err_t proc_fini_faux( proc_t * const proc ) ;  

/* Affichage d'un processus */
extern
void proc_afficher( const proc_t proc) ; 

/* Affichage d'un tableau de processus */
extern
void proc_liste_afficher( const proc_t * const tab_procs , /* tableau des processus */
			  const int nb_procs ) ; /* Nb de processus */

/* Recherche d'un processus dans un tableau de processus sur son pid */
extern 
booleen_t proc_liste_rechercher( const proc_t * const tab_procs , 
				 const int nb_procs , 
				 const pid_t pid, 
				 int * id_proc ) ;

/* Indique si tous les processus d'un tableau sont termines */
extern
booleen_t proc_liste_sont_finis( const proc_t * const tab_procs , 
			   const int nb_procs ) ;

#endif
