/* 
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

#include "signaux.h"

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int energie ;
pid_t pid_amiral;
bateau_t *bateau;
char fich_bat[128]; //Référence du fichier bateaux
char fich_ami[256] ; //référence du fichier amiral
bateaux_t *bateaux;
case_t marque;

/*
 * Handlers 
 */


static void hdl_ecriture(int signal){

    printf(" Bateau %c --> Ecriture des infos du bateau dans le fichier\n", bateau_marque_get(bateau) );


	// On récupère la liste de bateaux
    if( bateaux_load( &bateaux, fich_bat ) != 0 ){
        printf("Erreur durant la récupération de la liste\n", bateau_marque_get(bateau));
        exit(ERREUR);
    }
    // Le bateau s'ajoute dans la liste
    if( bateaux_bateau_add( bateaux, bateau ) != 0 ){
        printf("Erreur durant l'ajout du bateau %c dans la liste\n", bateau_marque_get(bateau));
        exit(ERREUR);
    }
	// On écrit la liste dans le fichier
    if( bateaux_save( bateaux, fich_bat ) != 0 ){
        printf("Erreur durant l'inscription de la liste de bateaux dans le fichier\n");
        exit(ERREUR);
    }
    // Le bateau signale qu'il a fini d'écrire dans le fichier
    printf(" Bateau %c --> Fin de l'écriture dans le fichier\n", bateau_marque_get(bateau) );
	
    kill( pid_amiral , SIG_INFOS );
	sleep(5);
}

static void hdl_bouclier(int signal){
	
    if( energie < BATEAU_SEUIL_BOUCLIER)
    	kill( pid_amiral , SIG_BCL );
}

static void hdl_energie(int signal){
	
	energie -= (40*BATEAU_MAX_ENERGIE)/100;
	energie = (energie<=0)? 0 : energie;
	printf(" Bateau %c --> Le bateau a fini sont tour. Energie = %d\%\n", bateau_marque_get(bateau), ((energie*100)/BATEAU_MAX_ENERGIE));
    sleep(1);
}

static void hdl_arret_de_jeu(int signal){

	bateaux_load( &bateaux, fich_bat );
    bateaux_bateau_del( bateaux, bateaux_pid_seek( bateaux, getpid()) );
    bateaux_save( bateaux, fich_bat );
	bateau_destroy(&bateau);

    if(signal == SIG_COULE){
        printf(" Bateau %c -> Le bateau a été coulé\n", marque );
    }else if(signal == SIG_WINNER){
        printf(" Bateau %c --> Bateau Vainqueur !\n", marque );
    }else{
        fprintf(stderr, "Signal d'arrêt de jeu non recconu\n");
        exit(ERREUR);
    }

    exit(CORRECT);
}




/*
 * Programme Principal 
 */

int
main( int nb_arg , char * tab_arg[] )
{
	char nomprog[128] ;
	
	int fd_ami;

	pid_t pid_bateau ;
	
	
	struct sigaction action_ecriture, action_fin_tour, action_bouclier;
	
  /*----------*/

	bateau = malloc(sizeof(bateau_t));

	action_ecriture.sa_handler = hdl_ecriture;
    action_ecriture.sa_flags   = 0;
    if (sigaction(SIG_INFOS, &action_ecriture, NULL) < 0){
        perror ("Erreur concernant le signal SIG_INFOS");
        return 1;
    }

	action_fin_tour.sa_handler = hdl_energie;
    action_fin_tour.sa_flags   = 0;
    if (sigaction(SIG_NRJ, &action_fin_tour, NULL) < 0){
        perror ("Erreur concernant le signal SIG_NRJ");
        return 1;
    }

	action_bouclier.sa_handler = hdl_bouclier;
    action_bouclier.sa_flags   = 0;
    if (sigaction(SIG_BCL, &action_bouclier, NULL) < 0){
        perror ("Erreur concernant le signal SIG_ALRM");
        return 1;
    }

	signal(SIG_COULE   , hdl_arret_de_jeu);
    signal(SIG_WINNER  , hdl_arret_de_jeu);

  /* 
   * Capture des parametres 
   */

  if( nb_arg != 4 )
    {
      fprintf( stderr , "Usage : %s <Fichier Bateaux> <fichier amiral> <marque> \n", 
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
	strcpy( nomprog , tab_arg[0] );
	strcpy( fich_bat , tab_arg[1] );
	strcpy( fich_ami , tab_arg[2] );
	marque = tab_arg[3][0];
	

	
	if ( (fd_ami = open( fich_ami, O_RDONLY, 0644)) == -1){
		fprintf( stderr, "%s : Probleme durant l'ouverture sur %s\n", nomprog , fich_ami);
        exit(-1);
    }
	if ( (read( fd_ami, &pid_amiral, sizeof(pid_t))) == -1){
		fprintf( stderr, "%s : Probleme durant la lecture sur %s\n", nomprog , fich_ami);
        exit(-1);
    }

	close(fd_ami);
	// Initialisation des information du bateau

	
	bateau_corps_set( bateau , coords_new());
	bateau_marque_set( bateau , marque );
    bateau_pid_set( bateau , getpid() );

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);
	

  /* Affectation du niveau d'energie */
  energie = BATEAU_MAX_ENERGIE ;
  
  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );

  /*
   * Deroulement du jeu 
   */

	while(1){

        printf(" Bateau %c --> Le bateau demande à jouer\n", bateau_marque_get(bateau) );
        // Attente de 1 seconde entre chaque demande
        sleep(1);

        if( kill(pid_amiral, SIG_JEU) != 0){      
            fprintf(stderr, "Erreur : Impossible de contacter l'amiral \n");
            exit(ERREUR);
		}
    }

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}

