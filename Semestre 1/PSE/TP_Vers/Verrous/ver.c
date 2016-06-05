#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>
#include <vers.h>
#include <jeu.h>


/**
 * Verrouille le fichier terrain dans son ensemble
 * Renvoie CORRECT si le fichier à pu être verrouillé, ERREUR sinon
 */
int verrouille_terrain(const int fd, ver_t *ver){


	/* Création du verrou interne */
	struct flock verrou;
	verrou.l_whence = 0;
    verrou.l_start  = 0;
	verrou.l_len    = 0;
	verrou.l_pid    = ver->pid;
	verrou.l_type   = F_WRLCK;
    

    if( fcntl( fd, F_SETLKW, &verrou)==-1){ // Pose bloquante : Attente passive si terrain non verrouillable
        return(ERREUR);
	}

    //printf(" Ver %c --> Pose du verrou effectuer.\n",ver->marque);
    return(CORRECT);
}

/**
 * Leve le verrou du fichier terrain
 * Renvoie CORRECT, ERREUR si echec
 */
int deverrouiller_terrain(const int fd, ver_t *ver){


    /* Création du verrou interne */
    struct flock verrou;
    verrou.l_whence = 0;
    verrou.l_start  = 0;
    verrou.l_len    = 0;
    verrou.l_pid    = ver->pid;
    verrou.l_type   = F_UNLCK;
    
    if( fcntl( fd, F_SETLK, &verrou)==-1){ // Pose bloquante : Attente passive si terrain non verrouillable
        return(ERREUR);
	}

    return(CORRECT);
}


int
main( int nb_arg , char * tab_arg[] )
{

     /* Parametres */
     char fich_terrain[128] ;
     case_t marque = TERRAIN_CASE_LIBRE ;
     char nomprog[128] ;

     /* variables generales */
     char mess[256];
     booleen_t arret = FAUX ;
     int no_err = 0;

     /* variables terrain */
     int fd_terrain ;
     coord_t * liste_voisins = (coord_t *)NULL ;
     int nb_voisins = 0 ;
     int ind_libre = 0 ;
     int nb_lig;
     int nb_col;

     /* variables ver */
     ver_t ver ;
     int en_vie =1;


     if( nb_arg != 3 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <marque>\n",
		   tab_arg[0] );
	  exit(-1);
     }

     if( strlen(tab_arg[2]) !=1 )
     {
	  fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
		   tab_arg[0] , tab_arg[2] );
	  exit(-1) ;
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
     marque = tab_arg[2][0] ;



	 /* Ouverture du ficher terrain */
	 if((fd_terrain=open(fich_terrain,O_RDWR,0666))==-1){
		 fprintf(stderr, "%s : Probleme durant l'ouverture du fichier %s.\n",
			nomprog, fich_terrain);
		 exit(-1);
	 }
	 printf("Terrain ouvert...\n");

    terrain_dim_lire(fd_terrain, &nb_lig, &nb_col);

	 /* Initialisation des information du ver */

     printf( "\n\n%s : ----- Debut du ver %c (%d) -----\n\n ",
	     nomprog , marque , getpid() );


     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());

	 ver.pid=getpid();
	 printf("PID du nouveau ver : %d\n",ver.pid);
	 ver.marque=marque;

    /* Initialise la position initial du ver */
    if((no_err = jeu_ver_initialiser(fd_terrain, nb_lig, nb_col, &ver))){
        printf("Erreur dans l'initialisation du ver %c.\n",
               ver.marque);
        return no_err;
    }
    
    terrain_voisins_rechercher( fd_terrain, ver.tete, &liste_voisins, &nb_voisins);

    /* Pose d'un verrou sur le terrain pour initialiser le ver */
	 if( (no_err=verrouille_terrain( fd_terrain, &ver))){
		 printf("Erreur dans le verrouillage du terrain pour initialiser le ver %c.\n",
			ver.marque);
		 return no_err;
	 }

    /* Initialisation du ver dans le terrain */
    if( ( no_err=terrain_marque_ecrire( fd_terrain , ver.tete, ver.marque) ) ){
        fprintf( stderr, "%s : erreur %d dans terrain_marque_ecrire\n", nomprog , no_err );
        if( no_err == ERREUR ){
            fprintf( stderr,"\t(terrain_marque_ecrire n'a pas pu placer le ver \"%c\" dans la terrain)\n" ,
                ver.marque );
        }
        exit(no_err) ;
    }

    // Déverouillage du fichier terrain
    if( ( no_err=deverrouiller_terrain( fd_terrain, &ver))){
        printf("Probleme durant le deverouillage du terrain post-initialisation du ver %c\n",
                ver.marque);
        exit(no_err) ;
    }

    sleep(5);// Attente pour permettre aux autres ver de s'initlialiser


    // Les vers ne cessent de se déplacer tant qu'il reste en vie
    while( en_vie ){
        /* Attente aléatoire de 2 à 5 secondes avant un déplacement */
        sleep(2 + (5-2)*((float)(rand()) / (float)(RAND_MAX)));


        // Preparation du deplacement

        /* Récupération de la liste des cases voisines au ver */
        if( (no_err = terrain_voisins_rechercher( fd_terrain, ver.tete, &liste_voisins, &nb_voisins)) ){
            fprintf( stderr, "%s : erreur %d dans terrain_voisins_rechercher\n", nomprog , no_err );
            exit(no_err) ;
        }

        // Verouillage du terrain

        if (verrouille_terrain( fd_terrain, &ver) == -1 ){
            printf ("--> Erreur lors du verouillage des cases voisines\n");
        }
        else
        {
            /* Déplacement */

            if( (no_err = terrain_case_libre_rechercher( fd_terrain, liste_voisins, nb_voisins, &ind_libre )) ){
                fprintf( stderr, "%s : erreur %d dans terrain_case_libre_rechercher\n", nomprog , no_err );
                exit(no_err) ;
            }

            if(ind_libre!=-1){
                if( (no_err = terrain_marque_ecrire( fd_terrain, liste_voisins[ind_libre], ver.marque ))){
                    fprintf( stderr, "%s : erreur %d dans terrain_marque_evrire\n", nomprog , no_err );
                    exit(no_err) ;
                }else{
                    ver.tete=liste_voisins[ind_libre];
                }
            }else{
                printf("Le ver %c est mort étouffé\n", ver.marque);
                en_vie=0;
            }

        }

        // Déverouillage du terrain
        if( (no_err = deverrouiller_terrain( fd_terrain, &ver)) ){
            printf("Probleme durant le deverouillage des cases voisines au ver %c\n",
                    ver.marque);
            exit(no_err) ;
        }

    }//fin du while

     printf( "\n\n%s : ----- Fin du ver %c (%d) -----\n\n ",
	     nomprog , marque , getpid() );

     exit(0);
}
