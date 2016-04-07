#include "G13.h"
#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"

/*
   L13={m E A*, m=b'a'b* , m C b3a3b3 , n>0}

   TD
    m = b3 a3 b3 (1+b+) = b3.a3.b2.b+

    S -> T.U.V.W

    T -> b.b.b

    U -> a.a.a

    V -> b.b

    W -> X+b
    X -> b.W


   TP
    S -> Z.R

    Z -> T.U
    R -> V.W

    T -> V.B
    V -> B.B

    U -> Y.A
    Y -> A.A

    W -> X+B
    X -> B.W


    A->a
    B->b

*/

int bG13AmorceR;
char sMOT[TAILLE_MAX];
/*
int bX(const int iD, int *piF){
    //X -> B.W
    int bSucces, iM, iF;
    bSucces = bB(iD,&iM) && bW(iM,&iF);
    *piF = (bSucces) ? iF:iD;
    return bSucces;
}
int bW(const int iD, int *piF){
    //W -> X+B
    int bSucces, iF;
    bSucces = bX(iD,&iF) || bB(iD,&iF);
    return bSucces;
}
*/
static int bMotConforme();
static int bS(const int iD, int *piF);
static int bZ(const int iD, int *piF);
static int bR(const int iD, int *piF);
static int bT(const int iD, int *piF);
static int bV(const int iD, int *piF);
static int bU(const int iD, int *piF);
static int bY(const int iD, int *piF);
static int bW(const int iD, int *piF);
static int bX(const int iD, int *piF);

static int bA(const int iD, int *piF);
static int bB(const int iD, int *piF);

void G13AMORCER(){
    //Amorce le module
    bG13AmorceR=kV;
}
int bMotConforme(){
    int bConf, iF;

    bConf = bS(0,&iF) && strlen(sMOT)==iF;
    return bConf;
}

void G13Tester(int iTest){
    switch(iTest){
        case 1 : strcpy(sMOT,"abbbaaabbb");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 2 : strcpy(sMOT,"bbbbaaaabbb");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 3 : strcpy(sMOT,"bbbaaabbb");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 4 : strcpy(sMOT,"bbbaaabbbbb");printf("\n# Test avec le mot \"%s\"\n#",sMOT);break;
        case 5 : strcpy(sMOT,"babb");printf("\n# Test avec le mot \"%s\"\n#",sMOT);
    }
    bMotConforme() ? printf("\n#\t----Test Success----\n#") : printf("\n#\t----Test  Failed----\n#");
}

int bX(const int iD, int *piF){
    //X -> B.W
    int bSucces, iM, iF;

    bSucces = bB(iD,&iM) && bW(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bW(const int iD, int *piF){
    //W -> X+B
    int bSucces, iF;

    bSucces = bX(iD,&iF) || bB(iD,&iF);

    return bSucces;
}

int bY(const int iD, int *piF){
    //Y -> A.A
    int bSucces, iM, iF;

    bSucces = bA(iD,&iM) && bA(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bU(const int iD, int *piF){
    //U -> Y.A
    int bSucces, iM, iF;

    bSucces = bY(iD,&iM) && bA(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bV(const int iD, int *piF){
    //V -> B.B
    int bSucces, iM, iF;

    bSucces = bB(iD,&iM) && bB(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bT(const int iD, int *piF){
    //T -> V.B
    int bSucces, iM, iF;

    bSucces = bV(iD,&iM) && bB(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bR(const int iD, int *piF){
    //R -> V.W
    int bSucces, iM, iF;

    bSucces = bV(iD,&iM) && bW(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bZ(const int iD, int *piF){
    //Z -> T.U
    int bSucces, iM, iF;

    bSucces = bT(iD,&iM) && bU(iM,&iF);
    *piF = (bSucces) ? iF:iD;

    return bSucces;
}

int bS(const int iD, int *piF){
    //S -> Z.R
    int bSucces, iM, iF;

    bSucces = bZ(iD,&iM) && bR(iM,&iF);
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