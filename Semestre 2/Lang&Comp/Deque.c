#include "Outil.h"
#include "Deque.h"
//NB:pour manipuler une deque de 20 sommets,encadrer tous les accès à la deque par DequeOuvrir(20) et DequeOuvrir(0);

const int knDequeCardinalMaX=100;//nb max de sommets admissible physiqt ds la deque; k comme constante;n comme entier naturel. 
int nCarD;//nombre de sommets stockés actuellement dans la deque
int nCardMaX;//nombre total de sommets admissible dans la dernière deque allouée;n comme entier naturel,donc 0 Ou plus.
int bDequeOuvertE;//flipflop;b comme booléen;un flipflop est une bascule à 2 états (flip,d'abord, puis flop,respectivement,d'où son nom)
int bDequeAmorceR;//ie le module a effectivement été amorcé
int sLasT;//si non nul, index sur le sommet de pile mais aussi valeur de fond de pile; s comme sommet
struct DequE{
	int sNexT[1+100];//s comme sommet;soit 1+knDequeCardinalMaX puisque l'indice 0 est inutilisé
}DequE,*pDequE;

void DequeAllouer(int nCardinalMax){//O(1)
	//appelé avec nCardinalMax>0 pr allouer une deque;devra être appelé ensuite avec nCardinalMax=0 pr restituer la deque
	Assert2("DequeAllouer",bDequeAmorceR,bCroit(0,nCardinalMax,knDequeCardinalMaX));
	FlipFlop(bVrai(nCardinalMax>0),&bDequeOuvertE);
	nCardMaX=nCardinalMax;
	nCarD=0;
	sLasT=0;
	if (nCardinalMax>0)
		pDequE=malloc(sizeof(DequE));
	else free(pDequE);
	if (bDequeOuvertE)
		DequeRazer(nCardMaX);//dc en O(nCardMaX) et pas en O(knDequeCardinalMaX),ce qui changerait la complexité des petits graphes
}//DequeAllouer

void DequeAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	//caractériser la deque avec des valeurs aberrantes qui seront dénoncées par les assertions
		pDequE=0;
		nCarD=-knDequeCardinalMaX;
		sLasT=-knDequeCardinalMaX;
	bDequeOuvertE=kF;//vital
	bDequeAmorceR=kV;
}//DequeAMORCER

int nDequeCardinal(){//O(1)
	int nCardinal=nCarD;
	Assert2("nDequeCardinal",bDequeAmorceR,bCroit(0,nCardinal,nCardMaX));
	return(nCardinal);
}//nDequeCardinal

int bDequeContient(int sSommeT){//O(1)
	int bContient;
	Assert3("bDequeContient",bDequeAmorceR,bDequeOuvertE,bCroit(1,sSommeT,nCardMaX));
	bContient=(pDequE->sNexT[sSommeT]!=0);//ce code peut être compacté. Mais est-ce plus clair?
	return(bContient);//exemple de routine où les contrôles (ici, des assertions) sont plus coûteux que le code utile.
}//nDequeCardinal

int sDequeDefiler(){//O(1)
	int sDefiler;
	sDefiler=sDequeDepiler();//ds cette implémentation de la deque,tête de file et sommet de pile sont toujours confondues
	return(sDefiler);
}//sDequeDefiler

int sDequeDepiler(){//O(1)
	int sDepiler=0;
	Assert4("sDequeDepiler",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,sLasT,nCardMaX));
	if (nCarD>0) {
		sDepiler=pDequE->sNexT[sLasT];//lit le sommet de pile (alias la tête de file)
		pDequE->sNexT[sLasT]=pDequE->sNexT[sDepiler];
		pDequE->sNexT[sDepiler]=0;//vital vu les tests tels que "if (!sNexT[sSommeT])" ds DequeEmpiler
		nCarD--;
	}
	Assert2("sDequeDepiler",bCroit(1,sDepiler,knDequeCardinalMaX),nCarD>=0);
	return(sDepiler);
}//sDequeDepiler

void DequeEmpiler(int sSommeT){//O(1)
	//empile sSommeT si celui-ci n'est pas déjà dans la deque
	Assert4("DequeEmpiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX));
	if (!pDequE->sNexT[sSommeT]) {
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
			sLasT=sSommeT;//seule différence avec le code de DequeEnfiler()
		}
	}
}//DequeEmpiler

void DequeEnfiler(int sSommeT){//O(1)
	//enfile sSommeT si celui-ci n'est pas déjà dans la deque
	Assert4("DequeEnfiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX));
	if (!pDequE->sNexT[sSommeT]) {
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
		}
		sLasT=sSommeT;//seule différence avec le code de DequeEmpiler()
	}
}//DequeEnfiler

void DequeINITIALISER(){//O(?)
	//relance le présent module
	Assert2("DequeINITIALISER",bDequeAmorceR,!bDequeOuvertE);
}//DequeINITIALISER

int sDequeQueue(){//O(1)
	int sQueue=0;
	Assert4("sDequeQueue",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,nCarD,nCardMaX));
	if (nCarD>0)//ce test évite de retourner une valeur flottante (copie de LasT) au lieu d'une constante (0) quand les assertions sont désactivées
		sQueue=sLasT;
	Croit(1,sQueue,nCardMaX);
	return(sQueue);
}//sDequeQueue

void DequeRazer(int nCardinalMax){//O(nCardinalMax)
	int uS;
	Assert4("DequeRazer",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX),bCroit(0,nCardinalMax,nCardMaX));
	for (uS=1;uS<=nCardinalMax;uS++)
		pDequE->sNexT[uS]=0;
	nCarD=0;
	sLasT=0;
}//DequeRazer

int sDequeSommet(){//O(1)
	int sSommet;
	Assert4("sDequeSommet",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,sLasT,nCardMaX));
	sSommet=pDequE->sNexT[sLasT];
	Croit(1,sSommet,nCardMaX);
	return(sSommet);
}//sDequeSommet

int sDequeSuivant(int sX){//O(1)
	int sY;
	sY=pDequE->sNexT[sX];
	Croit(1,sY,nCardMaX);
	return(sY);
}//sDequeSuivant

void DequeTESTER(int iTest){
	//teste le présent module
	int sSource;
	Appel0(sC2("DequeTester,test n°",sEntier(iTest)));
		switch (iTest) {
			case 1:
				DequeAllouer(12);
					DequeVoir("Deque vide");
					DequeEnfiler(5);
					DequeEnfiler(3);
					DequeVoir("Deque pleine");
					sSource=sDequeDefiler();
					DequeVoir("Deque finale");
				DequeAllouer(0);
				break;
			default:
				break;
		}
	Appel1(sC2("DequeTester,test n°",sEntier(iTest)));
}//DequeTESTER	

int sDequeTete(){//O(1)
	int sTete;
	sTete=sDequeSommet();//la tête de file est toujours le sommet de pile ds la présente implémentation de la deque
	return(sTete);
}//sDequeTete

int bDequeVide(){//O(1)
	int bVide;
	Assert4("bDequeVide",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX),bCroit(0,nCarD,nCardMaX));
	bVide=(nCarD==0);
	return(bVide);//exemple de routine où les contrôles (ici, des assertions) sont plus coûteux que le code utile.
}//bDequeVide

void DequeVoir(char *sMessage){//O(nCardMaX)
	int uS;
	Assert3("DequeVoir",bDequeAmorceR,bDequeOuvertE,sMessage!=0);
	printf("%s\n",sMessage);
	//afficher nCarD après affichage des index de sNexT[]
		printf("index = ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",uS);
		printf("  nCarD=%d\n",nCarD);
	//afficher sLasT après affichage des valeurs de sNexT[]
		printf("valeur= ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",pDequE->sNexT[uS]);
		printf("  sLasT=%d\n",sLasT);
}//DequeVoir

