#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <unistd.h>

#include "messages.h"

#define ERROR -1
#define SUCCESS 0


int main(int argc, char **argv){
    
    /* Variables */
    int cle_externe, id_file;
    
    /* Variables de message */
    requete_t requete;
    reponse_t reponse;
    
    
    /* Validation du nombre d'argument */
    if( argc!=2 ){
        printf("\tUsage : ./%s <cle_externe> \n\n",argv[0]);
        exit(ERROR);
    }
    
    /* Récupération de la clé et validation */
    cle_externe = atoi(argv[1]);
    if( cle_externe<= 0 ){
        printf("\tErreur : argument <cle_externe> invalide.\n");
        exit(ERROR);
    }
    
    /* Recherche de la file de messages */
    if( (id_file = msgget( cle_externe, 0 )) == ERROR ){
        perror("Probleme durant la recherche de la file de messages.\n");
        exit(ERROR);
    }
    
    /* Message de demande */
    requete.corps.dossard = getpid();
    requete.type = PC_COURSE;
    
    /* Initialisation de l'attente */
    messages_initialiser_attente();
    
    
    /* le coureur continue tant qu'il n'est ni décanillé ni gagnant */
    while( reponse.corps.etat == EN_COURSE ){
        
        printf("Envoi de la requête...\n");
        
        /* Envoi d'une requete au PC pour signaler une demande d'avancement */
        if( msgsnd( id_file, &requete, sizeof(corps_requete_t), 0) == ERROR ){
            perror("Erreur lors de l'envoi de la requete.\n");
            exit(ERROR);
        }
        
        printf("Attente de la réponse...\n");
        
        /* Recupération de la réponse du PC à la requête */
        if( msgrcv( id_file, &reponse, sizeof(reponse), requete.corps.dossard, 0) == ERROR ){
            perror("Erreur lors de la reception de la réponse.\n");
            exit(ERROR);
        }
        
        /* Affichage de la réponse */
        messages_afficher_reponse( &reponse );
        messages_afficher_parcours( &reponse );
        
        if( reponse.corps.etat == ARRIVE ){
            printf("----  ARRIVE ----\n");
            exit(SUCCESS);
        }
        else if( reponse.corps.etat == DECANILLE ){
            printf("----DECANILLE----\n");
            exit(SUCCESS);
        }
        
        /* Attente entre 2 envois de message vers le PC Course */
        messages_attendre_tour();
        
    }
    
    exit(SUCCESS);
}


