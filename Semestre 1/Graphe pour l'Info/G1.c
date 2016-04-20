#include "G1.h"
#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"

/* TD
    S->ab
 
   TP
    S->A.B
    A->a
    B->b
*/

int bG1AmorceR;
char sMOT[TAILLE_MAX];

int bMotConforme();
int bS(const int iD, int *piF);
int bA(const int iD, int *piF);
int bB(const int iD, int *piF);

void G1AMORCER(){
    //Amorce le module
    bG1AmorceR=kV;
}

void G1Tester(int iTest){
    
    switch(iTest){
        case 1 : strcpy(sMOT,"AB");printf("\nTest avec le mot %s",sMOT);break;
        case 2 : strcpy(sMOT,"ab");printf("\nTest avec le mot %s",sMOT);break;
        case 3 : strcpy(sMOT,"ba");printf("\nTest avec le mot %s",sMOT);break;
        case 4 : strcpy(sMOT,"BA");printf("\nTest avec le mot %s",sMOT);
    }
    
    bMotConforme() ? printf("\n--Test Success-- "):printf("\n--Test  Failed--");

}

int bMotConforme(){
    int bConf, iF;
    
    bConf = bS(0,&iF) && strlen(sMOT)==iF;
    return bConf;
}

int bS(const int iD, int *piF){
    //S->AB
    int bSucces, iM, iF;
    
    bSucces = bA(iD,&iM) && bB(iM,&iF);
    *piF = (bSucces) ? iF:iD;
    
    return bSucces;
}

int bA(const int iD, int *iF){
    //A->a
    int bSucces;
    
    bSucces = (sMOT[iD]=='a');
    
    *iF=iD+1;
    return bSucces;
}

int bB(const int iD, int *iF){
    //B->b
    int bSucces;
    
    bSucces = ( sMOT[iD]=='b');
    
    *iF=iD+1;
    return bSucces;
}


