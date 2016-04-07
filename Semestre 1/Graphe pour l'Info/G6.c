#include "G6.h"
#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"

/*
   L6={m=a'b²',n>0,}

   TD
    S -> X + Y
    X -> aSbb
    Y -> abb

   TP
    S -> X + Y
    X -> A.S.B.B
    Y -> A.B.B

    A -> a
    B -> b

*/

int bG6AmorceR;
char sMOT[TAILLE_MAX];

static int bMotConforme();
static int bS(const int iD, int *piF);
static int bX(const int iD, int *piF);
static int bY(const int iD, int *piF);

static int bA(const int iD, int *piF);
static int bB(const int iD, int *piF);

void G6AMORCER(){
    //Amorce le module
    bG6AmorceR=kV;
}

void G6Tester(int iTest){
    switch(iTest){
        case 1 : strcpy(sMOT,"abb");printf("\nTest avec le mot %s",sMOT);break;
        case 2 : strcpy(sMOT,"aabbbb");printf("\nTest avec le mot %s",sMOT);break;
        case 3 : strcpy(sMOT,"aaabbbbbb");printf("\nTest avec le mot %s",sMOT);break;
        case 4 : strcpy(sMOT,"aaaabbbbbbbb");printf("\nTest avec le mot %s",sMOT);break;
        case 5 : strcpy(sMOT,"ab");printf("\nTest avec le mot %s",sMOT);
    }
    bMotConforme() ? printf("\n--Test Success-- "):printf("\n--Test  Failed--");
}

int bMotConforme(){
    int bConf, iF;

    bConf = bS(0,&iF) && strlen(sMOT)==iF;
    return bConf;
}

int bS(const int iD, int *piF){
    //S->X+Y
    int bSucces, iM, iF;

    bSucces = bX(iD,&iF) || bY(iD,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bX(const int iD, int *piF){
    //X-> A.S.B.B
    int bSucces, iM1, iM2, iM3, iF;

    bSucces = bA(iD,&iM1) && bS(iM1,&iM2) && bB(iM2,&iM3) && bB(iM3,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bY(const int iD, int *piF){
    //Y -> A.B.B
    int bSucces, iM1, iM2, iF;

    bSucces = bA(iD,&iM1) && bB(iM1,&iM2) && bB(iM2,&iF);
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