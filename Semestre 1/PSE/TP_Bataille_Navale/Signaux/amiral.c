/* 
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>

#include "signaux.h"

#define BATEAU_NB_MAX 100

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ; //nom du programme (amiral.c)
char fich_bat[256] ; //référence (chemin + nom + extension) du fichier bateaux
char fich_mer[256] ; //référence (chemin + nom + extension) du fichier mer
char fich_ami[256] ; //référence (chemin + nom + extension) du fichier amiral


int fd_mer;
int fd_ami;

bateaux_t *bateaux; // Liste des bateaux
bateau_t *tmp_bateau;
bateau_t *tmp_bateau_cible;
int nb_bateaux; 	  //Nombre de bâteaux dans la liste


//Nombre cumule de bateaux traites par l'amiral
int cumul_bateaux = 0;
int bouclier = 0;

/*
 * FONCTIONS LOCALES
 */

static void hdl_bouclier(int signal){
    bouclier =1;
}


//Declenché par SIG_INFOS. Peu utile, à part pour rendre SIG_INFO capturable.
static void hdl_ecriture_ok(int sig){
    printf("--> Le bateau s'est inscrit dans le fichier\n");
}

//Declenché par SIGALRM. Peu utile, à part pour rendre SIGALRM capturable.
static void hdl_sigalrm(int sig){
    printf("--> Timeout !\n");
}



static void hdl_jeu(int sig, siginfo_t *siginfo, void *context){
    

    //Indice du bateau courant dans la liste en MC
    int indice;

    //Gestion du déplacement
    coords_t * liste_voisins = (coords_t *)NULL;
    booleen_t ok = FAUX;

    // Gestion du tir
    coord_t cible ;
    booleen_t acquisition ;
    int indice_bateau_cible;

	int nb_bateau;
	
	//On temporise les actions
	//sleep(1);

	// On récupère la liste de bateaux
    if( bateaux_load( &bateaux, fich_bat ) != 0 ){
        printf("Erreur durant la récupération de la liste\n");
        exit(ERREUR);
    }

    //On cherche l'indice du bateau expediteur du signal dans la liste en MC
    indice = bateaux_pid_seek(bateaux, siginfo->si_pid);

    //Si la recherche nous retourne -1, c'est que le bateau n'a pas été trouvé dans la liste en MC
    //On offre alors à ce dernier la possibilité de s'ajouter à la liste en MC.
    //Pour cela :
    // - On sauvegarde l'état du jeu (pour ne pas perdre les informations concernant les autres bateaux lors du rechargement)
    // - On envoi le signal SIG_INFOS au bateau pour lui dire de s'inscrire dans le fichier en MS
    // - On attend que le bateau nous retourne ce signal
    // - On recharge la liste à partir du fichier en MS
    if( indice == -1){
        
        bateaux_save(bateaux, fich_bat);

        kill(siginfo->si_pid , SIG_INFOS);

        //On attend la confirmation que le bateau s'est bien écrit en MS 
        //Ou en cas de defaillance du bateau, le signal SIG_ALARM de fin du timeout pour l'écriture en MS.
        sigset_t masque_attente;				//Declaration du masque temporaire pour l'attente
        sigfillset(&masque_attente);           	//On bloque tous les signaux
        sigdelset(&masque_attente, SIG_INFOS); 	//On débloque SIG_INFOS
        sigdelset(&masque_attente, SIGALRM);   	//On débloque SIGALRM

        //Lancement d'un timeout qui stoppera l'attente si elle n'est
        //pas stoppée par la reception du SIG_INFOS attendu du bateau.
        //Dans TIMEOUT secondes, on poursuivera : évite une attente infinie dans le
        //cas d'une défaillance de la part du bateau.
        alarm(2);

        #if DEBUG
            printf("--> Attente du signal SIG_INFOS de confirmation du bateau ou le timeout\n");
		#endif

		//Attente passive avec comme masque le masque "masque_attente"
        sigsuspend(&masque_attente);

        //Attente terminée, on recharge la liste
        bateaux_load(&bateaux, fich_bat);

        //On récupère à nouveau l'indice qui est à présent présent en MC sauf si problème du côté bateau
        indice = bateaux_pid_seek(bateaux, siginfo->si_pid);
        if(indice == -1) //En cas d'échec, on sort de la fonction pour ne pas bloquer le jeu
        {
            printf ("[Amiral] Erreur de recuperation des infos du bateau dont le pid est : %d\n", siginfo->si_pid);
            return;
        }
    }

    //A ce stade, nous avons récupéré l'indice du bateau dans la liste en MC.
    //On regarde alors s'il a été initialisé dans la mer (statut actif) ou initialisé puis coulé (cf commentaires l317)
    //et si ce n'est pas le cas, on tente d'initialiser le bateau dans la mer.
    //En cas d'echec, on sort de la fonction (le bateau retentera ultérieurement de s'initialiser)

	tmp_bateau = bateaux_bateau_get(bateaux, indice);

//	   Vérifie que le bateau n'est pas déjà          Verifie que le bateau n'a pas déjà
//	           initialisé dans la mer                    été initialisé puis coulé
//    \_________________________ _____________________/    \_____________ _____________/
//     			        V                                        V
    
	if( coords_nb_get(bateau_corps_get(tmp_bateau)) == 0 && indice != -1 )
    {
		
        if( mer_bateau_initialiser( fd_mer, tmp_bateau) == ERREUR ) //tentative d'initialisation du bateau dans la mer
        {
            #if !CLEARPRINT
                printf ("[Amiral] Impossible d'initialiser le bateau %c dans la mer\n", bateau_marque_get( tmp_bateau ) );
	    #endif
            return; //une nouvelle demande d'initialisation sera renvoyée par le navire ultérieurement
        }
		
	#if !CLEARPRINT
            printf ("[Amiral] Bateau %c initialisé dans la mer\n", bateau_marque_get( tmp_bateau ) );
	#endif

        //En cas de réussite de l'initialisation dans la mer, on place le statut du bateau à actif
        //bateau_actif_ecrire( &liste_bateaux[indice] , VRAI);
		
		mer_nb_bateaux_lire(fd_mer, &nb_bateau);
		mer_nb_bateaux_ecrire(fd_mer, ++nb_bateau);

        
        //On augmente le nombre cumule de bateaux
        cumul_bateaux ++;
		
		//On sauvegarde la liste de bateaux
		bateaux_save(bateaux, fich_bat);

        //On affiche la mer
        system ("clear");
        if( mer_afficher(fd_mer) == ERREUR ){
            printf ("[Amiral] Impossible d'afficher la mer\n");
            exit(ERREUR) ;
        }

		//sleep(1); //Temporisation d'affichage

		return; //On considère qu'une initialisation coûte un tour de jeu
    }


    
        /////////////////
        // DEPLACEMENT //
        /////////////////

    liste_voisins = coords_new();
		
	#if DEBUG
       printf("--> Recherche des voisins du bateau %c\n", bateau_marque_get( tmp_bateau ) );
	#endif

    if( mer_voisins_rechercher( fd_mer, tmp_bateau, &liste_voisins) == ERREUR )
    {
       printf ("[Amiral] Erreur dans la recherche des voisins du du bateau %c\n", bateau_marque_get( tmp_bateau ) );
       exit(ERREUR);
    }

    if( mer_bateau_deplacer( fd_mer, tmp_bateau, liste_voisins, &ok ) == ERREUR )
    {
        printf ("[Amiral] Erreur durant le déplacement du du bateau %c\n", bateau_marque_get( tmp_bateau ) );
        exit(ERREUR);
    }

    coords_destroy(&liste_voisins);

    if( ok ) //Le bateau est parvenu a se déplacer
    {
	#if !CLEARPRINT
        printf ("[Amiral] Deplacement du bateau %c reussie\n", bateau_marque_get( tmp_bateau ) );
	#endif	
		
    }
    else
    {
	    #if !CLEARPRINT
    	printf ("[Amiral] Deplacement du bateau %c impossible\n", bateau_marque_get( tmp_bateau ) );
	    #endif
    }

	//On sauvegarde les nouvelles coordonées dans la liste de bateaux
	bateaux_save(bateaux, fich_bat);

        /////////
        // TIR //
        /////////

    /* Acquisition d'une cible (bateau différent de lui meme) */
    if( mer_bateau_cible_acquerir( fd_mer, bateaux_bateau_get(bateaux, indice), &acquisition, &cible ) == ERREUR )
    {
        printf ("[Amiral] Erreur durant l'acquisition d'une cible par le bateau %c\n", bateau_marque_get( tmp_bateau ) );
        exit(ERREUR);
    }

    if( acquisition == VRAI ) //Le bateau parvient a acquierir une cible
    {
	    #if DEBUG
            printf("--> Cible choisie par le bateau %c\n", bateau_marque_get( tmp_bateau ) );
            coord_afficher( stdout , cible );
            printf("\n");
	    #endif

        //On récupère l'indice de la victime
		indice_bateau_cible = bateaux_coord_seek(bateaux, cible);
        if( indice_bateau_cible == PAS_TROUVE)
        {
            printf ("[Amiral] Erreur durant la recuperation de l'indice du bateau vise par le bateau %c\n", bateau_marque_get( tmp_bateau ) );
            exit(ERREUR);
        }

		tmp_bateau_cible = bateaux_bateau_get(bateaux, indice_bateau_cible);
		bouclier=0;
		kill(bateau_pid_get(tmp_bateau_cible), SIG_BCL);
		
		sleep(1);
		
		if (bouclier){
			bouclier=0;
			// Tir d'un boulet sur la cible acquise
            if ((-1 == mer_bateau_cible_tirer(fd_mer, cible))){
                printf( "%s : erreur dans mer_bateau_cible_tirer pour le bateau %c\n", 
		    		Nom_Prog,  bateau_marque_get(tmp_bateau));
                exit(-1) ;
            }
			kill(bateau_pid_get(tmp_bateau_cible), SIG_COULE);
			mer_bateau_couler(fd_mer, tmp_bateau_cible);

			mer_nb_bateaux_lire(fd_mer, &nb_bateau);
			mer_nb_bateaux_ecrire(fd_mer, --nb_bateau);
        }
		
    }
    else //Pas de cible acquise
    {
	    #if DEBUG
                printf("--> Pas de cible acquise pour le bateau %c\n", bateau_marque_get( tmp_bateau ) );
	    #endif
    }

    //Affichage de la mer
    system ("clear");
    if( mer_afficher(fd_mer) == ERREUR )
    {
        printf ("[Amiral] Impossible d'afficher la mer\n");
        exit(ERREUR) ;
    }
	mer_nb_bateaux_lire(fd_mer, &nb_bateau);

        //On vérifie si le bateau est vainqueur
    if (bateaux_nb_get(bateaux) == 1  && nb_bateau == 1 && cumul_bateaux > 1)
    {
	    //Le bateau est vainqueur
        kill(siginfo->si_pid, SIG_WINNER); //On envoie le signal SIG_WINNER au processus qui gère le bateau

        printf("\n╔═══════════════╗\n");
        printf  ("║ Vainqueur : %c ║ \n" ,bateau_marque_get( tmp_bateau ) );
        printf  ("╚═══════════════╝\n\n");

        
        exit(CORRECT);
    }

    kill( siginfo->si_pid, SIG_NRJ);
}




/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
    int taille;
	pid_t pid;
	// Structure sigaction pour une demande de jeu
    struct sigaction action_jeu;

	// Structure sigaction pour la reception de la confirmation d'ecriture en MS d'un bateau
    struct sigaction action_infos;

    // Structure sigaction pour le signal SIGALRM de timeout
    struct sigaction action_sigalrm;

	// Structure sigaction pour le signal SIG_BCL
    struct sigaction action_bouclier;

	bateaux = bateaux_new();

     /*----------*/

     /* 
      * Capture des parametres 
      */

     if( nb_arg != 5 )
     {
	  fprintf( stderr , "Usage : %s <fichier mer> <fichier bateaux> <fichier amiral> <taille>\n", 
		   tab_arg[0] );
	  exit(-1);
     }

	strcpy( Nom_Prog , tab_arg[0] );
	strcpy( fich_mer , tab_arg[1] );
	strcpy( fich_bat , tab_arg[2] );
	strcpy( fich_ami , tab_arg[3] );
	taille = atoi( tab_arg[4] );

	if( bateaux_save( bateaux, fich_bat ) != 0 ){
        printf("Erreur durant l'écriture de la liste vide\n");
        exit(ERREUR);
    }

	action_jeu.sa_sigaction = hdl_jeu;
    action_jeu.sa_flags     = SA_SIGINFO; //Pour récupérer différentes informations dont le PID de l'expediteur du signal
    sigemptyset(&action_jeu.sa_mask);
    sigaddset(&action_jeu.sa_mask, SIG_INFOS); //On ignore un hypothétique signal SIG_INFOS reçu un peu tardivement
    // Application de la structure sigaction pour une demande de jeu
    if (sigaction(SIG_JEU, &action_jeu, NULL) < 0){
        perror ("Erreur concernant le signal SIG_JEU.");
        return 1;
    }

	// Renseignement des champs de la structure sigaction pour le signal SIGALRM
    action_sigalrm.sa_handler = hdl_sigalrm;
    action_sigalrm.sa_flags   = 0;
    // Application de la structure sigaction pour le signal SIGALRM
    if (sigaction(SIGALRM, &action_sigalrm, NULL) < 0){
        perror ("Erreur concernant le signal SIG_ALRM.");
        return 1;
    }


    // Renseignement des champs de la structure sigaction pour la confirmation d'écriture en MS d'un bateau
    action_infos.sa_handler = hdl_ecriture_ok;
    action_infos.sa_flags   = 0;
    // Application de la structure sigaction pour la confirmation d'écriture en MS d'un bateau
    if (sigaction(SIG_INFOS, &action_infos, NULL) < 0){
        perror ("Erreur concernant le signal SIG_INFOS.");
        return 1;
    }

	action_bouclier.sa_handler = hdl_bouclier;
    action_bouclier.sa_flags   = 0;
    // Application de la structure sigaction pour le signal SIG_BCL
    if (sigaction(SIG_BCL, &action_bouclier, NULL) < 0){
        perror ("Erreur concernant le signal SIG_BCL.");
        return 1;
    }

     /*
      * Affichage pid bateau amiral 
      */
     pid = getpid();

     printf(" PID bateau amiral = %d\n" , pid ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)pid);
 
	mer_initialiser(fich_mer, taille, taille);
     // Ouverture fichier mer
    if( ( fd_mer = open( fich_mer , O_RDWR , 0644 )) == -1 ){
        fprintf( stderr, "%s : Probleme durant l'ouverture sur %s\n", Nom_Prog , fich_mer);
        exit(-1);
    }

    printf("Mer ouverte... \n");


    // Initialisation de la liste des bateaux
    // bateau_fichier_initialiser(fich_bat);

    // Ecriture du PID de l'amiral dans la liste des bateaux
	if ( (fd_ami = open( fich_ami, O_WRONLY, 0644)) == -1){
		fprintf( stderr, "%s : Probleme durant l'ouverture sur %s\n", Nom_Prog , fich_ami);
        exit(-1);
    }
	if ( (write( fd_ami, &pid, sizeof(pid_t))) == -1){
		fprintf( stderr, "%s : Probleme durant l'écriture sur %s\n", Nom_Prog , fich_ami);
        exit(-1);
    }


    printf( "\n\n[Amiral] --> Amiral (%d) disponible\n", getpid() );

    //Attente permanante de signaux
    while(1)
        pause();

     printf("\n\n\t----- Fin du jeu -----\n\n");
     
     exit(0);
}

