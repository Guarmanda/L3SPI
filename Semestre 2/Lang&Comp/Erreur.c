#include "Outil.h"
#include "Alex.h"
#include "Erreur.h"
#define knPileMaX 50
int bErreurAmorceR;
int ipErreuR;//ip = index de pile
struct{int eBug;int uLxm;} nPilE[1+knPileMaX];

void ErreurAfficheR(int ipErreur);

void ErreurAfficheR(int ipErreur){
	//affiche en clair l'erreur numéro ipErreur;ip = index de pile
	char *sErreur;
	Assert1("ErreurAfficheR",bCroit(1,ipErreur,knPileMaX));
	sErreur="erreur système";//signifie que votre compilateur se plante
	si("nPilE[ipErreur].uLxm ",nPilE[ipErreur].uLxm);
    AlexDenoncer(nPilE[ipErreur].uLxm);
	switch (nPilE[ipErreur].eBug) {
		case  eSemHoraire:	sErreur="\"hh.mm\" ne vérifie pas 0≤h≤23 et 0≤mm≤59";break;
		default:break;
	}
	printf(": %s",sErreur);
	if ( bCroitStrict(eSem0,nPilE[ipErreur].eBug,eSem1) )
		printf(" (analyse sémantique).\n");
}//ErreurAfficheR

void ErreurAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	ipErreuR=0;
	bErreurAmorceR=kV;
}//ErreurAMORCER

void ErreurDenoncer(){
	//dénonce toutes les erreurs qui ont été empilées pendant la compilation en les affichant à la console
	int ipErreur;
	Assert2("ErreurDenoncer",bErreurAmorceR,ipErreuR>=0);
	for (ipErreur=1;ipErreur<=ipErreuR;ipErreur++)
		ErreurAfficheR(ipErreur);
}//ErreurDenoncer

void ErreurEmpiler(int nErreurNumero, int nLexeme){
	//empile le nErreurNumero et le nLexeme où l'erreur a été détectée (donc l'erreur est sur ce lexème ou avant celui-ci) 
	Assert3("ErreurEmpiler",bErreurAmorceR,bCroitStrict(eLimite0,nErreurNumero,eLimite1),bAlexLexeme(nLexeme));
	ipErreuR++;
	nPilE[ipErreuR].eBug=nErreurNumero;
	nPilE[ipErreuR].uLxm=nLexeme;
}//ErreurEmpiler

int nErreurEnTout(){
	Assert2("nErreurEnTout",bErreurAmorceR,ipErreuR>=0);
	return(ipErreuR);
}//nErreurEnTout

void ErreurINITIALISER(){
	//relance le présent module
	Assert1("ErreurINITIALISER",bErreurAmorceR);
	ipErreuR=0;
}//ErreurINITIALISER

void ErreurTESTER(int iTest){
	//teste le présent module
	Appel0(sC2("ErreurTESTER,test n°",sEntier(iTest)));
		Assert1("ErreurTESTER",bErreurAmorceR);
		switch (iTest) {
			case  1:	break;
			default:break;
		}
	Appel1(sC2("ErreurTESTER,test n°",sEntier(iTest)));
}//ErreurTESTER

/*
int bAlexHoraire(int uLexeme){
	#define kuHeureHeurePointMinuteMinuteLg 5
	int bHoraire;
	float rHoraire;
	int nMinute;
	char sLexeme[knByteLiM];
	bHoraire=bAlexReel(uLexeme);
	if (bHoraire){
		CodeSourceTrancheR(lxmChainE[uLexeme].indexdebut,lxmChainE[uLexeme].indexfin,kF,sLexeme);
		//ss("sLexeme",sG(sLexeme));
		bHoraire=bHoraire && (strlen(sLexeme)==kuHeureHeurePointMinuteMinuteLg);
		if (bHoraire){
			sscanf(sLexeme,"%f5.2",&rHoraire);
			//sr("rHoraire",rHoraire);
			nMinute=trunc(rHoraire*100);
			nMinute=nMinute%100;
			//si("nMinute",nMinute);
			bHoraire=bHoraire && bCroit(0,nMinute,59);
			//compléter le code pour les heures
		}
	}
	return(bHoraire);
}//bAlexHoraire
*/