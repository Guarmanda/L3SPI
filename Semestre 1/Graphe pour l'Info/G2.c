#include "G2.h"
#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"

/* TD
    S->b+ba

 TP
    S->X+B
    X->BA
    A->a
    B->b
*/

int bG2AmorceR;
char sMOT[TAILLE_MAX];

static int bMotConforme();
static int bS(const int iD, int *piF);
static int bX(const int iD, int *piF);
static int bA(const int iD, int *piF);
static int bB(const int iD, int *piF);

void G2AMORCER(){
    //Amorce le module
    bG2AmorceR=kV;
}

void G2Tester(int iTest){

    switch(iTest){
        case 1 : strcpy(sMOT,"b");printf("\nTest avec le mot %s",sMOT);break;
        case 2 : strcpy(sMOT,"ba");printf("\nTest avec le mot %s",sMOT);break;
        case 3 : strcpy(sMOT,"ab");printf("\nTest avec le mot %s",sMOT);break;
        case 4 : strcpy(sMOT,"bba");printf("\nTest avec le mot %s",sMOT);break;
        case 5 : strcpy(sMOT,"");printf("\nTest avec le mot %s",sMOT);
    }

    int bSucces=bMotConforme();

    bSucces ? printf("\n--Test Success-- "):printf("\n--Test  Failed--");

}

int bMotConforme(){
    int bConf, iF;

    bConf = bS(0,&iF) && strlen(sMOT)==iF;
    return bConf;
}

int bS(const int iD, int *piF){
    //S->X+B
    int bSucces, iM, iF;


    bSucces = bX(iD,&iF) || bB(iD,&iF) ;
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bX(const int iD, int *piF){
    //X->BA
    int bSucces, iM, iF;

    bSucces = bB(iD,&iM) && bA(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bA(const int iD, int *piF){
    //A->a
    int bSucces;

    bSucces = (sMOT[iD]=='a');

    *piF=iD+1;
    return bSucces;
}

int bB(const int iD, int *piF){
    //B->b
    int bSucces;

    bSucces = ( sMOT[iD]=='b');

    *piF=iD+1;
    return bSucces;
}