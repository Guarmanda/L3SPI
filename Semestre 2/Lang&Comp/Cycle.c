#include "Outil.h"
#include "Cycle.h"
#include "Deque.h"
#include "Graphe.h"

#define kuArcEnTouT   40
#define knCycleLiM 1000
#define kbLitteraL 1
int sCyclE[knCycleLiM][knSommetLiM];
int nCycleAfficheR=0;
int bCycleAmorceR;

void ArtereEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler);
void ArtereInventorieR(graf *pgG,int sSource,int sTrappe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler);
void CycleAfficheR(graf gG,int sSousConnexe);
int bCycleAlternE(graf gG,int sListe[]);
int bCycleDecrirE(graf gG,int bCouleurDoitChanger,int sX,int sY);
void CycleDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible);
int bCycleEmpileR(int *pnCycleDistinct);
void CycleGenereR(char kcArc[],int nExces,graf **ppgG,int *pbColoration,int *pnSousConnexe);
void CycleEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler);
void CycleInventorieR(graf gG,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler);
void CycleRazeR();
char cSommetLitteraL(int sX);
void SommetListeR(int sSommet,int bVirguler);
int bSommetSousConnexE(graf gG,int sListe[],int nSousConnexe,int *psSoliton);
int bSommetViergE(graf gG,int sOrigine,int sVierge,int *pbCycle);

void ArtereEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler){
	//génère le graphe défini par (kcArc,nExces) et inventorie soit tous ses cycles soit seult ceux qui ne rendent aucun sommet sous-connexe.
	graf *pgG;
	int bAfficher=kF;
	int nSousConnexe;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	int nSommet;
	int sPole0,sPole1;
	CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
	GrapheAfficher0(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec","sans"),"couleurs"));
	GrapheSymetriser(pgG);
	//GrapheAfficher0(*ppgG,bCouleurChange,"Graphe symétrique colorié après symétrisation");
	Dis(sC4("Inventaire ",sChoix0(!bDetailler,"non "),"détaillé",sChoix0(bSansSommetSousConnexe,sC2b(", sous-connexité interdite pour les sommets A à",sC(cSommetLitteraL(nSousConnexe))))));
	CycleInventorieR(*pgG,bSansSommetSousConnexe,bCouleurChange,nSousConnexe,bAfficher,!bDetailler);
	nSommet=pgG->nSommetEnTout;
	for (sPole0=nSommet-3;sPole0<=nSommet;sPole0++)
		for (sPole1=nSommet-3;sPole1<=nSommet;sPole1++)
			if (sPole0<sPole1){
				s(sC3("Artère ",sCouple(sPole0,sPole1),":"));
				GrapheCreer(0,&pgG);
				nCycleAfficheR=0;
				nSousConnexe=0;
				CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
				//GrapheAfficher0(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec","sans"),"couleurs"));
				GrapheSymetriser(pgG);
				//GrapheAfficher0(*ppgG,bCouleurChange,"Graphe symétrique colorié après symétrisation");
				bAfficher=(sPole0==11) && (sPole1==14);
				CycleInventorieR(*pgG,bSansSommetSousConnexe,bCouleurChange,nSousConnexe,bAfficher,!bDetailler);
				ArtereInventorieR(pgG,sPole0,sPole1,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
			}
}//ArtereEnumereR

void ArtereInventorieR(graf *pgG,int sSource,int sTrappe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler){
	//inventorie et affiche les artères de gG qui relient sSource à sTrappe.
	int sBut;
	int sCible;
	int nCycleEnTout=0;
	int nCycleCompatible=0;
	int sDepart;
	int k1Empiler=kV;
	int sZ;
	//CycleRazeR();//raze la pile qui mémorise les cycles jugés pertinents
	//sBut et sCible étant deux nouveaux sommets reliés via (sCible,sSource) et (sTrappe,sBut)
	GrapheSommer(pgG,k1Empiler);
		GrapheSommer(pgG,k1Empiler);
			sCible=pgG->nSommetEnTout-1;
			sBut=pgG->nSommetEnTout;
			GrapheArquer(pgG,sCible,sSource);GrapheColorer(pgG,sCible,sSource,3);
			GrapheArquer(pgG,sTrappe,sBut);GrapheColorer(pgG,sTrappe,sBut,3);
			GrapheArquer(pgG,sCible,sBut);GrapheColorer(pgG,sCible,sBut,1);
			GrapheSymetriser(pgG);
			if (bAfficher)
				GrapheAfficher0(pgG,kV,"Graphe artérisé symétrique colorié après symétrisation");
			sDepart=sCible;
			//explorer en largeur d'abord en partant de chaque sommet sDepart;gG.sPer[] mémorise le chemin qui relie sDepart au sommet courant
				//nCycleAfficheR=0;
				//gG.sPer[]:=0
					for (sZ=1;sZ<=pgG->nSommetEnTout;sZ++)
						pgG->sPer[sZ]=0;
				pgG->sPer[sDepart]=sDepart;//vital pour identifier le sommet origine de ts les chemins détectés par nCycleDetecteR()
				CycleDetecteR(*pgG,sDepart,kF,bColoration,nSousConnexe,bDetailler,&nCycleEnTout,&nCycleCompatible);
		GrapheSommer(pgG,!k1Empiler);
	GrapheSommer(pgG,!k1Empiler);
	if (bAfficher)
		Dis(sC5b("Bilan:",sPluriel(nCycleCompatible,"artère"),"sans sous-connexité","sur",sPluriel(nCycleEnTout,"artère$ inventoriée$")));
}//ArtereInventorieR

void CycleAfficheR(graf gG,int sSousConnexe){
	//affiche sCyclE[0],énuméré depuis le sommet de plus petit rang;si sSousConnexe>0, affiche le nom de ce sommet sous-connexe.
	int nCardinal;
	int uS;
	nCardinal=sCyclE[0][0];
	printf("Cycle n°%2d (lgr %2d): ",nCycleAfficheR,nCardinal);
	//afficher le Cycle stocké ds sCyclE[0]
		printf("(");
			for (uS=1;uS<=nCardinal;uS++)
				SommetListeR(sCyclE[0][uS],1);
			SommetListeR(sCyclE[0][1],0);
		printf(")");
	if (sSousConnexe>0)
		printf("   (%c sous-connexe)",cSommetLitteraL(sSousConnexe));
	printf(".\n");
}//CycleAfficheR

int bCycleAlternE(graf gG,int sListe[]){
	//vrai ssi les couleurs des arcs qui relient les sommets de sListe changent d'arc en arc (circulairt)
	int sDebug[1+8]={0,1,5,10,12,13,14,15,16};
	int uItem;
	int nPresent;
	int bAlterne;
	int uArc;
	int nCardinal=sListe[0];
	int nCouleur,nCouleur0;
	int sX,sY,uS;
	if (0){//debugger grâce au code qui suit qui repère une liste contenant les éléments de sDebug
		nPresent=0;
		for (uS=1;uS<=nCardinal;uS++)
			for (uItem=1;uItem<=8;uItem++){
				if (sListe[uS]==sDebug[uItem])
					nPresent++;
			}
		if (nCardinal==8 && nPresent==8)
			bAlterne=kF;//poser un point d'arrêt ici
	}
	bAlterne=kV;//d
	sX=sListe[nCardinal];
	sY=sListe[1];
	nCouleur=nGrapheCouleur(gG,sX,sY);//a
	for (uArc=1;uArc<=nCardinal;uArc++){
		nCouleur0=nCouleur;
		sX=sY;
		sY=(uArc<nCardinal)?sListe[uArc+1]:sListe[1];
		nCouleur=nGrapheCouleur(gG,sX,sY);
		bAlterne=bAlterne && (nCouleur!=nCouleur0);
	}
	//bAlterne=kV;
	return(bAlterne);
}//bCycleAlternE

void CycleAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bCycleAmorceR=kV;
}//CycleAMORCER

int bCycleDecrirE(graf gG,int bCouleurDoitChanger,int sX,int sY){
	//vrai ssi le Cycle qui traverse sX et sY est alterne de lgr>2; si vrai, le décrit en le stockant ds sCyclE[0] depuis le sommet de plus petit rang.
	int nCardinal;
	int bDecrire;
	int sDernier;
	int sListe[knSommetLiM];
	int nPlace;
	int sPremier;
	int nRang;
	int uS;
	bDecrire=kF;
	for (uS=0;uS<knSommetLiM;uS++)
		sCyclE[0][uS]=0;
	//nCardinal:=lgr du Cycle,sListe[]:=pile de sommets
		nCardinal=0;
		sDernier=sX;
		sListe[++nCardinal]=sDernier;
		While(knSommetLiM);
		while ( bWhile(gG.sPer[sDernier]!=sDernier && gG.sPer[sDernier]!=sY) ) {
			sDernier=gG.sPer[sDernier];
			sListe[++nCardinal]=sDernier;
		}
		if (sY!=0)
			sListe[++nCardinal]=sY;
		sListe[0]=nCardinal;
	bDecrire=(nCardinal>2) && (!bCouleurDoitChanger || bCycleAlternE(gG,sListe));
	if (bDecrire){
		//sPremier:=sommet de plus petit rang
			sPremier=knSommetLiM;//a
			for (uS=1;uS<=nCardinal;uS++)
				if (sListe[uS]<sPremier){
					sPremier=sListe[uS];
					nRang=uS;
				}
		//sCyclE[0]:=sListe décalée, ie en commençant par sPremier
			for (nPlace=0;nPlace<knSommetLiM;nPlace++)
				sCyclE[0][nPlace]=0;
			nPlace=0;//a
			for (uS=nRang;uS<=nCardinal;uS++)
				sCyclE[0][++nPlace]=sListe[uS];
			for (uS=1;uS<=nRang;uS++)
				sCyclE[0][++nPlace]=sListe[uS];
			sCyclE[0][0]=nCardinal;
	}
	return(bDecrire);
}//bCycleDecrirE

void CycleDetecteR(graf gG,int sDepuis,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bDetailler,int *pnCycleEnTout,int *pnCycleCompatible){
	//détecter les ciruits en parcourant(récursivt) le graphe gG à partir de sDepuis; mémorise et affiche les cycles détectés
	int bCycle;
	int bEmpiler;
	int aK;
	int bSousConnexe;
	int sSousConnexe;
	int sVoisin;
	//printf("sDepuis:%d\n",sDepuis);
	if (nCycleAfficheR<knCycleLiM)
		for (aK=gG.aHed[sDepuis]; aK<gG.aHed[sDepuis+1]; aK++) {
			sVoisin=gG.sSuk[aK];
			if ( bSommetViergE(gG,sDepuis,sVoisin,&bCycle) ) {
				gG.sPer[sVoisin]=sDepuis;
				CycleDetecteR(gG,sVoisin,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,pnCycleEnTout,pnCycleCompatible);
			}
			else if (bCycle){
				if (bCycleDecrirE(gG,bColoration,sDepuis,sVoisin)){
					bEmpiler=bCycleEmpileR(&nCycleAfficheR);//empile sCyclE[0] en interne  si pas déjà fait
					if (bEmpiler){
						sSousConnexe=0;
						bSousConnexe=bSommetSousConnexE(gG,sCyclE[0],nSousConnexe,&sSousConnexe);
						if (!bSousConnexe)
							(*pnCycleCompatible)++;
						if (!bSansSommetSousConnexe || !bSousConnexe || bDetailler)
							CycleAfficheR(gG,sSousConnexe);
					}
				}
				//bExplorer=kF;
			}
		}
	*pnCycleEnTout=nCycleAfficheR;
}//CycleDetecteR

int bCycleEmpileR(int *pnCycleDistinct){
	//empile ds sCyclE[nCycleDistinct+1] le Cycle sCyclE[0] s'il est distinct de ceux stockés ds sCyclE[1..nCycleDistinct]
	int uCycle;
	int sCyclEz[knSommetLiM];
	int sCyclEs[knSommetLiM];
	int nCycleDistinct;
	int uCardinal;
	int bEmpiler;
	int nEmpiler=0;
	int bPareil;
	int uS;
	nCycleDistinct=*pnCycleDistinct;
	uCardinal=sCyclE[0][0];
	Assert1("bCycleEmpileR",uCardinal>1);
	for (uS=1; uS<=uCardinal+1; uS++)
		sCyclEz[uS]=sCyclE[0][uS];//copie map
	for (uCycle=1;(uCycle<=nCycleDistinct) && (nEmpiler==0); uCycle++)
		if (uCardinal==sCyclE[uCycle][0]){
			for (uS=1; uS<=uCardinal+1; uS++)//le sommet qui débute le Cycle (index 1) le termine aussi (index uCardinal+1)
				sCyclEs[uS]=sCyclE[uCycle][uS];//copie map
			for (bPareil=kV,uS=1; uS<=uCardinal; uS++)
				bPareil=bPareil && (sCyclEz[uS]==sCyclEs[uS]);
			if (bPareil)//Cycle déjà mémorisé,parcouru ds le mm sens
				nEmpiler=uCycle;
			for (bPareil=kV,uS=1; uS<=uCardinal; uS++)
				bPareil=bPareil && (sCyclEz[uS]==sCyclEs[uCardinal-uS+2]);
			if (bPareil)//Cycle déjà mémorisé,mais parcouru en sens inverse
				nEmpiler=uCycle;
		}
	bEmpiler=(nEmpiler==0);
	if (bEmpiler) {//empiler le nouveau Cycle
		uCycle=1+nCycleDistinct;
		Assert1("bCycleEmpileR",uCycle<knCycleLiM);
		//se("uCycle empilé",uCycle);
		for (uS=0; uS<knSommetLiM; uS++)
			sCyclE[uCycle][uS]=sCyclE[0][uS];
		*pnCycleDistinct=uCycle;
		bEmpiler=uCycle;
	};
	return(bEmpiler);
}//bCycleEmpileR

void CycleEnumereR(char kcArc[],int nExces,int bSansSommetSousConnexe,int bDetailler){
	//génère le graphe défini par (kcArc,nExces) et inventorie soit tous ses cycles soit seult ceux qui ne rendent aucun sommet sous-connexe.
	graf *pgG;
	int bAfficher=kF;
	int nSousConnexe;
	int bCouleurChange;//ie il y a plusieurs couleurs spécifiées ds kcArc
	CycleGenereR(kcArc,nExces,&pgG,&bCouleurChange,&nSousConnexe);
	GrapheAfficher0(pgG,bCouleurChange,sC3b("Graphe généré avant symétrisation, et spécifié",sChoix(bCouleurChange,"avec","sans"),"couleurs"));
	GrapheSymetriser(pgG);
	//GrapheAfficher0(*ppgG,bCouleurChange,"Graphe symétrique colorié après symétrisation");
	Dis(sC4("Inventaire ",sChoix0(!bDetailler,"non "),"détaillé",sChoix0(bSansSommetSousConnexe,sC2b(", sous-connexité interdite pour les sommets A à",sC(cSommetLitteraL(nSousConnexe))))));
	CycleInventorieR(*pgG,bSansSommetSousConnexe,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,7,9,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,7,9,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,5,2,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,7,2,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,7,5,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,9,5,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
	//ArtereInventorieR(pgG,9,2,bCouleurChange,nSousConnexe,bAfficher,bDetailler);
}//CycleEnumereR

void CycleGenereR(char kcArc[],int nExces,graf **ppgG,int *pbColoration,int *pnSousConnexe){
	//génère des cycles en créant un graphe défini par les triplets (sommet origine,sommet destination,couleur) de la chaîne kcArc.
	int uArc;
	int nArc0[1+kuArcEnTouT];//NB sommet origine de l'arc
	int nArc1[1+kuArcEnTouT];//NB sommet destination de l'arc
	int uArcEnTout;
	int nC;
	int uChaineLg;
	int nCouleur;
	int sDernier;
	int sDestination;
	int nDistinct[1+kuByteMax];
	int sOrigine;
	int sPremier;
	int uS;
	char cSommet;
	int nSommet;
	uChaineLg=strlen(kcArc);
	Assert2("CycleGenereR1", uChaineLg %3==0,uChaineLg<kuByteMax);
	//nSommet:=nb de sommets distincts cités ds kcArc
		for (nC=0;nC<=kuByteMax;nC++)
			nDistinct[nC]=0;
		for (nC=0;nC<uChaineLg;nC++)
			if (nC%3!=2){//nC n'indexe pas une couleur mais un sommet
				cSommet=kcArc[nC];
				nSommet=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
				nDistinct[nSommet]++;
			}
		//les sommets de kcArc[] sont réputés commencer à la lettre 'A'et être consécutifs;soit nDernier le sommet de rang maximal
			sPremier=kuIntegerMax;
			sDernier=0;
			for (uS=1;uS<=kuByteMax;uS++)
				if (nDistinct[uS]>0){
					sPremier=yInf(sPremier,uS);
					sDernier=ySup(sDernier,uS);
				}
			Assert1("CycleGenereR2", sPremier==1);
			for (uS=sPremier;uS<=sDernier;uS++)
				Assert1("CycleGenereR3", nDistinct[uS]>0);
		nSommet=sDernier;
	*pnSousConnexe=nSommet-nExces;//seuls les *pnSousConnexe premiers sommets pourront être déclarés sous-connexes;les autres sommets seront ignorés.
	uArcEnTout=(uChaineLg)/3;
	Assert2("CycleGenereR4", *pnSousConnexe>=0, uArcEnTout>0);
	//nArc0[]:=sommets origine listés ds cArc[]
		nArc0[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			nArc0[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	//nArc1[]:=sommets destination listés ds cArc[]
		nArc1[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-2];
			nArc1[uArc]=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
		}
	GrapheCreer2(ppgG,nSommet,uArcEnTout,&nArc0[0],&nArc1[0]);
	//colorier chaque arc
		*pbColoration=kV;
		nArc1[0]=0;
		for (uArc=1;uArc<=uArcEnTout;uArc++){
			cSommet=kcArc[3*uArc-3];
			sOrigine=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			cSommet=kcArc[3*uArc-2];
			sDestination=(bCroit('a',cSommet,'z'))? cSommet-'a'+kuMinusculeOffset : cSommet-'A'+kuMajusculeOffset;
			nCouleur=kcArc[3*uArc-1]-'0';
			Assert1("CycleGenereR5", bCroit(0,nCouleur,3));
			if (nCouleur==0)
				*pbColoration=kF;
			GrapheColorer(*ppgG,sOrigine,sDestination,nCouleur);
		}
}//CycleGenereR

void CycleINITIALISER(){//O(?)
	//relance le présent module
	Assert1("CycleINITIALISER",bCycleAmorceR);
}//CycleINITIALISER

void CycleInventorieR(graf gG,int bSansSommetSousConnexe,int bColoration,int nSousConnexe,int bAfficher,int bDetailler){
	//inventorie et affiche les cycles de gG,en totalité si bSansSommetSousConnexe est faux,ou seult ceux qui ne créent pas de sommet sous-connexe sinon.
	int nCycleEnTout=0;
	int nCycleCompatible=0;
	int sDepart;
	int sZ;
	CycleRazeR();//raze la pile qui mémorise les cycles jugés pertinents
	//explorer en largeur d'abord en partant de chaque sommet sDepart;gG.sPer[] mémorise le chemin qui relie sDepart au sommet courant
		nCycleAfficheR=0;
		for (sDepart=1;sDepart<=gG.nSommetEnTout;sDepart++){
			//gG.sPer[]:=0
				for (sZ=1;sZ<=gG.nSommetEnTout;sZ++)
					gG.sPer[sZ]=0;
			gG.sPer[sDepart]=sDepart;//vital pour identifier le sommet origine de ts les chemins détectés par nCycleDetecteR()
			CycleDetecteR(gG,sDepart,bSansSommetSousConnexe,bColoration,nSousConnexe,bDetailler,&nCycleEnTout,&nCycleCompatible);
		}//si le graphe est connexe,sDepart=1 suffit si bien que la boucle est superflue.
	if (bAfficher)
		Dis(sC5b("Bilan:",sPluriel(nCycleCompatible,"cycle"),"sans sous-connexité","sur",sPluriel(nCycleEnTout,"cycle$ inventorié$")));
}//CycleInventorieR

void CycleRazeR(){
	int nCycle;
	int uS;
	for (nCycle=0; nCycle<knCycleLiM; nCycle++)
		for (uS=1; uS<knSommetLiM; uS++)
			sCyclE[nCycle][uS]=0;
}//CycleRazeR

void CycleTESTER(int iTest){
	//teste le présent module
	int k1Detailler=kV;
	char kcArachnide[]="AB2BC1CD3DE2EA1AF3BG2CH2DI1EJ1FH1HJ2JG3GI1IF2AK1BL2CM3DN1EO2";
	char kcComplet4[]="AB0AC0AD0BC0BD0CD0";
	char kcComplet5[]="AB1AC2AD1AE2BC2BD2BE1CD2CE1DE3";
	char kcComplet60[]="AB0AC0AD0AE0AF0BC0BD0BE0BF0CD0CE0CF0DE0DF0EF0";
	char kcComplet61[]="AB1AC2AD1AE2AF3BC2BD2BE1BF3CD2CE1CF3DE1DF2EF3";
	char kcFaible[]="AB1AC1AG2AI1BC2BH1CD1DE2DI1EF1FG2GH1HI2";
	char kcPetersen5[]="AB2BC1CD3DE2EA1AF3BG2CH2DI1EJ1FH1HJ2JG3GI1IF2";
	char kcPeterpi[]="AB3AE2AG1BC3BH1CD2CI1DJ1EF1FH2FI2GI2GJ2KJ2LI1MG1NH2";
	//char kcPeterpi[]="AB3AE2AG1BC3BH1CD2CI1DJ1EF1FH2FI2GI2GJ2";
	int k1SansSommetSousConnexe=kV;
	Appel0(sC2("CycleTESTER,test n°",sEntier(iTest)));
		switch (iTest) {
			case  4:	CycleEnumereR(kcComplet4,0,k1SansSommetSousConnexe,!k1Detailler);break;//3 cycles sur 7 inventoriés
			case  5:	CycleEnumereR(kcComplet5,0,k1SansSommetSousConnexe,k1Detailler);break;//1 cycle sur 9 inventoriés
			case  6:	CycleEnumereR(kcComplet60,0,k1SansSommetSousConnexe,k1Detailler);break;//80 cycles sur 197 inventoriés
			case  7:	CycleEnumereR(kcComplet61,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 16 inventoriés
			case 10:	CycleEnumereR(kcPetersen5,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 19 inventoriés
			case 11:	CycleEnumereR(kcPetersen5,0,k1SansSommetSousConnexe,k1Detailler);break;//5 cycles sur 19 inventoriés
			case 12:	CycleEnumereR(kcArachnide,5,k1SansSommetSousConnexe,k1Detailler);break;//7 cycles sur 19 inventoriés
			case 13:	CycleEnumereR(kcFaible,0,k1SansSommetSousConnexe,k1Detailler);break;//
			case 14:	ArtereEnumereR(kcPeterpi,4,k1SansSommetSousConnexe,k1Detailler);break;//
			default:break;
		}
	Appel1(sC2("CycleTESTER,test n°",sEntier(iTest)));
}//CycleTESTER	

/*    CycleTESTER,test n°12: tâche en cours...
Graphe généré avant symétrisation, et spécifié avec couleurs: (20 arcs)
    (A,B,r) (A,F,v) (A,K,b) (B,C,b) (B,G,r) (B,L,r) (C,D,v) (C,H,r) (C,M,v) (D,E,r) (D,I,b) (D,N,b) (E,A,b) (E,J,b) (E,O,r) (F,H,b) (G,I,b) (H,J,r) (I,F,r) (J,G,v).
Sous-connexité interdite pour les sommets A à J.
Cycle n° 3 (lgr  8): (C,H,F,I,G,J,E,D,C).
Cycle n° 9 (lgr  8): (B,G,J,H,F,I,D,C,B).
Bilan: 7 cycles exempts de sous-connexité sur 19 cycles inventoriés.
    CycleTESTER,test n°12: tâche terminée.
*/

void SommetListeR(int sSommet,int bVirguler){
	//dédié CycleAfficheR
	if (kbLitteraL) 
		printf("%c",cSommetLitteraL(sSommet));
	else printf("%d",sSommet);
	if (bVirguler)
		printf(",");
}//SommetListeR

char cSommetLitteraL(int sX){
	char cLitteral;
	cLitteral=(bCroit(1,sX,kuMinusculeOffset-1))? 'A'+sX-kuMajusculeOffset : 'a'+sX-kuMinusculeOffset;
	return(cLitteral);
}//cSommetLitteraL

int bSommetSousConnexE(graf gG,int sListe[],int nSousConnexe,int *psSoliton){
	//vrai ssi un sommet de gG n'est plus 2-connexe ds gG\sListe
	int aK;
	int nCardinal;
	int bSousConnexe;
	int nConnexion;
	int sX,sY;
	bSousConnexe=kF;//d
	nCardinal=sListe[0];
	for (sX=1;sX<=nSousConnexe;sX++)
		if (!bVecteurContient(sX,nCardinal,sListe)){
			nConnexion=gG.aHed[sX+1]-gG.aHed[sX];//d
			for (aK=gG.aHed[sX]; aK<gG.aHed[sX+1]; aK++) {
				sY=gG.sSuk[aK];
				if ( bVecteurContient(sY,nCardinal,sListe) )
					nConnexion--;
			}
			if (!bSousConnexe && nConnexion<=1){
				*psSoliton=sX;
				bSousConnexe=kV;
			}
		}
	return(bSousConnexe);
}//bSommetSousConnexE

int bSommetViergE(graf gG,int sOrigine,int sVierge,int *pbCycle){
	// vrai ssi sVierge est un sommet non encore empilé,ie qui ne figure dc pas ds la paternité du sommet de pile sOrigine
	int nDistance=0;
	int bVierge=kV;
	int sX,sY;
	*pbCycle=kV;
	sY=sOrigine;
	do {
		sX=sY;
		sY=gG.sPer[sX];
		bVierge=bVierge && (sY!=sVierge);
		nDistance++;
	} while (bVierge && sY!=0 && gG.sPer[sY]!=sX);
	if (!bVierge)
		*pbCycle=(nDistance>1);//exclut les cycles de lgr 2
	//*pbCycle=kV;
	return(bVierge);
}//bSommetViergE


