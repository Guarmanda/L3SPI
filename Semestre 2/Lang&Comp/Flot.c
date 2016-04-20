#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Flot.h"
//structure de données du graphe courant G
/*const int knArcMaX = 100;
const int knSommetMaX = 10;*/
long zCheminDeCoutMinimalCalculeR(int sSource,int sTrappe,graf *pgG);//O(SA)
void CoutAltereR(int bAjouter,graf *pgG);
void FlotAugmenteR(graf *pgG,int sSource,int sTrappe);

void FlotAfficherParChemiN(graf *pgG,int sSource,int sTrappe,char *sMessage);
int bFlotAmorceR;//dédié FlotAmorceR
int bFlotCalculeR2(graf *pgG,int sSource1,int sTrappe1,int nFlotRequis1,int sSource2,int sTrappe2,int nFlotRequis2);
void FlotMatriceR(graf *pgG);
void FlotPondereR(graf *pgG,int sSource,int sDestination,int nCapaMax,int nCout,int nPrix);
void FlotTesteR2(int nTest);
int bFluxSuivanT(graf *pgG,int sSource,int *psDestination,long *pzCoutTotal);
void SystemeAfficheR(graf *pgG,int sSource,int sTrappe,char cVariable);

void CheminAfficheR(graf *pgG,char *sMessage){
	//énumère les triplets (origine,destination,flot) des arcs de pgG qui écoulent un flot non nul; si bTout, le flot considéré peut être nul.
	int bEncore,aK,nFlot,sX;
	long zCout=0;
	int bFlotNonNul;
	int cPasse;
	Vrai2(bFlotAmorceR,sMessage!=0);
	if (pgG->nArcEnTout>0){
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==1){
				//printf("%s sous la forme (source,cible≤coût) puis (source,cible:flot effectif):\n   ",sMessage);
				//printf("%s sous la forme (source,cible:flot effectif):\n   ",sMessage);
				printf("%s sous la forme (source,cible):\n   ",sMessage);
				if (0)//afficher ts les arcs sous la forme (source,cible≤coût) 
					for (sX=1;bEncore=sX<pgG->nSommetEnTout+1, !bEncore && bLigne(), bEncore;sX++)//bLigne() pr passer à la ligne en fin de boucle
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			}
			for (zCout=0,sX=1;sX<pgG->nSommetEnTout+1;sX++){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if ( nFlot=pgG->nPhi[aK], (nFlot>0) ){
						assert(nFlot==1);
						if (cPasse==1){//afficher l'arc aK car il écoule un flot non nul (ou >=0 si bTout)
							printf("(%d,%d) ",sX,pgG->sSuk[aK]);
							//printf("(%d,%d:%d*%d) ",sX,pgG->sSuk[aK],nFlot,pgG->nCout[aK]);
							if (nFlot>0)
								zCout+=nFlot*pgG->nCout[aK];
						}
						else bFlotNonNul=1;
					}
			}
			if (cPasse==1)
				printf("Coût total: %s.",sPluriel(zCout,"unité"));
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//CheminAfficheR

long zCheminDeCoutMinimalCalculeR(int sSource,int sTrappe,graf *pgG){//O(SA)
	//décrit dans pgG->sPer[] un chemin améliorant de coût minimal s'il en existe;altère les champs sPer,nVal,nAugVal et aArcTo.
	const int kuInfini=9999;
	int aK;
	int aL;
	int sX;
	int sY;
	Vrai3(bCroit(1,sSource,pgG->nSommetEnTout),bCroit(1,sTrappe,pgG->nSommetEnTout),sSource!=sTrappe);
	//initialiser le tableau pgG->sPer à 0 et le tableau pgG->nVal à plus l'infini
		for (sX=1;sX<=pgG->nSommetEnTout+1;sX++)
			pgG->sPer[sX]=0;
		for (sX=1;sX<=pgG->nSommetEnTout+1;sX++)
			pgG->nVal[sX]=kuInfini;
	pgG->nVal[sSource]=0;
	pgG->sPer[sSource]=0;
	pgG->nAugVal[sSource]=kuInfini;
	DequeAllouer(pgG->nSommetEnTout);
		DequeEnfiler(sSource);
		While(pgG->nSommetEnTout*pgG->nArcEnTout);//un multiplicande égal à 1 ne suffit pas
		do {//NB nPhi[] est invariant ds cette routine
			sX=sDequeDefiler();
			//balayer les arcs avant d'origine sX
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if (pgG->nPhi[aK]<pgG->nCapa[aK]){
						sY=pgG->sSuk[aK];//extrémité de aK
						if (pgG->nVal[sY]>pgG->nVal[sX]+pgG->nCout[aK]) {
							pgG->nVal[sY]=pgG->nVal[sX]+pgG->nCout[aK];
							pgG->sPer[sY]=sX;
							pgG->aArcTo[sY]=aK;
							pgG->nAugVal[sY]=yMin(pgG->nAugVal[sX],pgG->nCapa[aK]-pgG->nPhi[aK]);
							DequeEnfiler(sY);//ne fait rien si déjà enfilé
						}
					}
			//balayer les arcs arrière d'extrémité sX
				for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
					if (aL=pgG->aInv[aK],pgG->nPhi[aL]>0){
						sY=pgG->sKus[aK];//origine de aK
						if (pgG->nVal[sY]>pgG->nVal[sX]-pgG->nCout[aL]) {
							pgG->nVal[sY]=pgG->nVal[sX]-pgG->nCout[aL];
							pgG->sPer[sY]=sX;
							pgG->aArcTo[sY]=aL;
							pgG->nAugVal[sY]=yMin(pgG->nAugVal[sX],pgG->nPhi[aL]);
							DequeEnfiler(sY);//ne fait rien si déjà enfilé
						}
					}
		} while (bWhile(!bDequeVide()) );
	DequeAllouer(0);
	return(pgG->nVal[sTrappe]);//à ce point,sPer[sTrappe] aura ou non été mis à jour;si oui, il existe un chemin améliorant de coût minimal
}//zCheminDeCoutMinimalCalculeR

void CoutAltereR(int bAjouter,graf *pgG){
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++)
		if (bAjouter)
			pgG->nCout[aK]+=pgG->nPrix[aK];
		else pgG->nCout[aK]-=pgG->nPrix[aK];
}//CoutAltereR

void FlotAfficher(graf *pgG,int bTout,char *sMessage){
	//énumère les triplets (origine,destination,flot) des arcs de pgG qui écoulent un flot non nul; si bTout, le flot considéré peut être nul.
	int bEncore,aK,nFlot,sX;
	long zCout=0;
	int bFlotNonNul;
	int cPasse;
	Vrai3(bFlotAmorceR,sMessage!=0,bBool(bTout));
	if (pgG->nArcEnTout>0){
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==1){
				//printf("%s sous la forme (source,cible≤coût) puis (source,cible:flot effectif):\n   ",sMessage);
				//printf("%s sous la forme (source,cible:flot effectif):\n   ",sMessage);
				printf("%s sous la forme (source,cible):\n   ",sMessage);
				if (0)//afficher ts les arcs sous la forme (source,cible≤coût) 
					for (sX=1;bEncore=sX<pgG->nSommetEnTout+1, !bEncore && bLigne(), bEncore;sX++)//bLigne() pr passer à la ligne en fin de boucle
						for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
							printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			}
			for (zCout=0,sX=1;sX<pgG->nSommetEnTout+1;sX++){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					if ( nFlot=pgG->nPhi[aK], bTout || (nFlot>0) ){
						assert(bTout || (nFlot==1));
						if (cPasse==1){//afficher l'arc aK car il écoule un flot non nul (ou >=0 si bTout)
							printf("(%d,%d) ",sX,pgG->sSuk[aK]);
							//printf("(%d,%d:%d*%d) ",sX,pgG->sSuk[aK],nFlot,pgG->nCout[aK]);
							if (nFlot>0)
								zCout+=nFlot*pgG->nCout[aK];
						}
						else bFlotNonNul=1;
					}
			}
			if (cPasse==1)
				printf("Coût total: %s.",sPluriel(zCout,"unité"));
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//FlotAfficher

void FlotAfficherParChemiN(graf *pgG,int sSource,int sTrappe,char *sMessage){
	//énumère flot élémentaire par flot élémentaire les triplets (origine,destination) des arcs de pgG qui écoulent un flot non nul.
	int aK,nFlot,sX,sY;
	long zCout=0;
	int bFlotNonNul;
	int nFlux=0;
	int cPasse;
	Vrai3(bFlotAmorceR,bGrapheSommet(pgG,sSource),sMessage!=0);
	if (pgG->nArcEnTout>0) {
		for (bFlotNonNul=0,cPasse=0;cPasse<=bFlotNonNul;cPasse++) {//évaluer bFlotNonNul à la passe 0; si bFlotNonNul est faux, afficher en passe 1
			if (cPasse==0){
				for (zCout=0,sX=1;sX<pgG->nSommetEnTout+1;sX++)
					for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
						if ( nFlot=pgG->nPhi[aK], (nFlot>0) ){
							assert(nFlot==1);
							bFlotNonNul=1;
						}
				}
			else {printf("%s:\n",sMessage);
				//afficher ts les arcs sous la forme (source,cible≤coût) 
					for (zCout=0,aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
						if ( nFlot=pgG->nPhi[aK], (nFlot>0) ){
							assert(nFlot==1);
							nFlux++;
							sX=sSource;
							sY=pgG->sSuk[aK];
							zCout+=pgG->nCout[aK];
							printf("   Chemin n°%d: ",nFlux);
								printf("(%d",sX);
								While(pgG->nSommetEnTout);
								do {
									//printf("%s",sCouple(sX,sY));
									printf(",%d",sY);
									sX=sY;
								} while( bWhile(bFluxSuivanT(pgG,sX,&sY,&zCout)) );
							printf(").\n");
								//printf("(%d,%d≤%d) ",sX,pgG->sSuk[aK],pgG->nCout[aK]);
	
						}
				printf("Coût total: %s.",sPluriel(zCout,"unité"));
			}
		}
		if (!bFlotNonNul)
			printf("%s de valeur nulle.",sMessage);
	} else printf("aucun arc");
	printf("\n");
}//FlotAfficherParChemiN

void FlotAMORCER(){
	//amorce le présent module une fois pour toutes
	bFlotAmorceR=kV;
}//FlotAMORCER

void FlotAugmenteR(graf *pgG,int sSource,int sTrappe){
	//actualise nPhi[] sur le chemin sSource sTrappe
	int nDelta;
	int aK;
	int sX;
	nDelta=pgG->nAugVal[sTrappe];
	sX=sTrappe;
	While(pgG->nSommetEnTout);
	do {
		aK=pgG->aArcTo[sX];
		if (pgG->sSuk[aK]==sX)
			pgG->nPhi[aK]+=nDelta;
		else pgG->nPhi[aK]-=nDelta;
		sX=pgG->sPer[sX];
	} while (bWhile(sX!=sSource) );
}//FlotAugmenteR

int bFlotCalculer(graf *pgG,int sSource,int sTrappe,int nFlotRequis){//O(S2A)
	//calcule et rend dans pgG->nPhi[] le flot zFlotRequis à coût minimal sur pgG,un graphe avec arcs inverses,capacités et coûts initialisés.
	long zCoutTotal;
	int nFlotAtteint;
	int bCalculer,aK,sX;
	int bTrappeAtteinte;
	int zCoutMinimal;
	//Appel0(sC4b("FlotCalculer de la source",sEntier(sSource),"à la trappe",sEntier(sTrappe)));
		Vrai4(bFlotAmorceR,pgG->nArcEnTout>0,pgG->aInv[1]>0,nFlotRequis>=0);
		Vrai3(bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe),sSource!=sTrappe);
		bCalculer=(nFlotRequis>0);
		for (aK=1;aK<=pgG->nArcEnTout;aK++)
			pgG->nPhi[aK]=0;//valeur du flot qui passera ds l'arc aK
		if (bCalculer){
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				bCalculer=bCalculer && (pgG->nCapa[aK]>=0);//capacités unitaires
			for (aK=1;aK<=pgG->nArcEnTout;aK++)
				bCalculer=bCalculer && (pgG->nCout[aK]>=0);//coûts unitaires
			if (bCalculer){
				nFlotAtteint=0;
				zCoutTotal=0;
				While(pgG->nSommetEnTout);
				do {//accroître le flot en ajoutant à chaque étape un flot élémentaire de coût minimal et atteindre si possible le seuil zFlotRequis.
					zCoutMinimal=zCheminDeCoutMinimalCalculeR(sSource,sTrappe,pgG);//O(SA)
					if (bTrappeAtteinte=pgG->sPer[sTrappe]!=0) {
						pgG->nAugVal[sTrappe]=yMin(pgG->nAugVal[sTrappe],nFlotRequis-nFlotAtteint);
						FlotAugmenteR(pgG,sSource,sTrappe);
						nFlotAtteint+=pgG->nAugVal[sTrappe];
						zCoutTotal+=pgG->nAugVal[sTrappe]*zCoutMinimal;
					};
				} while (bWhile(bTrappeAtteinte && (nFlotAtteint<nFlotRequis)) );
			}
		}
	//Appel1(sC4b("FlotCalculer de la source",sEntier(sSource),"à la trappe",sEntier(sTrappe)));
	return(bCalculer);
}//bFlotCalculer

int bFlotCalculeR2(graf *pgG,int sSource1,int sTrappe1,int nFlotRequis1,int sSource2,int sTrappe2,int nFlotRequis2){
	//calcule un biflot de coût minimal sur pgG qui décrit un graphe avec ses arcs inverses,ses capacités et ses deux coûts tous initialisés.
	//Poser x1=y1+y2-b et x2=y1-y2 pour minimiser (c1+c2)y1 + c1-c2)y2 -c1b sc (Ay1+aY2=r1+Ab , Ay1-Ay2=r2 , 0≤y1≤b , 0≤y2≤b) équivaut à minimiser...
	//...(c1+c2)y1 sc (Ay1=1/2(r1+r2+Ab) , Ay2=1/2(r1-r2+Ab) , 0≤y1≤b , 0≤y2≤b) et donc à effectuer les 2 minimisations indépendantes ci-dessous.
	int aK;
	int bFlot1=0;
	int bFlot12=0;
	int bFlot2=0;
	int nPhi1[99];
	int nPhi2[99];
	int sSource;
	int sTrappe;
	Vrai5(bFlotAmorceR,pgG->nArcEnTout>0,pgG->aInv[1]>0,nFlotRequis1>0,nFlotRequis2>0);
	Vrai3(bGrapheSommet(pgG,sSource1),bGrapheSommet(pgG,sTrappe1),sSource1!=sTrappe1);
	Vrai3(bGrapheSommet(pgG,sSource2),bGrapheSommet(pgG,sTrappe2),sSource2!=sTrappe2);
	//Appel0(sC8b("Flot2Calculer de",sEntier(sSource1),"à",sEntier(sTrappe1),"et de",sEntier(sSource2),"à",sEntier(sTrappe2)));
		//1° Minimiser (c1+c2)y1 sc (Ay1=1/2(r1+r2+Ab) , 0≤y1≤b) et sauvegarder les flux dans nPhi1[]
			GrapheSommer(pgG,kV);
				sSource=pgG->nSommetEnTout;
				GrapheArquer(pgG,sSource,sSource1);
				GrapheArquer(pgG,sSource,sSource2);
				GrapheSommer(pgG,kV);
					sTrappe=pgG->nSommetEnTout;
					GrapheArquer(pgG,sTrappe,sTrappe1);
					GrapheArquer(pgG,sTrappe,sTrappe2);
					GrapheSymetriser(pgG);
					FlotPondereR(pgG,sSource,sSource1,1,0,0);
					FlotPondereR(pgG,sSource,sSource2,1,0,0);
					FlotPondereR(pgG,sTrappe,sTrappe1,1,0,0);
					FlotPondereR(pgG,sTrappe,sTrappe2,1,0,0);
					CoutAltereR(1,pgG);//ajoute les nPrix aux nCout pr obtenir (c1+c2)
						bFlot1=bFlotCalculer(pgG,sSource,sTrappe,nFlotRequis1+nFlotRequis2);//initialise et rend pgG->nPhi[]
						if (bFlot1)
							FlotAfficher(pgG,kF,"Flot y1");
						if (bFlot1)
							FlotAfficherParChemiN(pgG,sSource1,sTrappe1,"Flot y1 chemin par chemin");
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi1[aK]=pgG->nPhi[aK];
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi1[aK]=pgG->nPhi[aK];
					CoutAltereR(0,pgG);//restaure les nCout
				GrapheSommer(pgG,kF);
			GrapheSommer(pgG,kF);
/*
		//2° Minimiser (c1-c2)y2 sc (Ay1=1/2(r1-r2+Ab) , 0≤y2≤b) et sauvegarder les flux dans nPhi2[]
			GrapheSommer(pgG,kV);
				sSource=pgG->nSommetEnTout;
				GrapheArquer(pgG,sSource,sSource1);
				GrapheArquer(pgG,sSource,sSource2);
				GrapheSommer(pgG,kV);
					sTrappe=pgG->nSommetEnTout;
					GrapheArquer(pgG,sTrappe,sTrappe1);
					GrapheArquer(pgG,sTrappe,sTrappe2);
					CoutAltereR(0,pgG);//retranche les nPrix aux nCout pr obtenir (c1-c2)
						bFlot2=bFlotCalculer(pgG,sSource,sTrappe,nFlotRequis1+nFlotRequis2);//initialise et rend pgG->nPhi[]
						if (bFlot2)
							FlotAfficher(pgG,kF,"Flot y1");
						if (bFlot2)
							FlotAfficherParChemiN(pgG,sSource1,sTrappe1,"Flot y1 chemin par chemin");
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi2[aK]=pgG->nPhi[aK];
						for (aK=1;aK<=pgG->nArcEnTout;aK++)
							nPhi2[aK]=pgG->nPhi[aK];
					CoutAltereR(1,pgG);//restaure les nCout
				GrapheSommer(pgG,kF);
			GrapheSommer(pgG,kF);
		bFlot12=bFlot1 && bFlot2;
*/
bFlot12=kF;
		if (bFlot12){// Calculer les flots originaux de x1 et x2 à partir de y1 et y2
			// afficher le flux x1
				Titrer("Flot X1");
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					pgG->nPhi[aK]=nPhi1[aK]+nPhi2[aK]-pgG->nCapa[aK];//y1+y2-b
				FlotAfficher(pgG,kF,"Flot x1");
			// afficher le flux x2
				Titrer("Flot X2");
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					pgG->nPhi[aK]=nPhi1[aK]-nPhi2[aK];//y1-y2
				FlotAfficher(pgG,kF,"Flot x2");
				if (1)
					FlotAfficherParChemiN(pgG,sSource2,sTrappe2,"Flot X2 chemin par chemin");
		}
	//Appel1(sC8b("Flot2Calculer de",sEntier(sSource1),"à",sEntier(sTrappe1),"et de",sEntier(sSource2),"à",sEntier(sTrappe2)));
	return(bFlot12);
}//bFlotCalculeR2

void FlotCapaciter(graf *pgG,int sOrigine,int sDestination,int nCapacitehMaximale){
	//attribue la capacité sCapacitehMaximale à l'arc (sOrigine,sDestination) de gG, ou à tous les arcs ssi sOrigine=sDestination=0
	int  bCapaciter,aK;
	Assert4("FlotCapaciter1",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCapacitehMaximale>=0);
	Assert1("FlotCapaciter2",(sOrigine==0) == (sDestination==0));
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nCapa[aK]=nCapacitehMaximale;
		bCapaciter=kV;
		}
	else for (bCapaciter=0,aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
		if (pgG->sSuk[aK]==sDestination){
			pgG->nCapa[aK]=nCapacitehMaximale;
			bCapaciter=kV;
		}
	Assert1("FlotCapaciter3",bCapaciter);		
}//FlotCapaciter

void FlotCouter1(graf *pgG,int sOrigine,int sDestination,int nCout){
	//attribue le coût nCout à pgG->nCout[aK] tel que aK est l'arc (sOrigine,sDestination), ou à tous les arcs ssi sOrigine=sDestination=0 
	int  bCouter1,aK;
	Assert4("FlotCouter1",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCout>=0);
	Assert1("FlotCouter11",(sOrigine==0) == (sDestination==0));
	bCouter1=kF;
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nCout[aK]=nCout;
		bCouter1=kV;
		}
	else {
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
			if (pgG->sSuk[aK]==sDestination){
				pgG->nCout[aK]=nCout;
				bCouter1=kV;
			}
		for (aK=pgG->aHed[sDestination];aK<pgG->aHed[sDestination+1];aK++)
			if (pgG->sSuk[aK]==sOrigine){
				pgG->nCout[aK]=nCout;
				bCouter1=kV;
			}
		}
	Assert1("FlotCouter1",bCouter1);		
}//FlotCouter1

void FlotCouter2(graf *pgG,int sOrigine,int sDestination,int nCout){
	//attribue le coût nCout à pgG->nPrix[aK] tel que aK est l'arc (sOrigine,sDestination), ou à tous les arcs ssi sOrigine=sDestination=0 
	int  bCouter2,aK;
	Assert4("FlotCouter2",bFlotAmorceR,bCroit(0,sOrigine,pgG->nSommetEnTout),bCroit(0,sDestination,pgG->nSommetEnTout),nCout>=0);
	Assert1("FlotCouter21",(sOrigine==0) == (sDestination==0));
	bCouter2=kF;
	if ((sOrigine==0) && (sDestination==0)){
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->nPrix[aK]=nCout;
		bCouter2=kV;
		}
	else {
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
			if (pgG->sSuk[aK]==sDestination){
				pgG->nPrix[aK]=nCout;
				bCouter2=kV;
			}
		for (aK=pgG->aHed[sDestination];aK<pgG->aHed[sDestination+1];aK++)
			if (pgG->sSuk[aK]==sOrigine){
				pgG->nPrix[aK]=nCout;
				bCouter2=kV;
			}
		}
	Assert1("FlotCouter2",bCouter2);		
}//FlotCouter2

void FlotINITIALISER(){//O(?)
	//relance le présent module
	Vrai(bFlotAmorceR);
}//FlotINITIALISER

void FlotMatriceR(graf *pgG){
	//affiche pgG sous forme matricielle
	int uC;
	int aK;
	int bArc[1+pgG->nSommetEnTout];
	int sX;
	int sY;
	Vrai(bFlotAmorceR);
	assert(bGrapheSimple(pgG));
	printf("Matrice du graphe direct (sommet source en ligne,sommet destination en colonne):\n");
		for (uC=0;uC<=pgG->nSommetEnTout;uC++)
			printf("%3d",uC);//colonne
		printf("\n");
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (uC=1;uC<=pgG->nSommetEnTout;uC++)
				bArc[uC]=0;
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				bArc[sY]++;
			}
			//afficher la ligne courante
				printf("%3d",sX);//ligne
				for (uC=1;uC<=pgG->nSommetEnTout;uC++)
					printf("%3d",bVrai(bArc[uC]));
				printf("\n");
		}
}//FlotMatriceR

void FlotPondereR(graf *pgG,int sSource,int sDestination,int nCapaMax,int nCout,int nPrix){
	FlotCapaciter(pgG,sSource,sDestination,nCapaMax);
	FlotCapaciter(pgG,sDestination,sSource,nCapaMax);
	FlotCouter1(pgG,sSource,sDestination,nCout);
	FlotCouter1(pgG,sDestination,sSource,nCout);
	FlotCouter2(pgG,sSource,sDestination,nPrix);
	FlotCouter2(pgG,sDestination,sSource,nPrix);
}//FlotPondereR

void FlotTESTER(int iTest){
	graf *pgG;
	int nSommet=0;
	int sSource=1;//d
	int sTrappe=8;//d
	const long kzFlotRequis=1;
	Appel0(sC2("FlotTESTER,test n°",sEntier(iTest)));
		switch (iTest) {
		case 1:	 nSommet=8;break;
		case 2:	 nSommet=9;break;
		case 3:	 nSommet=5;sSource=3;sTrappe=1;break;
		case 4:	 nSommet=6;sSource=5;sTrappe=6;break;
		default: FlotTesteR2(iTest);break;
		}
		if (nSommet!=0){
			GrapheCreer( nSommet,&pgG );
		        //GrapheArquer(pgG, 1, 5);
				GrapheAfficher(pgG,sC4b("Graphe avec",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
				if (iTest==3)
					pgG->nCout[4]=20;
				if (iTest==4){
					FlotCouter1(pgG,5,2,52);FlotCouter1(pgG,5,3,53);FlotCouter1(pgG,5,4,54);FlotCouter1(pgG,5,6,55);FlotCouter1(pgG,5,1,10);}
				if (bFlotCalculer(pgG,sSource,sTrappe,kzFlotRequis))
					FlotAfficher(pgG,0,"flot résultant");
			GrapheCreer( 0,&pgG );
		}
	Appel1(sC2("FlotTESTER,test n°",sEntier(iTest)));
}//FlotTESTER

void FlotTesteR2(int nTest){
	#define kuArcEnTout1 14
	#define kuArcEnTout3 18
	#define kzFlotRequis1 1
	#define kzFlotRequis2 1
	#define kuChemin1Lg 6
	#define kuChemin2Lg 6
	#define kuCoutProhibitif 9999
	int nArc10[1+kuArcEnTout1]={-1,1,1, 2, 3,3,3, 4,4, 5, 6,6, 7, 8, 9};//NB sommet origine de l'arc
	int nArc11[1+kuArcEnTout1]={-1,2,3, 4, 4,5,6, 6,9, 7, 8,9, 9,10,10};//NB sommet destination de l'arc
	int nArc30[1+kuArcEnTout3]={-1,1,1,1, 2,2,2, 3,3,3, 4,4,4, 5,5,5, 6,6,6};//NB sommet origine de l'arc
	int nArc31[1+kuArcEnTout3]={-1,4,5,6, 4,5,6, 4,5,6, 7,8,9, 7,8,9, 7,8,9};//NB sommet destination de l'arc
	int sChemin1[1+kuChemin1Lg]={-1,1,3,5,7,9,10};
	int sChemin2[1+kuChemin2Lg]={-1,1,2,4,6,8,10};
	int bEulerien;
	graf *pgG;
	int uS;
	int sSource1=1;
	int sSource2=1;
	int sTrappe1=1;
	int sTrappe2=1;
	switch (nTest) {
	case 11://1 nid d'abeille et demi, 2 sources identiques, 2 trappes identiques
			GrapheCreer2(&pgG,10,kuArcEnTout1,&nArc10[0],&nArc11[0]);
			GraphePonderer(pgG);
			GrapheAfficher(pgG,sC2b("GrapheSymetriser AVANT:",sPluriel(pgG->nArcEnTout,"arc")));
			GrapheSymetriser(pgG);
			GrapheAfficher(pgG,sC2b("GrapheSymetriser APRES:",sPluriel(pgG->nArcEnTout,"arc")));
			FlotCapaciter(pgG,0,0,1);
			FlotCouter1(pgG,0,0,2);//couts pr x1
			FlotCouter2(pgG,0,0,1);//prix pr x2
			//le coût du chemin sChemin1 est trop élevé pour le flot 1 représenté par la variable x1
				for (uS=1; uS<kuChemin1Lg; uS++)
					FlotCouter1(pgG,sChemin1[uS],sChemin1[uS+1],50);
			//le coût du chemin sChemin2 est trop élevé pour le flot 2 représenté par la variable x2
				for (uS=1; uS<kuChemin2Lg; uS++)
					FlotCouter2(pgG,sChemin2[uS],sChemin2[uS+1],50);
			//dissuader les flots de passer par les aretes ci-dessous qui n'ont été ajoutées que pr rendre le graphe eulérien 
				FlotCouter1(pgG,3,6,kuCoutProhibitif);
				FlotCouter2(pgG,3,6,kuCoutProhibitif);
				FlotCouter1(pgG,4,9,kuCoutProhibitif);
				FlotCouter2(pgG,4,9,kuCoutProhibitif);
			sSource1=1;
			sTrappe1=10;
			break;
	case 12://graphe étagé, 2 sources identiques, 2 trappes identiques
			GrapheCreer2(&pgG,3*3,kuArcEnTout3,&nArc30[0],&nArc31[0]);
			GrapheDedoubler(pgG);
			GraphePolariser(pgG,&sSource1,&sTrappe1);
			break;
	default:assert(1<0);
			break;
	}
	Vrai3(bGrapheSimple(pgG),bGrapheSommet(pgG,sSource1),bGrapheSommet(pgG,sTrappe1));
	sSource2=sSource1;
	sTrappe2=sTrappe1;
	GrapheInverser(pgG);
	//GrapheAfficher(pgG,"Graphe dédoublé");
	bEulerien=bGrapheEulerien(pgG,sSource1,sTrappe1);
	sss("Le graphe final",sEst(bEulerien),"eulérien.");
//bEulerien=kF;
	if (bEulerien){
		//GrapheAfficher3(pgG,"Flot2TesteR");
		//FlotMatriceR(pgG);
		//SystemeAfficheR(pgG,sSource1,sTrappe1,'u');
		//SystemeAfficheR(pgG,sSource2,sTrappe2,'v');
		bFlotCalculeR2(pgG,sSource1,sTrappe1,kzFlotRequis1,sSource2,sTrappe2,kzFlotRequis2);
	}
	GrapheCreer(0,&pgG);
}//Flot2TesteR

int bFluxSuivanT(graf *pgG,int sSource,int *psDestination,long *pzCoutTotal){
	//rend le sommet destination qui transmet le flux élémentaire depuis sSource, ssi il existe un tel flux
	int nFlot;
	int aK;
	int bSuivant=kF;
	for (aK=pgG->aHed[sSource];aK<pgG->aHed[sSource+1];aK++)
		if ( nFlot=pgG->nPhi[aK], nFlot>0 ){
			bSuivant=kV;
			assert(nFlot==1);
			*pzCoutTotal+=pgG->nCout[aK];
			*psDestination=pgG->sSuk[aK];
		}
	return(bSuivant);
}//bFluxSuivanT

void SystemeAfficheR(graf *pgG,int sSource,int sTrappe,char cVariable){
	//affiche le système d'équations du flot dans pgG de demande (sSource1,sTrappe1) si flot simple,et cplétée par (sSource2,sTrappe2) si biflot
	int uC;
	int aK;
	int aL;
	int tArc[1+pgG->nArcEnTout];
	int sX;
	Vrai2(bFlotAmorceR,pgG!=0);
	assert(bGrapheSimple(pgG));
	GrapheInverser(pgG);//mm si déjà fait
	Vrai2(bGrapheSommet(pgG,sSource),bGrapheSommet(pgG,sTrappe));
	printf("Système d'équations associé au flot de demande %s",sCouple(sSource,sTrappe));
	printf(",équations sommets 1 à %d:\n",pgG->nSommetEnTout);
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			//arcs entrants et sortants:>0 si sortants,<0 si sortants, et nuls si non incidents à sX
				for (aK=1;aK<=pgG->nArcEnTout;aK++)
					tArc[aK]=0;
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					tArc[aK]=+1;
				for (aL=pgG->aDeh[sX];aL<pgG->aDeh[sX+1];aL++){
					aK=pgG->aInv[aL];
					tArc[aK]=-1;//NB vu bGrapheSimple,un arc est soit entrant soit sortant,dc tArc[aK]=-1 n'écrasera pas un tArc[aK]=-+1
				}
			//terme droit
				tArc[0]=bVrai(sX==sSource) - bVrai(sX==sTrappe);
			//afficher la ligne courante dédiée à sX
				printf("%3d ",sX);
				for (uC=1;uC<=pgG->nArcEnTout;uC++)
					if (tArc[uC]!=0)
						printf("%s%c%d",sSigne(tArc[uC]),cVariable,uC);
					else printf("   %s",sChoix0(uC>9," "));
				printf(" = %2d",tArc[0]);//terme droit
				printf("\n");
		}
}//SystemeAfficheR
