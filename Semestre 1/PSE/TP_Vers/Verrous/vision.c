#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#include <commun.h>
#include <terrain.h>


/*--------------------*
 * Main demon
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
     int fd_terrain ;
     char fich_terrain[128] ;
     char mess[256];
     char nomprog[256] ;
    int nb_lig;
    int nb_col;

	 struct stat info_fichier_terrain; // structure
     time_t date_derniere_modif;    //date de la dernière modification


     if( nb_arg != 4 )
     {
	  fprintf( stderr , "Usage : %s <fichier terrain> <ligne> <colone>\n",
		   tab_arg[0] );
	  exit(-1);
     }

     strcpy( nomprog , tab_arg[0] );
     strcpy( fich_terrain , tab_arg[1] );
    nb_lig=atoi(tab_arg[2]);
    nb_col=atoi(tab_arg[3]);

    terrain_initialiser(fich_terrain, nb_lig, nb_col);
    
	 /* Ouverture du ficher terrain */
	 if((fd_terrain=open(fich_terrain,O_RDONLY,0666))==-1){
		 fprintf(stderr, "%s : Probleme durant l'ouverture du fichier %s.\n",
			nomprog, fich_terrain);
		 exit(-1);
	 }
	 printf("Terrain ouvert\n");
    
    
    /* RŽcupŽration de la date de dernière modification */

    stat (fich_terrain,&info_fichier_terrain);
    date_derniere_modif = info_fichier_terrain.st_ctime;
    
    system ("clear"); //fait un "clear" du terminal
    printf("Affichage du terrain: \n");
    terrain_afficher(fd_terrain);

    /* Boucle infinie affichant le terrain ˆ chaque changement */
    while(1){

        stat (fich_terrain,&info_fichier_terrain);

        
        //Si la date est différente de celle précedement "sauvegardee" dans date_derniere_modif,
        //on la "sauvegarde" (on actualise date_derniere_modif) et on affiche le terrain.
        if(date_derniere_modif != info_fichier_terrain.st_ctime){
            date_derniere_modif = info_fichier_terrain.st_ctime;

            system ("clear"); //fait un "clear" du terminal
            printf("Affichage du terrain: \n");
            terrain_afficher(fd_terrain);


        }
    }

     printf("\n%s : --- Arret de l'affichage du terrain ---\n", nomprog );

     exit(0);
}
