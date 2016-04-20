#include <com.h>
#include <proc.h>

#include <signal.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/wait.h>

/* ------------------------------ */
/* ----- long options array ----- */
/* ------------------------------ */

static struct option longopts[] =
{
  {"verbose", no_argument, NULL, (int)'v'},
  {"help", no_argument, NULL, (int)'h'},
  {0, 0, 0, 0}
};


/*
 * Usage 
 */
static 
void usage( char * nomprog )
{
  fprintf( stdout, " Programme de simulation d'un scheduller avec Tourniquet\n" );
  fprintf( stdout , " usage : %s [options] <fichier liste des commandes> <quantum de temps (microsecondes)> \n" , nomprog );
  fprintf( stdout , "Options:\n"); 
  fprintf( stdout , "  -v, --verbose                 trace de l'execution acitvee\n");
  fprintf( stdout , "  -h, --help                    affiche cette aide\n");
}


int
main( int argc , char * argv[] ) 
{
  /* --- Variables --- */
  err_t cr = OK ;
  char nomprog[MAX_STRING] ; 

  /* Processus */
  proc_t * liste_proc_prets = NULL ; 
  useconds_t quantum = 0 ; 

  /* Commandes */
  char ListeCommandes[MAX_STRING] ; /* Nom du fichier des commandes */ 
  char *** commandes = NULL ; /* Liste des commandes */
  int nb_commandes = 0 ; 

  /* Options */
  int opt ;
  booleen_t verbose = FAUX ; 

  /* --- Gestion parametres + options --- */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vh", longopts, NULL)) != -1 )
    {
      switch(opt)
	{
	case 'v': /* --verbose */
	  printf("verbose\n");
	  verbose = VRAI ;
	  break;
	  
	case 'h': /* --help */
	  usage(nomprog) ;
	  exit(0);
	  break;

	case '?':
	  usage(nomprog) ;
	  exit(0);
	  break;

	default:
	  usage(nomprog) ;
	  exit(0);
	  break;
	}
    }
  argc -= optind ;
  argv += optind ;

  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */ 


  if( argc != 2 ) 
    {
      usage(nomprog) ; 
      exit(0); 
    }

  
  strcpy( ListeCommandes , argv[0] ) ;
  quantum = atoi(argv[1]) ; 

  /* --- Programme --- */
  printf("\n\n\n\t===========Debut %s==========\n\n" , nomprog );

  /* 
   * Chargement des commandes 
   */
  if( ( cr = com_fichier_charger( &commandes , /* tableau commandes a remplir */
				  &nb_commandes , 
				  ListeCommandes ) ) )
    {
      printf( "Pb sur chargement liste de commandes, cr = %d\n" , cr ) ; 
      exit(-1) ; 
    }

  if( verbose ) 
    com_liste_afficher(commandes ,  nb_commandes )  ; 


  /* 
   * Lancement des processus 
   */

  /* Reservation memoire tableau des pid */
  liste_proc_prets = malloc( sizeof(proc_t) * nb_commandes ) ;

    int pid = 0;
    int pidRecv = 0;
    int i = 0;
    int cmdNum = 0;
    
    //Lance les commandes et les stop directement
    for(i = 0 ; i < nb_commandes ; i++){
        switch(pid = fork()){
          case -1:
             printf("ERREUR pour le fork\n");
             exit(-1);
             
          case 0: //Le fils lance la commande qui lui correspond
             if( execv(commandes[i][0], commandes[i]) < 0)
                 printf("\nErreur lors du lancement de %s\n", commandes[i][0]);
             exit(0);
             
          default: //Le père stop le fils, inscrit sont pid dans la liste des processus prêt et le marque à non fini
             kill(pid, SIGSTOP);
             proc_pid_ecrire(&liste_proc_prets[i] , pid );
             proc_fini_faux(&liste_proc_prets[i]);
      }
     }
    
    if(verbose){
        printf("\nÉtat des processus au début de l'odonnaceur : \n");
        proc_liste_afficher(liste_proc_prets, nb_commandes);
        printf("\n");
     }

  /* 
   * Gestion des processus
   */

    i = -1;
    pidRecv = pid;
    int fini = 1;
    struct timeval temps, tempsCmd, tempsDebut, tempsFin;
    
    timerclear(&tempsCmd);
    
    //Enregistre le temps de début
    gettimeofday(&tempsDebut, NULL);
    
    //Boucle tant qu'il y a des processus en cours
    while(!proc_liste_sont_finis(liste_proc_prets, nb_commandes)){
        //Récupére le temps actuel
        gettimeofday(&temps, NULL);
        timersub(&temps, &tempsCmd, &temps);
        
        //Vérifie que le tant d'activité du processus ne dépasse pas le quantum ou que le processus soit fini
        if( ((temps.tv_sec * 1000000) + temps.tv_usec) > quantum || fini){
            //Stop le processus
            kill(pid, SIGSTOP);
            pidRecv = pid;
            
            //Cherche le prochain processus encore en cours
            while(pid == pidRecv && !proc_liste_sont_finis(liste_proc_prets, nb_commandes)){
                i = (i + 1)%nb_commandes;
                
                //Si le processus est encore en cours
                if(!proc_est_fini(liste_proc_prets[i])){
                    //Récupére son PID
                    pid = proc_pid_lire(liste_proc_prets[i]);
                    pidRecv = 0;
                    
                    //Redémarre le processus
                    kill(pid, SIGCONT);
                    
                    //Enregistre son temps de lancement
                    gettimeofday(&tempsCmd, NULL);
                    fini = 0;
                 }
             }
         }
        else{
            //Vérifie si le processus c'est terminé
            pidRecv = waitpid(-1, NULL, WNOHANG);
            
            //Si le processus c'est terminé
            if(proc_liste_rechercher(liste_proc_prets, nb_commandes, pidRecv, &cmdNum)){
                
#ifdef _DEBUG_
                printf("\nFils de pid %d terminé.\n", pidRecv);
#endif
                //Marque le processus comme fini
                proc_fini_vrai(&liste_proc_prets[cmdNum]);
                fini = 1;
             }
         }
     }
    
    gettimeofday(&tempsFin, NULL);
    timersub(&tempsFin, &tempsDebut, &tempsFin);
    
    if(verbose){
        printf("\n\nÉtat des processus à la fin de l'odonnaceur : \n");
        proc_liste_afficher(liste_proc_prets, nb_commandes);
        
     }
    
    printf("\n%s executé en %lf secondes\n", nomprog, (tempsFin.tv_sec + (tempsFin.tv_usec/1000000.0)));

  printf("\n\n\t===========Fin %s==========\n\n" , nomprog );
 
 return(0) ;
}

