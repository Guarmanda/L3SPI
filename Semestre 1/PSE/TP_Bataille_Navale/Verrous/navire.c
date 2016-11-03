#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>
#include <time.h>   //pour initialisation du random

#include <bateau.h>
#include <mer.h>


//===============================================
//VERROUILLAGE/DEVERROUILLAGE POUR LA MER ENTIERE
//===============================================
/*
* Verrouille la totalité du fichier mer en vue du placement aléatoire d'un nouveau bâteau dans ce dernier.
* Renvoie CORRECT si le fichier mer pu être verrouillé, ERREUR le cas contraire.
*/
int verrouiller_mer( const int fd,	/* Fichier mer */
                    bateau_t * bateau)  /* Bâteau qui va se déplacer (propriétaire du verrou) */
{
    
    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_WRLCK ;	 // verrou en écriture (exclusif)
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)0;
    verrou.l_len    = 0;
    verrou.l_pid    = bateau_pid_get(bateau);

    printf(" Bateau %c --> attente pose verrou interne sur mer\n" , 
    	bateau_marque_get(bateau));
    //pose bloquante : si mer non verrouillable, le bâteau attend jusqu'à pouvoir la verrouiller
    if( fcntl( fd , F_SETLKW , &verrou ) == -1 )
        return(ERREUR);
    /* Fin de l'attente passive, le verrou est posé */
    printf(" Bateau %c --> pose du verrou interne sur mer\n", bateau_marque_get(bateau));
    return(CORRECT);
}


/*
* Déverrouille la totalité du fichier mer en vue du placement aléatoire d'un nouveau bâteau sur ce dernier
* Renvoie CORRECT ou ERREUR en cas d'échec.
*/
int deverrouiller_mer( const int fd,	  /* Fichier mer */
                      bateau_t * bateau)  /* Bâteau qui s'est deplacé (propriétaire du verrou) */
{
    
    struct flock verrou;// Déclaration d'un verrou interne (structure flock) */

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_UNLCK ;	  // levée de verrou
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)0;
    verrou.l_len    = 0;
    verrou.l_pid    = bateau_pid_get(bateau);
    
    printf(" Bateau %c --> demande levee verrou interne sur mer\n" , bateau_marque_get(bateau));
    if( fcntl( fd , F_SETLK , &verrou ) == -1 )
        return(ERREUR);
    printf(" Bateau %c --> levee du verrou interne sur mer\n", bateau_marque_get(bateau));
    return(CORRECT);
}


//=========================================================
//VERROUILLAGE/DEVERROUILLAGE POUR LE VOISINAGE D'UN BATEAU
//=========================================================
/*
* Verrouille le voisinage passé en paramètre d'un bâteau passé en paramètre en vue du déplacement de ce bâteau
* Renvoie CORRECT si tout le voisinage a pu être verrouille, ERREUR le cas contraire.
*/
int navire_verrouiller_voisinage( const int fd,			 /* Fichier mer */
                                 bateau_t * bateau,		 /* Bâteau qui va se déplacer */
                                 coords_t * const liste_voisins,  /* Liste des cases voisines */
                                 const int nb_voisins)		 /* Nombre de cases voisines dans la liste */
{
    int i;
    case_t case_mer ;

    struct flock verrou; // Déclaration d'un verrou interne (structure flock) */

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_WRLCK ; // verrou en écriture (exclusif)
    verrou.l_whence = (short)0 ;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);

    /* Parcours la liste des cases à verrouiller */
    for(i=0; i<nb_voisins; i++){ //pour chaque case
        mer_case_lire( fd , liste_voisins->coords[i], &case_mer );
        if( case_mer == MER_CASE_LIBRE ){
            verrou.l_start  = (long)liste_voisins->coords[i].pos;
	    	printf(" Bateau %c --> demande pose d'un verrou interne sur la case en [%i,%i]\n", 
	    		bateau_marque_get(bateau),liste_voisins->coords[i].l,liste_voisins->coords[i].c);
        	//pose non bloquante : si le verrouillage d'un voisin n'est pas possible, on retourne ERREUR
            if( fcntl( fd , F_SETLK , &verrou ) == -1 )
                return(ERREUR);
            printf(" Bateau %c --> pose le verrou interne sur la case en [%i,%i]\n",
	    		bateau_marque_get(bateau),liste_voisins->coords[i].l,liste_voisins->coords[i].c);
        }
    }
    return(CORRECT);
}


/*
* Déverrouille le voisinage passé en paramètre d'un bâteau passé en paramètre
* Renvoie CORRECT ou ERREUR en cas d'échec.
*/
int navire_deverrouiller_voisinage( const int fd,		   /* Fichier mer */
                                   bateau_t * bateau,		   /* Bâteau qui va se déplacer */
                                   coords_t * const liste_voisins,  /* Liste des cases voisines */
                                 const int nb_voisins)		   /* Nombre de cases voisines dans la liste */
{
    int i;

    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée */
    verrou.l_type   = F_UNLCK ;	// levée de verrou
    verrou.l_whence = (short)0 ;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);


    // Parcours la liste des cases à déverrouiller
    for(i=0; i<nb_voisins; i++){ //pour chaque case
		
		verrou.l_start  = (long)liste_voisins->coords[i].pos;
        printf(" Bateau %c --> demande levee d'un verrou interne sur la case en [%i,%i]\n", 
			bateau_marque_get(bateau),liste_voisins->coords[i].l,liste_voisins->coords[i].c);

        	// On déverrouille la case
        if( fcntl( fd , F_SETLK , &verrou ) == -1 )
          	return(ERREUR);
        printf(" Bateau %c --> leve le verrou interne sur la case en [%i,%i]\n", 
			bateau_marque_get(bateau),liste_voisins->coords[i].l,liste_voisins->coords[i].c);
		
    }
    return(CORRECT);
}



//=======================================
//VERROUILLAGE/DEVERROUILLAGE D'UNE CIBLE
//=======================================
/*
* Verrouille une cible passée en paramètre pour un bâteau passé en paramètre.
* Le bateau tente de poser un verrou en écriture (exclusif) sur la case. En cas d'échec, cela
* signifie que la case est déjà verrouillée (bouclier activé ou cible vérouillée par un autre bâteau). 
* Il ne peut donc pas tirer.
* Renvoie CORRECT si la cible a pu être verrouille (pas de bouclier) ou ERREUR le cas contraire.
*/
int navire_verrouiller_cible( const int fd,	 /* Fichier mer */
                             bateau_t * bateau,  /* Bateau tireur */
                             coord_t cible)	 /* Cible visée */
{
    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_WRLCK ;	// verrou en écriture (exclusif)
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)cible.pos;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);

    printf(" Bateau %c --> demande verrouillage de la cible [%i,%i]\n", 
    	bateau_marque_get(bateau),cible.l,cible.c);

    // On pose un verrou interne non bloquant exclusif sur la case à verrouiller
    if( fcntl( fd , F_SETLK , &verrou ) == -1 ) //Renvoie -1 si pose impossible
        return(ERREUR);

    printf(" Bateau %c --> verrouillage de la cible [%i,%i]\n", 
    	bateau_marque_get(bateau),cible.l,cible.c);

    return(CORRECT);
}

/*
* Déverrouille une cible passée en paramètre pour un bâteau passé en paramètre.
* Renvoie CORRECT si la cible a pu être déverrouillée ou ERREUR le cas contraire.
*/
int navire_deverrouiller_cible( const int fd,	   /* Fichier mer */
                               bateau_t * bateau,  /* Bateau tireur */
                               coord_t cible)	   /* Cible visee */
{
    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_UNLCK ;	// levée de verrou
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)cible.pos;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);

    printf(" Bateau %c --> demande deverrouillage de la cible [%i,%i]\n", 
    	bateau_marque_get(bateau),cible.l,cible.c);

    // Levée du verrou
    if( fcntl( fd , F_SETLK , &verrou ) == -1 )
        return(ERREUR);
        
    printf(" Bateau %c --> deverrouillage de la cible [%i,%i]\n", 
    	bateau_marque_get(bateau),cible.l,cible.c);

    return(CORRECT);
}


//========================================================
//VERROUILLAGE/DEVERROUILLAGE POUR LE BOUCLIER D'UN BATEAU
//========================================================
/*
* Verrouille les cases constituant le corps d'un bâteau passé en paramètre (= activation du bouclier)
* Renvoie CORRECT ou ERREUR en cas d'échec.
*/
int navire_verrouiller_corps( const int fd,	 /* Fichier mer */
                             bateau_t * bateau)  /* Bâteau dont on souhaite verrouiller le corps */
{
    int i;
    coords_t * corps_bateau;

    corps_bateau = bateau_corps_get(bateau);// Récupération des coordonnées du corps du bâteau

    struct flock verrou; // Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_RDLCK ;		    	/* verrou en lecture (exclusif) */
    verrou.l_whence = (short)0 ;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);

    // Parcours la liste des cases à verrouiller (corps du bâteau)
    for(i=0; i<BATEAU_TAILLE; i++){ //pour chaque case
        // On indique la posit° de la case à verrouiller dans le champ l_start de la struct flock
        verrou.l_start  = (long)corps_bateau->coords[i].pos;

        printf(" Bateau %c --> attente bouclier sur la case [%i,%i]\n", 
			bateau_marque_get(bateau),corps_bateau->coords[i].l,corps_bateau->coords[i].c);

        // Pose bloquante : le bâteau attend de pouvoir activer son boulier pour poursuivre
        if (fcntl(fd, F_SETLKW, &verrou) == -1 )
            return(ERREUR);

    	// Fin de l'attente passive, le verrou est posé
        printf(" Bateau %c --> pose bouclier sur la case en [%i,%i]\n", 
			bateau_marque_get(bateau),corps_bateau->coords[i].l,corps_bateau->coords[i].c);
    }
    return(CORRECT);
}

/*
* Déverouille les cases constituant le corps d'un bâteau passé en paramètre (= désactivation du bouclier)
* Renvoie CORRECT ou ERREUR en cas d'échec.
*/
int navire_deverrouiller_corps( const int fd,	   /* Fichier mer */
                               bateau_t * bateau)  /* Bateau dont on souhaite verrouiller le corps */
{
    int i;
    coords_t * corps_bateau;

    corps_bateau = bateau_corps_get(bateau);// Récupération des coordonnées du corps du bâteau
    
    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_UNLCK ; // levée de verrou
    verrou.l_whence = (short)0 ;
    verrou.l_len    = (long)MER_TAILLE_CASE;
    verrou.l_pid    = bateau_pid_get(bateau);

    // Parcours la liste des cases a deverrouiller (corps du bâteau)
    for(i=0; i<BATEAU_TAILLE; i++){ //pour chaque case
        // On indique la posit° de la case à déverrouiller dans le champ l_start de la struct flock
        verrou.l_start  = (long)corps_bateau->coords[i].pos;
        printf(" Bateau %c --> demande levee d'un verrou interne sur la case en [%i,%i]\n", 
			bateau_marque_get(bateau),corps_bateau->coords[i].l,corps_bateau->coords[i].c);

        // On déverouille la case
        if( fcntl(fd, F_SETLK, &verrou) == -1 )
            return(ERREUR);

        printf(" Bateau %c --> leve le verrou interne sur la case en [%i,%i]\n", 
			bateau_marque_get(bateau),corps_bateau->coords[i].l,corps_bateau->coords[i].c);
    }
    return(CORRECT);
}

//====================================================
//VERROUILLAGE/DEVERROUILLAGE POUR LE HEADER DE LA MER
//====================================================
/*
* Verrouille le header du fichier mer en lecture pour signaler à vision.c qu'un déplacement est en cours.
* Renvoie CORRECT si le header a pu être verouillé, ERREUR le cas contraire.
*/
int verrouiller_header_mer( const int fd,      /* Fichier mer */
                           bateau_t * bateau)  /* Bâteau qui va se déplacer (propriétaire du verrou) */
{
    // Déclaration d'un verrou interne (structure flock)
    struct flock verrou;

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_RDLCK ; // verrou en lecture (paratagé)
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)0 ;
    verrou.l_len    = MER_TAILLE_ENTETE;
    verrou.l_pid    = bateau_pid_get(bateau);

    printf(" Bateau %c --> attente pose verrou interne sur l'entete du fichier mer\n" ,
    	bateau_marque_get(bateau));

    //pose bloquante : si trop de verrous existants, le bâteau attend de pouvoir verrouiller
    if( fcntl( fd , F_SETLKW , &verrou ) == -1 ) 
        return(ERREUR);

    // Fin de l'attente passive, le verrou est posé
    printf(" Bateau %c --> pose du verrou interne  sur l'entete du fichier mer\n", 
    	bateau_marque_get(bateau));

    return(CORRECT);
}

/*
* Déverrouille le header du fichier mer
* Renvoie CORRECT si le header a pu être verrouillé, ERREUR le cas contraire.
*/
int deverrouiller_header_mer( const int fd,	/* Fichier mer */
                             bateau_t * bateau)	/* Bâteau qui s'est déplacé (propriétaire du verrou) */
{
    struct flock verrou;// Déclaration d'un verrou interne (structure flock)

    // Construction du verrou interne : affectation de la structure flock précédemment créée
    verrou.l_type   = F_UNLCK ; // levée de verrou
    verrou.l_whence = (short)0 ;
    verrou.l_start  = (long)0 ;
    verrou.l_len    = MER_TAILLE_ENTETE;
    verrou.l_pid    = bateau_pid_get(bateau);

    printf(" Bateau %c --> demande levee verrou interne sur l'entete du fichier mer\n" ,
    	bateau_marque_get(bateau));

    if( fcntl( fd , F_SETLK , &verrou ) == -1 )
        return(ERREUR);

    printf(" Bateau %c --> levee du verrou interne sur l'entete du fichier mer\n", 
    	bateau_marque_get(bateau));

    return(CORRECT);
}



/* 
 *  Programme principal 
 */

int
main( int nb_arg , char * tab_arg[]){

	char fich_mer[128] ;
	case_t marque = MER_CASE_LIBRE ;
	char nomprog[128] ;              // Nom du programme (navire)
	
	int fd_mer ; // Descripteur du fichier mer
	int nb_bateau; // Nombre de bateaux dans la mer
	
	int no_err = CORRECT ;
	booleen_t deplacement;
	
	// Gestion du bateau
	booleen_t couler = FAUX; // L'état du bateau :
							// VRAI-> le bateau a coulé
							// FAUX-> le bateau navigue
	bateau_t *nouveau_bateau = malloc(sizeof(bateau_t));
	pid_t pid;            // PID du bateau
	float energie = 0.0 ; // Energie du bateau

	// Gestion des cases voisines
    coords_t * liste_voisins = (coords_t *)NULL ;
    booleen_t ciblage = FAUX; // Etat du ciblage du bateau :
    					// VRAI-> le bateau a trouvé une cible;
    					// FAUX-> le bateau n'a pas trouvé de cible;
    coord_t * cible = malloc(sizeof(coord_t)) ;

	/*----------*/

	strcpy( nomprog , tab_arg[0] ) ;

	if( nb_arg != 4 ){
		fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n", nomprog );
		exit(-1);
	}

	if( strlen(tab_arg[2]) !=1 ){
		fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",nomprog , tab_arg[2] );
		exit(-1) ;
	}

	strcpy( nomprog , tab_arg[0] );
	strcpy( fich_mer , tab_arg[1] );
	marque = tab_arg[2][0] ;
	sscanf( tab_arg[3] , "%f" , &energie );
  	
  	/* Ouverture fichier mer */
    if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 ){
        fprintf( stderr, "%s : Probleme durant l'ouverture sur %s\n", nomprog , fich_mer);
        exit(-1);
    }
    printf("Mer ouverte. \n");
  	
	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());
	pid = getpid();
	
	printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n", nomprog , marque , pid);

	// Initialisation des information du bateau
	bateau_marque_set(nouveau_bateau, marque);
	bateau_pid_set(nouveau_bateau, pid);
	
	
	// Initialisation du bateau dans la mer
	
	printf(" Bateau %c : Verrouillage de la mer \n", bateau_marque_get(nouveau_bateau));
	// Si le bâteau n'a pu verrouiller le fichier mer à terme de son attente passive, il est tué
    if ((no_err = verrouiller_mer(fd_mer, nouveau_bateau))){
        printf(" Probleme durant le verrouillage de la mer pour l'initialisation du bâteau %c\n", 
			bateau_marque_get(nouveau_bateau));
        exit(no_err);
    }
	printf(" Bateau %c : Mer verrouiller \n", bateau_marque_get(nouveau_bateau));


	// On initialise le bateau dans la mer
	if ((no_err = mer_bateau_initialiser(fd_mer, nouveau_bateau))){
		printf( "%s : erreur %d dans mer_bateau_initialiser.\n", nomprog, no_err);
		
		if (no_err == ERREUR)
			printf( " mer_bateau_initialiser n'a pas pu placer le bateau %c dans la mer.\n", bateau_marque_get(nouveau_bateau));
		
		exit(no_err);
	}else{
		// On incrémente le nombre de bateau sur la mer
		mer_nb_bateaux_lire(fd_mer, &nb_bateau);
		mer_nb_bateaux_ecrire(fd_mer, ++nb_bateau);
	}

	printf("Bateau %c initialisé. \n", bateau_marque_get(nouveau_bateau));
	

	// Deverrouillage de la mer
	if ((no_err = deverrouiller_mer(fd_mer, nouveau_bateau))){
        printf("Probleme durant le deverrouillage de la mer pour l'initialisation du bâteau %c\n", 
        	bateau_marque_get(nouveau_bateau));
        exit(no_err);
    }
	

	/* Si le bateau dispose d'assez d'energie, il active son bouclier */
    if(energie >= BATEAU_SEUIL_BOUCLIER){ //BATEAU_SEUIL_BOUCLIER défini dans bateau.h
    	if( (no_err = navire_verrouiller_corps(fd_mer, nouveau_bateau))){
            printf("Probleme durant l'activation du bouclier du bâteau %c\n",
            	bateau_marque_get(nouveau_bateau));
            exit(no_err) ;
        }
    }
    
	sleep(5); // Attente pour permettre aux autres bateaux de s'initlialiser
	
	
	// Les bateaux ne cessent de se déplacer tant qu'ils sont en vie
	while (!couler){
		
		// Attente aléatoire de 3 à 5 seconde avant un déplacement
		sleep(3+(2)*((float)(rand())/(float)(RAND_MAX)));
		
		//on desative son bouclier
    	if(energie >= BATEAU_SEUIL_BOUCLIER){
            if( (no_err = navire_deverrouiller_corps(fd_mer, nouveau_bateau))){
                printf("Probleme durant la desactivation du bouclier du bâteau %c\n",
		    		bateau_marque_get(nouveau_bateau));
                exit(no_err) ;
            }
        }

		// Avant de se déplacer, le bateau vérifie si il n'a pas été coulé ou qu'il n'est pas vainqueur
		mer_bateau_est_touche(fd_mer, nouveau_bateau, &couler);
		mer_nb_bateaux_lire(fd_mer, &nb_bateau);
		
		if (couler){ // Le bateau a coulé
			printf(" Le bateau %c a été coulé\n", bateau_marque_get(nouveau_bateau));
		}else if(nb_bateau == 1){
			printf("  Le bateau %c est vainqueur\n", bateau_marque_get(nouveau_bateau));
			couler = VRAI;
		}else{
			
			if(energie){// si le navire n'a plus d'energie, il ne peux pas se déplacer

				// On verrouille les cases voisines pour le déplacement
				mer_voisins_rechercher(fd_mer, nouveau_bateau, &liste_voisins);
				if ( -1 == navire_verrouiller_voisinage(fd_mer, nouveau_bateau, liste_voisins, coords_nb_get(liste_voisins))){
        			printf("Probleme durant le verrouillage des case voisines du bâteau %c\n", 
						bateau_marque_get(nouveau_bateau));
        			
    			}else{
    			
            		// Le bâteau verrouille le header du fichier mer pour signaler à vision.c qu'un déplacement est en cours.
            		verrouiller_header_mer(fd_mer, nouveau_bateau);
            
    				// On déplace le bateau
    				if ((no_err = mer_bateau_deplacer(fd_mer, nouveau_bateau, liste_voisins, &deplacement))){
        				printf("Probleme durant le déplacement du bâteau %c\n", 
							bateau_marque_get(nouveau_bateau));
        				exit(no_err);
    				}
    		
    				// Déverouillage du header du fichier mer
            		deverrouiller_header_mer(fd_mer, nouveau_bateau);
    		
    				// Diminution de l'énergie
            		if(deplacement){
            			energie -= (20*BATEAU_MAX_ENERGIE)/100;
						energie = (energie < 0)? 0 : energie;
            			printf(" Energie restante pour le bateau %c : %f\n", 
            				bateau_marque_get(nouveau_bateau), energie);
	    			}

					// On deverrouille les cases voisines pour le déplacement
    				navire_deverrouiller_voisinage(fd_mer, nouveau_bateau, liste_voisins, coords_nb_get(liste_voisins));
				}


				/* Si le bateau dispose d'assez d'energie, il re-active son bouclier */
    			if(energie >= BATEAU_SEUIL_BOUCLIER){ //BATEAU_SEUIL_BOUCLIER défini dans bateau.h
    				if( (no_err = navire_verrouiller_corps(fd_mer, nouveau_bateau))){
            			printf("Probleme durant l'activation du bouclier du bâteau %c\n",
	    					bateau_marque_get(nouveau_bateau));
            			exit(no_err) ;
        			}
    			}

    			coords_destroy(&liste_voisins);
    		
    		}// Mais même sans energie, il peux tirer

			printf(" Bateau %c cherche une cible \n",
					bateau_marque_get(nouveau_bateau));
			
			
    		// On cherche une cible
    		if ((no_err = mer_bateau_cible_acquerir(fd_mer, nouveau_bateau, &ciblage, cible))){
    			fprintf( stderr,"%s : erreur %d dans mer_bateau_cible_acquerir\n", nomprog, no_err);
            	exit(no_err);
    		}
			
			
    		// Et on la verrouille 
    		if (ciblage){

				printf(" Bateau %c a acquis la cible en [%i,%i] \n",
					bateau_marque_get(nouveau_bateau), coord_ligne_get(*cible), coord_colonne_get(*cible));
    			// On tente de verrouiller la case où l'on souhaite tirer
    			if (ERREUR != navire_verrouiller_cible(fd_mer, nouveau_bateau, *cible)){
        			
        			// Tir d'un boulet sur la cible acquise
                	if ((no_err = mer_bateau_cible_tirer(fd_mer, *cible))){
                 	   fprintf( stderr, "%s : erreur %d dans mer_bateau_cible_tirer pour le bateau %c\n", 
		    				nomprog, no_err, bateau_marque_get(nouveau_bateau));
                 	   exit(no_err) ;
                	}
        			
        			//on tente de deverouiller la case où l'on a tiré
                	if(ERREUR == navire_deverrouiller_cible(fd_mer, nouveau_bateau, *cible)){
                    	fprintf( stderr, "%s : erreur %d dans deverouillage cible pour le bateau %c\n", 
		    				nomprog, no_err, bateau_marque_get(nouveau_bateau));
                    	exit(no_err) ;
                	}
    			}else{
    				printf("Impossible de verrouiller la cible : cible protegee\n");
    			}
    		}
			
  			/***********/
  			/* A FAIRE */
  			/***********/
		}
	}
	
	mer_bateau_couler(fd_mer, nouveau_bateau); // On détruit le bateau sur la mer
	bateau_destroy(&nouveau_bateau); // Et on le détruit définitivement 
	
	// On décrémente le nombre de bateau sur la mer
	mer_nb_bateaux_lire(fd_mer, &nb_bateau);
	mer_nb_bateaux_ecrire(fd_mer, --nb_bateau);
	
	printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", nomprog , marque , pid);

	close(fd_mer);
	exit(0);
}
