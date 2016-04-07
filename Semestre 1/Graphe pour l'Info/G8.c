#include "G8.h"
#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"

/*
   L8={m=a'b'a+,n>0}

   TD
    S->X.Y
    X->a.X.b + a.b
    Y->a.Y + a

   TP
    S->W.V
    V->Z+A
    W->X+Y
    X->A.W.B
    Y->A.B
    Z->A.V

    A->a
    B->b

*/

int bG8AmorceR;
char sMOT[TAILLE_MAX];

static int bMotConforme();
static int bS(const int iD, int *piF);
static int bV(const int iD, int *piF);
static int bW(const int iD, int *piF);
static int bX(const int iD, int *piF);
static int bY(const int iD, int *piF);
static int bZ(const int iD, int *piF);

static int bA(const int iD, int *piF);
static int bB(const int iD, int *piF);

void G8AMORCER(){
    //Amorce le module
    bG8AmorceR=kV;
}

void G8Tester(int iTest){
    switch(iTest){
        case 1 : strcpy(sMOT,"abaaa");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 2 : strcpy(sMOT,"ab");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 3 : strcpy(sMOT,"aaabbba");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 4 : strcpy(sMOT,"aaa");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 5 : strcpy(sMOT,"abab");printf("\n# Test avec le mot \"%s\"\n#",sMOT);
    }
    bMotConforme() ? printf("\n#\t----Test Success----\n#"):printf("\n#\t----Test  Failed----\n#");
}

int bMotConforme(){
    int bConf, iF;

    bConf = bS(0,&iF) && strlen(sMOT)==iF;
    return bConf;
}


int bS(const int iD, int *piF){
    //S->W.V
    int bSucces, iM, iF;

    bSucces = bW(iD,&iM) && bV(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bV(const int iD, int *piF){
    //V->Z+A
    int bSucces, iF;

    bSucces = bZ(iD,&iF) || bA(iD,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bW(const int iD, int *piF){
    //W->X+Y
    int bSucces, iF;

    bSucces = bX(iD,&iF) || bY(iD,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bX(const int iD, int *piF){
    //X->A.W.B
    int bSucces, iM1, iM2, iF;

    bSucces = bA(iD,&iM1) && bW(iM1,&iM2) && bB(iM2,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bY(const int iD, int *piF){
    //Y->A.B
    int bSucces, iM, iF;

    bSucces = bA(iD,&iM) && bB(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bZ(const int iD, int *piF){
    //Z->A.V
    int bSucces, iM, iF;

    bSucces = bA(iD,&iM) && bV(iM,&iF);
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