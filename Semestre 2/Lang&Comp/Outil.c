#include "Outil.h"

#define kuAntiSlashZerO 1 //encombrement du caractère "\0" qui délimite les chaînes de caractères
#define kcEchappemenT1 -61
#define kcEchappemenT2 -59
#define knEcrisMaX 63
#define kuOctetGererMaX  kuByteMax
#define kuWhileMaX 5 //nb max de while imbriqués (si des appels récursifs imbriquent un grand nombre de while, augmenter sensiblement cette valeur)
//constantes et variables:
int bEcriS[1+knEcrisMaX];//dédié routines s0,s1
int nEcriS=0;//initialisation vitale ici car OutilAmorcer n'a pas encore été appelé à l'appel de s0() en tête de main();pour s0() et s1()
int ipWhilE=0;//index de pile dédié While() et bWhile()
long zWhilE[1+kuWhileMaX];
int nOctetGereR0;
long yOctetGereR0[1+kuOctetGererMaX];
int nOctetGereR1;
long yOctetGereR1[1+kuOctetGererMaX];
int zuOctetGereR;
int bOutilAmorceR;//ie le module a bien été amorcé
const int knStopFlipFloP=7;//dédié routine FlipFlop()
//prototypes des routines privées (ie non publiques dc hors .h):
void assert2(int bAssertion1,int bAssertion2);//vérifie que bAssertion1 et bAssertion2 sont vrais
void assert3(int bAssertion1,int bAssertion2,int bAssertion3);
void assert4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void assert5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void assert6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT0(char *sContexte,int bAssertion,int nParametre);
int bConsonnE2(char *sString,int *pnCodeCaractereRg);
int bLettrE2(char *sString,int *pnCodeCaractereRg);
void OctetGereR(char *sMalloc);
int bVoyellE2(char *sString,int *pnCodeCaractereRg);

void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	int bAssertion=bAssertion1 && bAssertion2 && bAssertion3 && bAssertion4 && bAssertion5 && bAssertion6;
	if (!bAssertion){
		AsserT0(sContexte,bAssertion1,1);
		AsserT0(sContexte,bAssertion2,2);
		AsserT0(sContexte,bAssertion3,3);
		AsserT0(sContexte,bAssertion4,4);
		AsserT0(sContexte,bAssertion5,5);
		AsserT0(sContexte,bAssertion6,6);
	}
	assert(bAssertion);
}//AsserT

void AsserT0(char *sContexte,int bAssertion,int nParametre){
	if (!bAssertion){
		printf("    *** Assertion fausse (paramètre n°%d)",nParametre);
		if (strlen(sContexte)>0)
			printf(" dans \"%s\" %d",sContexte,nParametre);
		printf(".\n");
	}
}//AsserT0

void assert2(int bAssertion1,int bAssertion2){
	AsserT("",bAssertion1,bAssertion2,kV,kV,kV,kV);
}//assert2

void assert3(int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//assert3

void assert4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//assert4

void assert5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//assert5

void assert6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT("",bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//assert6

void Assert1(char *sContexte,int bAssertion1){
	AsserT(sContexte,bAssertion1,kV,kV,kV,kV,kV);
}//Assert1

void Assert2(char *sContexte,int bAssertion1,int bAssertion2){
	AsserT(sContexte,bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert2

void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//Assert3

void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//Assert4

void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//Assert5

void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Assert6

void b(int bBooleen){
	printf("%s\n",(bBooleen!=0)?"vrai":"faux");
}//b

void i(long yEntier1){
	printf("%ld.\n",yEntier1);
}//i

void ii(long yEntier1,long yEntier2){
	printf("%ld, %ld.\n",yEntier1,yEntier2);
}//ii

void iii(long yEntier1,long yEntier2,long yEntier3){
	printf("%ld, %ld, %ld.\n",yEntier1,yEntier2,yEntier3);
}//iii

void s(char *sString){
	assert(sString!=0);
	printf("%s.\n",sString);
}//s

void sb(char *sString,int bBooleen){
	printf("%s:%s.\n",sString,(bBooleen!=0)?"vrai":"faux");
}//sb

void si(char *sString,long yEntier1){
	printf("%s:%ld.\n",sString,yEntier1);
}//si

void sii(char *sString,long yEntier1,long yEntier2){
	printf("%s:%ld, %ld.\n",sString,yEntier1,yEntier2);
}//sii

void siii(char *sString,long yEntier1,long yEntier2,long yEntier3){
	printf("%s:%ld, %ld, %ld.\n",sString,yEntier1,yEntier2,yEntier3);
}//siii

void siiii(char *sString,long yEntier1,long yEntier2,long yEntier3,long yEntier4){
	printf("%s:%ld, %ld, %ld, %ld\n",sString,yEntier1,yEntier2,yEntier3,yEntier4);
}//siiii

void sr(char *sString,double dReel1){
	printf("%s:%lf.\n",sString,dReel1);
}//sr

void srr(char *sString,double dReel1,double dReel2){
	printf("%s:%lf, %lf.\n",sString,dReel1,dReel2);
}//srr

void srrr(char *sString,double dReel1,double dReel2,double dReel3){
	printf("%s:%lf, %lf, %lf.\n",sString,dReel1,dReel2,dReel3);
}//srrr

void ss(char *sString1,char *sString2){
	Vrai2(sString1!=0,sString2!=0);
	printf("%s, %s.\n",sString1,sString2);
}//ss

void sss(char *sString1,char *sString2,char *sString3){
	Vrai3(sString1!=0,sString2!=0,sString3!=0);
	printf("%s, %s, %s.\n",sString1,sString2,sString3);
}//sss

void ssss(char *sString1,char *sString2,char *sString3,char *sString4){
	Vrai4(sString1!=0,sString2!=0,sString3!=0,sString4!=0);
	printf("%s, %s, %s, %s.\n",sString1,sString2,sString3,sString4);
}//ssss

void sssss(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5){
	Vrai5(sString1!=0,sString2!=0,sString3!=0,sString4!=0,sString5!=0);
	printf("%s, %s, %s, %s, %s.\n",sString1,sString2,sString3,sString4,sString5);
}//sssss

long zAbs(long yEntier){
	//rend la valeur absolue positive ou déroute si yEntier est trop négatif;cache la fonction labs
	long zAbs;
	Assert1("zAbs",yEntier!=kyLongintMin);
	zAbs=labs(yEntier);//>=0 ssi yEntier!=kyLongintMin
	return(zAbs);
}//zAbs

void Appel0(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme en cours...". Puis passe à la ligne. Vérifie le parenthésage des appels.
	Vrai2(sMessage!=0,nEcriS<knEcrisMaX);
	FlipFlop(1,&bEcriS[++nEcriS]);
	if (strlen(sMessage)==0){
		printf("Programme en cours...\n");
	} else printf("%s%s: tâche en cours...\n",sE(2*nEcriS),sMessage);
}//Appel0

void Appel1(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme terminé.". Puis passe à la ligne. Vérifie le parenthésage des appels.
	int nMessageLg=strlen(sMessage);
	Vrai2(sMessage!=0,nEcriS>0);
	FlipFlop(0,&bEcriS[nEcriS]);
	if (nMessageLg)
		printf("%s%s: tâche terminée.\n",sE(2*nEcriS),sMessage);
	else printf("Programme terminé.\n");
	nEcriS--;
	assert(nEcriS>=0);
	if (!nMessageLg){
		assert(nEcriS==0);//ie s0 et s1 sont correctt parenthésés
		assert(ipWhilE>=0);//si ok,il a bien été ajouté 1° un appel à While() avant chaque boucle while et 2° un appel à bWhile() dans ladite boucle
	}
}//Appel1

int bBit(char cCaractere){
	int bBit=(cCaractere=='0') || (cCaractere=='1');
	assert(bBit==0 || bBit==1);
	return(bBit);
}//bBit

int bBool(long yEntier){
	int bBool=(yEntier==0) || (yEntier==1);
	assert(bBool==0 || bBool==1);
	return(bBool);
}//bBool

char *sBool(long yValeur){
	//rend en clair la valeur booléenne de yValeur
	if (yValeur)
		return("vrai");
	else return("faux");
}//sBool

int bByte(long yEntier){
	int bByte=bCroit(0,yEntier,kuByteMax);
	return(bByte);
}//bByte

char *sC(char cAlphaNumeriqueOuEspace){
	//convertit cA en string;cA est censé être un caractère alphanumérique (donc non accentué) ou un espace
	char *sAccu=malloc(1+kuAntiSlashZerO);
	char sMotif[2];
	assert(isalnum(cAlphaNumeriqueOuEspace) || isspace(cAlphaNumeriqueOuEspace));//isspace: espace,saut de page,fin de ligne,retour chariot,tabulation.
	sMotif[0]=cAlphaNumeriqueOuEspace;
	sMotif[1]='\0';
	strcpy(sAccu,sMotif);
	OctetGereR(sAccu);
	return(sAccu);
}//sC

char *sC1(char *sA){
	//rend sA après avoir vérifié que son pointeur n'est pas nul
	assert(sA!=0);
	return(sA);
}//sC1

char *sC1p(char *sA){
	//concatène sA et "."
	assert(sA!=0);
	char *sAccu=sC2(sA, ".");
	return(sAccu);
}//sC1p

char *sC2(char *sA,char *sB){
	//concatène sA et sB
	int uRequis;
	Vrai2(sA!=0,sB!=0);
	uRequis=1+strlen(sA)+strlen(sB);
	char *sAccu=malloc(uRequis+kuAntiSlashZerO);
	strcpy(sAccu,sA);
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2

char *sC2b(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bBlancEnSus,nRequis;
	char *sAccu;
	Vrai2(sA!=0,sB!=0);
	nRequis=strlen(sA)+strlen(sB);
	assert(nRequis>=0);
	bBlancEnSus=(strlen(sA)>0) && (strlen(sB)>0);
	if (bBlancEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par strlen...Le 4 minimise les dégâts
	strcpy(sAccu,sA);
	if (bBlancEnSus)
		strcat(sAccu," ");
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2b

char *sC2bp(char *sA,char *sB){
	//concatène sA,sB et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC2b(sA,sB),".");//sC2b vérifie que sA et sB sont définis
	return(sAccu);
}//sC3bp

char *sC2p(char *sA,char *sB){
	//concatène sA,sB et "."
	char *sAccu=sC2(sC2(sA, sB),".");//sC2 vérifie que sA et sB sont définis
	return(sAccu);
}//sC2p

char *sC2v(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bVirguleEnSus,nRequis;
	char *sAccu;
	Vrai2(sA!=0,sB!=0);
	nRequis=strlen(sA)+strlen(sB);
	assert(nRequis>=0);
	bVirguleEnSus=(strlen(sA)>0) && (strlen(sB)>0);
	if (bVirguleEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par strlen...Le 4 minimise les dégâts
	strcpy(sAccu,sA);
	if (bVirguleEnSus)
		strcat(sAccu,",");
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2v

char *sC3(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC
	char *sAccu=sC2(sC2(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3

char *sC3b(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC2b(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3b

char *sC3bp(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC3b(sA,sB,sC),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3bp

char *sC3p(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "."
	char *sAccu=sC4(sA,sB,sC, ".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3p

char *sC3v(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3v

char *sC4(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD
	char *sAccu=sC2(sC3(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4

char *sC4b(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC3b(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4b

char *sC4bp(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4bp

char *sC4p(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "."
	char *sAccu=sC2(sC4(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4p

char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE
	char *sAccu=sC2(sC4(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5

char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5b

char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC5b(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5bp

char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5p

char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6

char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC5b(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6b

char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC6b(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6bp

char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6p

char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7

char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC6b(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7b

char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC7b(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7bp

char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "."
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7p

char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8

char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC7b(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8b

char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8bp

char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "."
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8p

int nCaractere(char *sString){
	//rend le nombre de caractères de sString (et non pas le nombre de codes caractères,contrairt à strlen() qui renvoie 2 pour un seul "à")
	int nC=0;//index sur le code caractère courant de sString
	int nCaractere=0;
	int nChaineLg;
	char cCode;
	assert(sString!=0);
	for (nChaineLg=strlen(sString),nC=0;nC<nChaineLg;nC++){
		cCode=sString[nC];
		if ( isalpha(cCode) || isdigit(cCode) || bLettrE2(sString,&nC) ) //dernier terme: voyelle ou consonne avec un signe diacritique
			nCaractere++;
	}
	assert(nCaractere>=0);
	return(nCaractere);
}//nCaractere

int nChainePos(char cQuoi,char *sDansQuoi){
	//rend le rang0 de cQuoi dans sDansQuoi, ou -1 si échec
	int nC;
	int nPos=-1;
	for (nC=0; nC<strlen(sDansQuoi) && (nPos<0); nC++)
		if (cQuoi==sDansQuoi[nC])
			nPos=nC;
	return(nPos);
}//nChainePos

int bChiffre(char cCaractere){
	//cCaractere est un chiffre décimal
	int bChiffre=bDecit(cCaractere);
	return(bChiffre);
}//bChiffre

char *sChoix0(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide.
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? strlen(sOption) : 0;
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	if (bOption)
		strcpy(sCopie,sOption);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix0

char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative){
	//rend sOption si bOptionSinonAlternative est vrai; sinon,rend sAlternative.
	int nRequis;
	Vrai2(sOption!=0,sAlternative!=0);
	nRequis = bOptionSinonAlternative? strlen(sOption) : strlen(sAlternative);
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	if (bOptionSinonAlternative)
		strcpy(sCopie,sOption);
	else strcpy(sCopie,sAlternative);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix

void Confirmer(char *sMessage){
	char cCar;
	printf("%s Valider SVP (touche entrée)",sMessage);
	scanf("%c",&cCar);
	printf(" Merci d'avoir validé.\n");
}//Confirmer

int bConsonnE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knConsonne1LiM 21
    #define knConsonne2LiM 04
	int nConsonne1[knConsonne1LiM]={64,65,66,67,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,89};//consonnes sans signe diacritique
	int nConsonne2[knConsonne2LiM]={79,89,111,121};//ççÑñ";
	int bConsonne2=0;
	Vrai2(sString!=0,pnCodeCaractereRg!=0);
	Croit(0,2,strlen(sString));
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bConsonne2=isalpha(cCode);//consonne ou voyelle sans signe diacritique (accents,cédille,tilde...)
	if (bConsonne2){//consonne?
		assert(0);//ie code actuellt non exécuté vu le contexte des appels à bConsonnE2()
		for (bConsonne2=0,nCar=0; nCar<knConsonne1LiM; nCar++)
			bConsonne2=bConsonne2||(cCode==-nConsonne1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sString)) {//l'accès à sString[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knConsonne2LiM; nCar++)
				bConsonne2=bConsonne2||(cCode==-nConsonne2[nCar]);
			if (bConsonne2)
				(*pnCodeCaractereRg)++;
		}
	}
	return(bConsonne2);
}//bConsonnE2

char *sCouple(long yEntierA,long yEntierB){
	//rend la chaîne (yEntierA,yEntierB)	
	char *sCouple=sP(sC3(sEntier(yEntierA),",",sEntier(yEntierB)));
	OctetGereR(sCouple);
	return(sCouple);
}//sCouple

void Croissant(double dMinInclus,double dDedans,double dMaxInclus){
	if (!bCroissant(dMinInclus,dDedans,dMaxInclus))
		printf("BUG ds bCroissant():%lf≤%lf≤%lf est FAUX\n",dMinInclus,dDedans,dMaxInclus);
	assert(bCroissant(dMinInclus,dDedans,dMaxInclus));
}//Croissant

int bCroissant(double dMinInclus,double dDedans,double dMaxInclus){
	int bCroissant=(dMinInclus<=dDedans) && (dDedans<=dMaxInclus);
	return(bCroissant);
}//bCroissant

int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	int bCroissantStrict=(dMinExclu<dDedans) && (dDedans<dMaxExclu);
	return(bCroissantStrict);
}//bCroissantStrict

void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	if (!bCroissantStrict(dMinExclu,dDedans,dMaxExclu))
		printf("BUG ds bCroissantStrict():%lf<%lf<%lf est FAUX\n",dMinExclu,dDedans,dMaxExclu);
	assert(bCroissantStrict(dMinExclu,dDedans,dMaxExclu));
}//CroissantStrict

void Croit(long yMinInclus,long yDedans,long yMaxInclus){
	if (!bCroit(yMinInclus,yDedans,yMaxInclus))
		printf("BUG ds bCroit():%ld≤%ld≤%ld est FAUX\n",yMinInclus,yDedans,yMaxInclus);
	assert(bCroit(yMinInclus,yDedans,yMaxInclus));
}//bCroit

int bCroit(long yMinInclus,long yDedans,long yMaxInclus){
	int bCroit=(yMinInclus<=yDedans) && (yDedans<=yMaxInclus);
	return(bCroit);
}//bCroit

int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu){
	int bCroitStrict=(yMinExclu<yDedans) && (yDedans<yMaxExclu);
	return(bCroitStrict);
}//bCroit

void CroitStrict(long yMinExclu,long yDedans,long yMaxExclu){
	if (!bCroitStrict(yMinExclu,yDedans,yMaxExclu))
		printf("BUG ds bCroitStrict():%ld<%ld<%ld est FAUX\n",yMinExclu,yDedans,yMaxExclu);
	assert(bCroitStrict(yMinExclu,yDedans,yMaxExclu));
}//CroitStrict

int bDecit(char cCaractere){
	//cCaractere est un chiffre décimal;cache la fonction isdigit()
	int bDecit=isdigit(cCaractere);
	return(bDecit);
}//bDecit

void Dis(char *sString){//affiche la valeur de la chaîne et ajoute un point final.
	s(sC2(sString,"."));
}//Dis

char *sE(int nEspace){
	//nEspace blancs juxtaposés
	char *sE=sFois(nEspace,' ');
	return(sE);
}//sE

char *sEntier(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntier

char *sEntier2(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier2=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier2,"%2ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier2);
}//sEntier2

char *sEntier3(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier3=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier3,"%2ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier3);
}//sEntier3

char *sEntierAvecSigne(long yEntier){
	//// "+5" ou "-5" ou " 0"
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%+ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntierAvecSigne

char *sEst(int bAssertion){
	//rend "est" tel quel,ou négativé avec "n'"..."pas" si bAssertion est faux 
	#define kuEstLg 3//"est"
	#define kuNestPasLg 4//"n'est pas"
	char *sEst=malloc( kuAntiSlashZerO + (bAssertion)? kuEstLg : kuNestPasLg);
	if (bAssertion)
		strcat(sEst,"est");
	else strcpy(sEst,"n'est pas");
	OctetGereR(sEst);
	return(sEst);
}//sEst

int bFaux(int iQuelconque){
	//rend la constante entière kV (vrai) si iQuelconque==0 et la constante kF (faux) sinon
	int bFaux=(iQuelconque==0) ? 1 : 0;
	return(bFaux);
}//bFaux

void FlipFlop(int bNouvelEtat,int *pbFlipFlop){
	//bascule *pbFlipFlop après avoir vérifié que la valeur booléenne de bNouvelEtat bascule effectivt à chaque appel de FlipFlop
	/*if (bNouvelEtat==*pbFlipFlop)
		Stop(knStopFlipFloP);*/
	assert(bNouvelEtat!=*pbFlipFlop);
	*pbFlipFlop=bNouvelEtat;
}//FlipFlop

long zFib(int nIndex){//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0
	#define kuFibMax 50
	long zFib=0;
	double rPhi,rPhiBarre,rFib;
	Assert1("nFib",bCroit(0,nIndex,kuFibMax));
	rPhi=(1.0+sqrt(5.0))/2.0;
	rPhiBarre=(1.0-sqrt(5.0))/2.0;
	rFib=(pow(rPhi,nIndex)-pow(rPhiBarre,nIndex))/sqrt(5.0);
	//printf("rFib(%d)=%lf....",nIndex,rFib);
	zFib=trunc(rFib);
	return(zFib);
}//zFib

char *sFois(int nFois,char cMotif){
	//juxtapose nFois cMotif
	int uF;
	char *sFwa;
	char cFwa[2];
	Vrai2(nFois>=0,isprint(cMotif));//implique 1 code caractère par caractère,dc cMotif ne peut coder un "é" car il est occupe 2 codes caractères.
	sFwa=malloc(nFois+kuAntiSlashZerO);
	cFwa[0]=cMotif;
	cFwa[1]='\0';
	strcpy(sFwa,cFwa);
	for (uF=2;uF<=nFois;uF++)
		strcat(sFwa,cFwa);
	OctetGereR(sFwa);
	return(sFwa);
}//sFois

int nHasard(int uBorneLim){
	//rend un nombre aléatoire ds [0..uBorneLim[
	int nHasard;
	Croit(1,uBorneLim,kuIntegerMax-1);
	nHasard=rand()%uBorneLim;
	Croit(0,nHasard,uBorneLim-1);
	return(nHasard);
}//nHasard

int uHasard(int uBorneMax){
	//rend un nombre aléatoire ds [1..nBorneMax]
	int uHasard;
	Croit(1,uBorneMax,kuIntegerMax);
	uHasard=1+rand()%uBorneMax;
	Croit(1,uHasard,uBorneMax);
	return(uHasard);
}//uHasard

int bImpair(int iEntier){
	int bImpair=bVrai(iEntier%2);
	assert(bBool(bImpair));
	return (bImpair);
}//bImpair

double rInf(double dA,double dB){
	//rend inf(dA,dB)
	double rInf=(dA<dB)?dA:dB;
	return(rInf);
}//rInf

long yInf(long yA,long yB){
	//rend inf(yA,yB);identique à yMin(yA,yB)
	long yInf=(yA>yB)?yB:yA;
	return(yInf);
}//yInf

int bLettre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (accent,cédille,tilde...);cache la fonction isalpha()
	int bLettre=isalpha(cCaractere);
	return(bLettre);
}//bLettre

int bLettrE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	char cCode;
	int bLettrE2=0;
	assert(sString!=0);
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bLettrE2=isalpha(cCode);//vrai si consonnes ou voyelles sans signe diacritique (accent,cédille,tilde...)
	if ( !bLettrE2 && (*pnCodeCaractereRg<strlen(sString)) ) {//l'accès à sString[nCodeCaractereRg+1] est valide
		bLettrE2=bVoyellE2(sString,pnCodeCaractereRg) || bConsonnE2(sString,pnCodeCaractereRg);
	}
	return(bLettrE2);
}//bLettrE2

void Ligne(){
	printf("\n");
}//Ligne

int bLigne(){
	Ligne();
	return(1);
}//bLigne

double rLog(double rN){
	//logarithme népérien
	double rLog=log(rN);
	return(rLog);
}//rLog

double rLog2(double rN){
	//logarithme en base 2
	double rLog2=log2(rN);
	return(rLog2);
}//rLog2

double rMax(double dA,double dB){
	//rend sup(dA,dB)
	double rMax=(dA>dB)?dA:dB;
	return(rMax);
}//rMax

long yMax(long yA,long yB){
	//rend max(yA,yB);identique à ySup(yA,yB)
	long yMax=(yA>yB)?yA:yB;
	return(yMax);
}//yMax

void MemIntRaz(int piMemOrigine[],int nItemEnTout){
	Vrai2(piMemOrigine!=0,nItemEnTout>=0);
	MemIntValuer(piMemOrigine,nItemEnTout,0);
}//MemIntRaz

void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur){
	int nItem;
	Vrai2(piMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		piMemOrigine[nItem]=iValeur;
	}
}//MemIntValuer

void MemLongRaz(int pyMemOrigine[],int nItemEnTout){
	Vrai2(pyMemOrigine!=0,nItemEnTout>=0);
	MemLongValuer(pyMemOrigine,nItemEnTout,0);
}//MemLongRaz

void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur){
	int nItem;
	Vrai2(pyMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		pyMemOrigine[nItem]=yValeur;
	}
}//MemLongValuer

double rMin(double dA,double dB){
	//rend inf(dA,dB)
	double rMin=(dA<dB)?dA:dB;
	return(rMin);
}//rMin

long yMin(long yA,long yB){
	//rend min(yA,yB);identique à yInf(yA,yB)
	long yMin=(yA>yB)?yB:yA;
	return(yMin);
}//yMin

int bMajuscule(char cCaractere){
	//cCaractere est une lettre majuscule sans signe diacritique (accent,cédille,tilde...);cache la fonction isupper()
	int bMajuscule=isupper(cCaractere);
	return(bMajuscule);
}//bMajuscule

int bMinuscule(char cCaractere){
	//cCaractere est une lettre minuscule signe diacritique (accent,cédille,tilde...);cache la fonction islower()
	int bMinuscule=islower(cCaractere);
	return(bMinuscule);
}//bMinuscule

int uModulo1(int uDividende,int uDiviseur){
	//rend le modulo standard à ceci près que le résultat 0 éventuel est remplacé par uDiviseur: uModulo1(12,4)=4 
	int nModulo;
	Vrai2(uDividende>0,uDiviseur>0);
	nModulo=uDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0)//ou 1 pr que li+1 soit exécutée 
		siii("uModulo1",uDividende,uDiviseur,nModulo);
	Croit(1,nModulo,uDiviseur);
	return(nModulo);
}//uModulo1

char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation){
	//rend sVerbe suivi de sAffirmation,ou négativé avec "ne" et sNegation si bNegativer
	#define kuNegationEtBlancLgMax 4
	Vrai4(sVerbe!=0,bBool(bNegativer),sAffirmation!=0,sNegation!=0);
	char *sNie=malloc(strlen(sVerbe)+ySup(strlen(sAffirmation),strlen(sNegation))+kuNegationEtBlancLgMax);
	if (bNegativer){
		strcpy(sNie,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sNie,sVerbe);
	}
	else strcpy(sNie,sVerbe);
	strcat(sNie," ");
	if (bNegativer)
		strcat(sNie,sNegation);
	else strcat(sNie,sAffirmation);
	OctetGereR(sNie);
	return(sNie);
}//sNie

void OctetGereR(char *sMalloc){
	//prend note de l'allocation de sMalloc sur l'espace courant et libère le demi-espace le plus ancien si cette allocation sature l'espace courant
	const int kbConfirmer=kF;
	int nAlloc;
	char *sAlloc;
	if (zuOctetGereR==0){
		yOctetGereR0[nOctetGereR0++]=(long) sMalloc;
		if (nOctetGereR0>=kuOctetGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (0 vers 1)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR1[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR1[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR1=0;//premier index valide sur le futur demi-espace 
		}
	} else {
		yOctetGereR1[nOctetGereR1++]=(long) sMalloc;
		if (nOctetGereR1>=kuOctetGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (1 vers 0)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR0[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR0[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR0=0;//premier index valide sur le futur demi-espace
		}
	}
}//OctetGereR

void OutilAMORCER(){
	//amorce le présent module une fois pour toutes
	//NB ne toucher ni à nEcriS ni à bEcriS[] utilisés avant l'amorçage;
	assert(nEcriS==1);//vu l'appel s0("") en tête du main();pour s0() et s1()
	assert(strlen("à")>1);//ATTENTION: strlen("à")==2 et strlen("a")==1. strlen() ne compte plus des caractères mais des codes caractères,d'où le 2.
	bOutilAmorceR=kV;
}//OutilAMORCER

void OutilINITIALISER(){
	//relance le présent module
	Vrai(bOutilAmorceR);
}//OutilINITIALISER

void OutilTESTER(int iTest){
	long zBof;
	int nIndex=0;
	long yIndex;
	int uFois;
	int nT[1+10];
	#define kuConsonneEnTout 44
	#define kuVoyelleEnTout 47
	Appel0(sC2("OutilTESTER,test n°",sEntier(iTest)));
		char *skConsonne="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
		char *skVoyelle="ÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		char *skLettre="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		switch (iTest) {
			case 01:	printf("Le graphe %s un circuit\n",sPas("contient",1)); break;
			case 02:	printf("Le graphe %s un circuit\n",sPas("contient",0)); break;
			case 03:	printf("Il %s circuit\n",sNie("y a",1,"un","aucun")); break;
			case 04:	printf("Il %s boucle\n",sNie("y a",0,"une","aucune")); break;
			case 10:	printf("test des fonctions de concaténation:\n");
			case 11:	printf("11AVANT%sAPRES\n",sC1("a"));
			case 12:	printf("12AVANT%sAPRES\n",sC2("b","c"));
			case 13:	printf("13AVANT%sAPRES\n",sC2b("d","e"));
			case 14:	printf("14AVANT%sAPRES\n",sC2b("f",""));
			case 15:	printf("15AVANT%sAPRES\n",sC2b("","g"));
			case 16:	printf("16AVANT%sAPRES\n",sC2b("",""));
			case 17:	printf("17AVANT%sAPRES\n",sC2bp("",""));
			case 18:	printf("18AVANT%sAPRES\n",sC1p(sC2bp("h", "i")));
			case 19:	printf("19AVANT%sAPRES\n",sC7bp("1","2","3","4","5","6","7"));break;
			case 30:	assert(strlen("étagé")>6);break;//e aigu occupe 2 codes caractères,vu strlen()
			case 50:	assert(nCaractere(skVoyelle)==kuVoyelleEnTout);break;
			case 51:	assert(nCaractere(skConsonne)==kuConsonneEnTout);break;
			case 52:	assert(nCaractere(skLettre)==kuVoyelleEnTout+kuConsonneEnTout);break;
			case 55:	for (nIndex=0;nIndex<kuVoyelleEnTout;nIndex++)
							printf("test de bVoyellE2[%d] %d\n",nIndex,bVoyellE2("aeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã",&nIndex));break;
			case 60:	for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [0..3]: %d.\n",nHasard(3));
						for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [1..4]: %d.\n",uHasard(4));
						break;
			case 61:	zBof=zPgcd(60,32);
						zBof=zPgcd(170,153);
						zBof=zPpcm(60,32);
						zBof=zPpcm(170,153);
						break;
			case 62:	yIndex=-4;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-169;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-1234;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",-yIndex,sPar3(-yIndex));
						yIndex=kxLongintMax;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=kyLongintMin+1;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						break;
			case 70:	Titrer("salut");
						Titrer("");
						Titrer("solo");
						break;
			case 80:	printf("Texte: %s.\n",sFois(4,'z'));
						break;
			case 90:	for (uFois=1;uFois<10;uFois++)
							nT[uFois]=5;
						MemIntRaz(nT,10);
						break;
			case 95:	for (nIndex=0;nIndex<=50;nIndex++)
							printf("zFib(%d)=%ld\n",nIndex,zFib(nIndex));
						break;
			default:
				break;
		}
	Appel1(sC2("OutilTESTER,test n°",sEntier(iTest)));
}//OutilTESTER

int bPair(int iEntier){
	int bPair=bFaux(iEntier%2);
	assert(bBool(bPair));
	return (bPair);
}//bPair

char *sP(char *sEntreParenthese){
	//rend sEntreParenthese précédé de "(" et suivi de ")"
	assert(sEntreParenthese!=0);	
	char *sP=sC3("(",sEntreParenthese,")");
	OctetGereR(sP);
	return(sP);
}//sP

char *sPar3(long yEntier){
	//convertit yEntier en chaîne dans laquelle les groupes de 3 chiffres sont séparés par des kcSeparateur qui sont des blancs,eg 12 345.
	int uC,nChiffre,nD,nDecit,nCar;
	char kcSeparateur=' ';
	char *sEntier;
	long zEntier;
	int bSigne;
	sEntier=malloc(31+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	bSigne=(yEntier<0);
	zEntier=zAbs(yEntier);//oui,on peut faire mieux, mais ça prend plus de temps...
	sprintf(sEntier,"%ld",zEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 bits suffisent.
	nChiffre=strlen(sEntier);
	nDecit=nChiffre+(nChiffre-1)/3;
	nCar=0;
	sEntier[bSigne+nDecit]='\0';
	for (nD=bSigne+nDecit,uC=1;uC<=nChiffre;uC++){
		sEntier[--nD]='0'+zEntier%10;
		if (nD>=bSigne && (uC%3==0))
			sEntier[--nD]=kcSeparateur;
		zEntier=zEntier/10;
		nCar++;
	}
	Assert2("sPar3",zEntier==0,nD+1>=bSigne);
	if (bSigne)
		sEntier[0]='-';
	OctetGereR(sEntier);
	return(sEntier);
}//sPar3

char *sPas(char *sVerbe,int bNegativer){
	//rend sVerbe tel quel,ou négativé avec "ne"..."pas" si bNegativer 
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sPas=malloc(kuNeLg+strlen(sVerbe)+kuPasLg+kuAntiSlashZerO);
	if (bNegativer){
		strcpy(sPas,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sPas,sVerbe);
		strcat(sPas, " pas");
	}
	else strcpy(sPas,sVerbe);
	OctetGereR(sPas);
	return(sPas);
}//sPas

void Pause(){//suspend l'exécution et attend une frappe clavier minimale
	char cCar;
	printf(" Pause affichage... valider SVP (touche entrée) ou stopper l'exécution en tapant autre chose ");
	scanf("%c",&cCar);
	if (cCar!='\n')
		Stop(1);
	//printf("\n");
}//Pause

long zPgcd(long xA,long xB){
	//rend le Plus Grand Commun Diviseur de xA et xB;en O(lg(Sup(xA,xB))
	long zPgcd=1;
	long zA,zB,zQuotient,zReste;
	Assert2("zPgcd1",xA>0,xB>0);
	zA=ySup(xA,xB);
	zB=yInf(xA,xB);
	do {
		//sii("zA et zB",zA,zB);
		zQuotient=zA/zB;
		zReste=zA%zB;
		if (zReste>0)
			zPgcd=zReste;
		//si("zPgcd",zPgcd);
		zA=zB;
		zB=zReste;
	} while(zReste>0);
	//printf("Le pgcd de %ld et %ld vaut %ld.\n",xA,xB,zPgcd);
	Assert1("zPgcd2",zPgcd>0);
	return(zPgcd);
}//zPgcd

char *sPluriel(long zEffectif,char *sSingulier){
	//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges"
	int nC,nD;
	int nChaineLg;
	char *sPluriel;
	int nPosition;
	Assert2("sPluriel",zEffectif>=0,sSingulier!=0);
	sPluriel=sC2b(sEntier(zEffectif),sSingulier);
	nChaineLg=strlen(sPluriel);
	nPosition=nChainePos('$',sPluriel);
	if (nPosition>=0){//si zEffectif>1,remplacer les '$' par des 's';sinon, retirer ts les '$'.
		if (zEffectif>1){
			while (nPosition=nChainePos('$',sPluriel),nPosition>=0)
				sPluriel[nPosition]='s';
			}
		else {for (nD=0,nC=0;nC<nChaineLg;nC++)
				if (sPluriel[nC]!='$')
					sPluriel[nD++]=sPluriel[nC];
			sPluriel[nD++]='\0';
		}
	}
	else if (zEffectif>1)
		sPluriel=sC2(sPluriel,"s");
	return(sPluriel);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel

int mPoidsFort(long yEntier){
	//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2;rend -1 si non défini
	int yE,mPoidsFort;
	mPoidsFort=-1;
	if (yEntier>0){
		yE=yEntier;
		while (yE>0){
			yE=yE/2;
			mPoidsFort++;
		}
	}
	Assert1("mPoidsFort",bCroit(-1,mPoidsFort,63));
	return(mPoidsFort);
}//mPoidsFort

long zPpcm(long xA,long xB){
	//rend le Plus Petit Commun Multiple de xA et xB
	long zPpcm=0;
	Assert2("zPpcm",xA>0,xB>0);
	zPpcm=(xA*xB)/zPgcd(xA,xB);
	//Assert2("zPpcm2",xA%zPpcm==0,xB%zPpcm==0);
	//printf("Le ppcm de %ld et %ld vaut %ld.\n",xA,xB,zPpcm);
	return(zPpcm);
}//zPpcm

long zPuissance(long yOperande,int nExposant){
	long zPuissance;
	Assert2("zPuissance1",nExposant>=0,yOperande!=0 || nExposant!=0);
	zPuissance=pow(yOperande,nExposant);
	Assert1("zPuissance2",zPuissance>=0);
	return(zPuissance);
}//zPuissance;

char *sSigne(long yEntier){
	//"+" ou "-" ou " " selon que yEntier est positif ou nul, ou non.
	char *sSigne=sChoix(yEntier>=0,"+","-");
	return(sSigne);
}//sSigne

long muSigne(int bSigneInverser,long yValeur){
	long muSigne;
	muSigne=(bSigneInverser)? -yValeur: yValeur;
	return(muSigne);
}//muSigne

void Stop(int byMassacre){
	Assert1("Stop",bByte(byMassacre));
	printf("Arrêt de l'exécution, exit %d.\n",byMassacre);
	exit(byMassacre);//affiche le paramètre de exit() puis arrête l'exécution. Cache la fonction système exit().
}//Stop

double rSup(double dA,double dB){
	//rend sup(dA,dB)
	double rSup=(dA>dB)?dA:dB;
	return(rSup);
}//rSup

long ySup(long yA,long yB){
	//rend sup(yA,yB);identique à yMax(yA,yB)
	long ySup=(yA>yB)?yA:yB;
	return(ySup);
}//ySup

void Titrer(char *sTitre){
	//affiche sTitre centré sur une ligne de kuTitreLargeur caractères de type kcMotif
	const int kuTitreLargeur=60;//où ce que vous voulez
	const char kcMotif='*';//où ce que vous voulez
	assert(sTitre!=0);
	int nTitreLg=nCaractere(sTitre);
	assert(nTitreLg<kuTitreLargeur);
	int nEspace=(kuTitreLargeur-nTitreLg)/2;//quitte à perdre un caractère
	int bUnMotifEnSus=bImpair(nTitreLg);//ie un kcMotif sera ajouté pr récupérer le caractère perdu li-1
	assert(nEspace+nTitreLg+nEspace+bUnMotifEnSus==kuTitreLargeur);
	printf("%s%s%s\n",sFois(nEspace,kcMotif),sTitre,sFois(nEspace+bUnMotifEnSus,kcMotif));
}//Titrer

int bVecteurContient(int nEnquis,int nCardinal,int iVecteur[]){
	//nEnquis dans iVecteur[1..nCardinal] 
	int uE;
	int bContient=kF;
	Assert1("bVecteurContient",nCardinal>0);
	for (uE=1;uE<=nCardinal;uE++)
		if (nEnquis==iVecteur[uE])
			 bContient=kV;
	return(bContient);
}//bVecteurContient

void VecteurVoir(char *sNom,int piQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche piQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Vrai2(sNom!=0,piQuelVecteur!=0);
	Croit(0,nIndexMin,nIndexMax);
	printf("%s:",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%4d",piQuelVecteur[nE]);
	printf("\n");
}//VecteurVoir

void VecteurVoyr(char *sNom,long pyQuelVecteur[],long zIndexMin,long zIndexMax){
	//affiche pyQuelVecteur[zIndexMin..zIndexMax],dc bornes incluses
	long zE;
	Vrai2(sNom!=0,pyQuelVecteur!=0);
	Croit(0,zIndexMin,zIndexMax);
	printf("%s:",sNom);
		for (zE=zIndexMin;zE<=zIndexMax;zE++)
			printf("%12ld",pyQuelVecteur[zE]);
	printf("\n");
}//VecteurVoir


int bVoyelle(char *sString,int nCodeCaractereRg){
	//sString[nCodeCaractereRg] ou Chaine[nCodeCaractereRg..nCodeCaractereRg+1] code une voyelle
	int nRg=nCodeCaractereRg;
	Vrai2(sString!=0,nCodeCaractereRg>=0);
	int bVoyelle=bVoyellE2(sString,&nRg);
	return(bVoyelle);
}//bVoyelle

int bVoyellE2(char *sString,int *pnCodeCaractereRg){
	//sString[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une voyelle;si vrai et 2 codes, passe au code suivant
	//pour le seul ŸaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã";//piqûre Haüy;nValide2[1] pour le seul Ÿ
	int nCar;
	char cCode;
    #define knVoyelle1LiM 12
    #define knVoyelle2LiM 33
    #define knVoyelle3LiM 01
	//nVoyelle1 dédié voyelles sans signes diacritiques";
	int nVoyelle1[knVoyelle1LiM]={'A','E','I','O','U','Y','a','e','i','o','u','y'};
	//nVoyelle2 dédié dans l'ordre à éàèùâêîôûäïöüÿÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜã";
	int nVoyelle2[knVoyelle2LiM]={87,96,88,71,94,86,82,76,69,92, 81,74,68,65,126,118,114,108,101,119, 128,103,126,118,114,108,101,124,117,113, 106,100,93};
	//nVoyelle3 pour le seul Ÿ
	int nVoyelle3[knVoyelle3LiM]={72};
	int bVoyellE2=0;
	assert(sString!=0);
	Croit(0,*pnCodeCaractereRg,strlen(sString));
	cCode=sString[*pnCodeCaractereRg];
	bVoyellE2=isalpha(cCode);
	if (bVoyellE2){//voyelle ou consonne?
		for (bVoyellE2=0,nCar=0; nCar<knVoyelle1LiM; nCar++)
			bVoyellE2=bVoyellE2||(cCode==nVoyelle1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sString)) {//l'accès à sString[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle2LiM; nCar++)
				bVoyellE2=bVoyellE2||(cCode==-nVoyelle2[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
		else if (cCode==kcEchappemenT2) {
			cCode=sString[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle3LiM; nCar++)
				bVoyellE2= bVoyellE2 || (cCode==-nVoyelle3[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
	}
	return(bVoyellE2);
}//bVoyellE2

void Vrai(int bAssertion){
	assert(bAssertion);
}//Vrai

int bVrai(int iQuelconque){
	//rend vrai ssi iQuelconque!=0
	int bVrai=(iQuelconque!=0) ? 1 : 0;
	return(bVrai);
}//bVrai

void Vrai2(int bAssertion1,int bAssertion2){
	assert2(bAssertion1,bAssertion2);
}//Vrai2

void Vrai3(int bAssertion1,int bAssertion2,int bAssertion3){
	assert3(bAssertion1,bAssertion2,bAssertion3);
}//Vrai3

void Vrai4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	assert4(bAssertion1,bAssertion2,bAssertion3,bAssertion4);
}//Vrai4

void Vrai5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	assert5(bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5);
}//Vrai5

void Vrai6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	assert6(bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Vrai6

void While(long zIterationMax){
	//prend note du nombre maximum d'itérations acceptable dans le while qui suit immédiatement l'appel de cette routine
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return, etc.
	assert(zIterationMax>=0);
	ipWhilE++;
	assert(ipWhilE<=kuWhileMaX);
	zWhilE[ipWhilE]=zIterationMax;
}//While

int bWhile(int bExpressionBooleenne){
	//rend bExpressionBooleenne tout en gérant l'itération en cours (ie son rang ne dépasse pas zIterationMax spécifié dans l'appel à While() qui précède
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return,etc
	Croit(0,ipWhilE,kuWhileMaX);
	zWhilE[ipWhilE]--;//décrémente le nombre d'itérations de la boucle imbriquée de rang ipWhilE
	assert(zWhilE[ipWhilE]>=0);
	if (bExpressionBooleenne==0){//la sortie imminente du while courant ramène le contexte ds la boucle imbriquée englobante,de rang ipWhilE-1
		zWhilE[ipWhilE]=0;//superflu mais ce nettoyage facilite la mise au point
		ipWhilE--;//vital
		assert(ipWhilE>=0);
	}//Chaque boucle while est donc contrôlée via 1° un appel à While() avant le while et 2° un appel à bWhile() dans l'expression booléenne liée au...
	return(bExpressionBooleenne);//...while; Appel1("") à la fin du main() vérifie que le contrôle des while est bien séquencé via "assert(ipWhilE>=0)".
}//bWhile




