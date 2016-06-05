#include "Outil.h"
#define k1BitsDistincts 2
#define knLigneMaX 4
#define knColonneMaX 8*knLigneMaX
#define knPremierMaX 1000
typedef struct{
	int nLigne;
	int Mat[1+knLigneMaX][1+knLigneMaX];//pas knColonneMaX,dédié nDuoCompteR()
}eMatricE;

int bMatriceAmorceR;
int bMatriceOuvertE;
int abPremieR[1+knPremierMaX];

void ComplexitehAfficheR(long zBarre);
void ComplexitehCalculeR(float fTempsMoyen);
void ComplexitehPreciseR(int nDimension,long zBarre);
void DecomposE(int nDecomposota);
void DecomposeR(int nDecomposota);
void DiviseurS(int nDivisota,int uPile[]);
int nDuoCompteR(int bVoir,eMatricE *pmA,int *pnDuo,int *pnCopie,int *pnRecopie);
void DuoDecompteR(long zDecompteMaximal);
void DuoDenombreR();
int nDuoEstimeR(eMatricE *pmA,int uFois);
void DuoMaximiseR();
void DuoMinimiseR();
void ListeVoiR(int uListe[]);
void MatriceAlloueR(eMatricE **ppmA);
void MatriceBandeR(int iBande,eMatricE **ppmC);
void MatriceBiaiseR(int iBande,eMatricE **ppmC);
void MatriceConfigureR(long zConfigurationVoulue,eMatricE **ppmC);
void MatriceConstitueR(long zConfigurationVoulue,eMatricE **ppmC);
void MatriceCulminer(int uCulminant,eMatricE **ppmC);
int nMatriceCulmineR(eMatricE *pmC);
long zMatriceCulminerAuMieuX(int uCulminant,eMatricE *pmC);
void MatriceFoisseR(int iFois,eMatricE **ppmC);
void MatriceIdentiteR(eMatricE **ppmC);
void MatriceModuleR(int uModulo,eMatricE **ppmC);
long zMatriceMultiplieR(eMatricE *pmA,eMatricE *pmB,eMatricE **ppmC);
void MatriceRazeR(eMatricE **ppmA);
int nMatriceRempliE(eMatricE *pmA);
float fMatriceRempliR(int bDoublonPossible,int uEffectif,eMatricE **ppmA);
int bMatriceVidE(eMatricE *pmA);
void MatriceVoir(char *sMessage,eMatricE *pmA);
void MatriceVoirSouS(int bSous,char *sMessage,eMatricE *pmA);
void ModuloParFibonnaccI();
void PpcmOptimalExhibeR();
void PremierTabuleR();
void PremierVoiR();

void ComplexitehAfficheR(long zBarre){
	float fExposant;
	if (0)
		si("zBarre",zBarre);
	fExposant=rLog(zBarre*knLigneMaX)/rLog(knLigneMaX);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité:N**%3.4f au pire.\n",fExposant);
}//ComplexitehAfficheR

void ComplexitehCalculeR(float fTempsMoyen){
	float fExposant;
	fExposant=rLog(fTempsMoyen*knLigneMaX)/rLog(knLigneMaX);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité moyenne:N**%3.4f.\n",fExposant);
}//ComplexitehCalculeR

void ComplexitehPreciseR(int nDimension,long zBarre){
	float fExposant;
	if (0)
		si("zBarre",zBarre);
	fExposant=rLog(zBarre*nDimension)/rLog(nDimension);// car N**X = zBarre => X=log(zBarre)/log(N)
	if (fExposant<0*2.0)
		fExposant=2.0;
	printf("Complexité:N**%3.4f au pire.\n",fExposant);
}//ComplexitehPreciseR

void DecomposE(int nDecomposota){
	int uN,nReste;
	//printf("nDecomposota=%d\n",nDecomposota);
	for (nReste=1,uN=2;(uN<=nDecomposota) &&(nReste!=0);uN++){
		nReste=nDecomposota%uN;
		if (nReste==0){
			printf("%d",uN);
			if (uN<nDecomposota)
				printf(".",uN);
			DecomposE(nDecomposota/uN);
		}
	}
}//DecomposE

void DecomposeR(int nDecomposota){
	Assert1("DecomposeR",bCroit(1,nDecomposota,1e3));
	printf("%d=",nDecomposota);
		if (nDecomposota>1)
			DecomposE(nDecomposota);
		else printf("%d",nDecomposota);
	printf(".\n");
}//DecomposeR

void DiviseurS(int nDivisota,int uPile[]){
	//empile ds uPile[] les diviseurs stricts de nDivisota,ie ]1,nDivisota[,en ordre croissant,avec le plus petit diviseur en fond de pile (index 1). 
	int upIndex,uN,nReste;
	Assert1("DiviseurS",bCroit(1,nDivisota,1e3));
	for (upIndex=0,uN=2;uN<nDivisota;uN++){
		nReste=nDivisota%uN;
		if (nReste==0){
			uPile[++upIndex]=uN;
		}
	}
	uPile[0]=upIndex;
}//DiviseurS

int nDuoCompteR(int bVoir,eMatricE *pmA,int *pnDuo,int *pnCopie,int *pnRecopie){
	//rend le nombre minimum de duos de 1 distincts ds *pmA. Deux duos identiques situés sur deux lignes distinctes ne comptent que pour 1.
	int uC,uD,uL,nCmax,nDmax,nDuoMajeur,nEtape,nSingleton;
	int nColonne;
	int nDecompter,nDecompter0;
	int nDuau;
	int bDuo=kF;
	int nDuo[1+knColonneMaX][1+knColonneMaX];
	int nMatrice[1+knLigneMaX][1+knColonneMaX];
	int nPasse;
	int bVide;
	//nMatrice[][]:=(*ppmA)->Mat[][]
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				nMatrice[uL][uC]=0;
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knLigneMaX;uC++)
				nMatrice[uL][uC]=-pmA->Mat[uL][uC];//dc négatif
	//nDuo[][]=0
		for (uL=1;uL<=knColonneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				nDuo[uL][uC]=0;
	//nDuo[uL][0]=nbre de 1 ds nMatrice[uL][]
		for (uL=1;uL<=knLigneMaX;uL++)
			for (nDuo[uL][0]=0,uC=1;uC<=knLigneMaX;uC++)
				if (nMatrice[uL][uC]==1)
					nDuo[uL][0]++;
	nPasse=0;
	nEtape=0;
	nDecompter=0;
	do{
		nEtape++;
		nDecompter0=nDecompter;
		do{
			nPasse++;
			if (0)
				MatriceVoir(sC2("Passe n°",sEntier(nPasse)),pmA);
			if (0){
				for (uL=1;uL<=knLigneMaX;uL++){
					for (uC=1;uC<=knColonneMaX;uC++)
						printf(" %2d",nMatrice[uL][uC]);
					printf("\n");
				}
			printf("\n");
			}
			//nDuo[uC][uD]=k ssi k lignes contiennent un duo de valeurs nEtape,avec un nEtape en colonne uC et un autre en colonne uD
				for (uC=1;uC<=knColonneMaX;uC++)
					for (uD=1;uD<=knColonneMaX;uD++)
						nDuo[uC][uD]=0;
				nDuau=0;//a
				for (uL=1;uL<=knLigneMaX;uL++)
					for (uC=1;uC<=knColonneMaX;uC++)
						if (abs(nMatrice[uL][uC])==nEtape)
							for (uD=uC+1;uD<=knColonneMaX;uD++)
								if (abs(nMatrice[uL][uD])==nEtape){
									(nDuo[uC][uD])++;
									nDuau++;
								}
			if (bVoir && (nPasse>=1))
				si("Nb de duos vus",nDuau);
			//nCmax,nDmax mémorise les numéros de colonnes qui ciblent le (un) duo majeur, ie rencontré sur le plus grand nombre de lignes
				nCmax=0;
				nDmax=0;
				nDuoMajeur=0;//d
				for (uC=1;uC<=knColonneMaX;uC++)
					for (uD=1;uD<=knColonneMaX;uD++)
						if (nDuoMajeur<nDuo[uC][uD]){
							nDuoMajeur=nDuo[uC][uD];
							nCmax=uC;
							nDmax=uD;
						}
				bDuo=(nDuoMajeur>0);
				if (bDuo){
					//nColonne:=rg première colonne entièrt vide de nMatrice
						for (nColonne=0,uC=1;uC<=knColonneMaX && nColonne==0;uC++){
							bVide=kV;
							for (uL=1;uL<=knLigneMaX;uL++)
								bVide=bVide && nMatrice[uL][uC]==0;
							if (bVide)
								nColonne=uC;
						}
					Assert1("nDuoCompteR",bCroit(1,nColonne,knColonneMaX));//si assertion fausse,augmenter knColonneMaX.
					if (0)
						siii("nCmax,nDmax et nColonne (ie nouvelle colonne attribuée)",nCmax,nDmax,nColonne);
					for (uL=1;uL<=knLigneMaX;uL++)
						if (abs(nMatrice[uL][nCmax])==nEtape && abs(nMatrice[uL][nDmax])==nEtape){
							nMatrice[uL][nCmax]=0;//le premier terme du duo disparaît
							nMatrice[uL][nDmax]=0;//le second terme du duo disparaît
							nMatrice[uL][nColonne]=abs(nEtape)+1;//un futur opérande est créé
						}
					nDecompter++;
				}
		}while(bDuo);
		//nMatrice[uL][uC]=nValeur+1 si nMatrice[uL][uC] est non nul;dc ts les opérandes non nuls ont la même valeur,au signe près,conservé
		for (uL=1;uL<=knLigneMaX;uL++)
			for (uC=1;uC<=knColonneMaX;uC++)
				if (abs(nMatrice[uL][uC])==nEtape)
					nMatrice[uL][uC]=muSigne(nMatrice[uL][uC]<0,nEtape+1);
	} while(nDecompter0<nDecompter);
	if (bVoir)
		MatriceVoir(sC2("Passe n°",sEntier(nPasse)),pmA);
	//*pnRecopie:=somme sur chaque colonne des bits isolés de résultats de duos, moins 1
		for (*pnRecopie=0,uC=1;uC<=knColonneMaX;uC++){
			nSingleton=0;
			for (uL=1;uL<=knLigneMaX;uL++)
				if (nMatrice[uL][uC]>nEtape)//>0, donc addition de 2 opérandes qui constituent un duo
					nSingleton++;
			if (nSingleton>1)
				(*pnRecopie)+=nSingleton-1;
		}
	//*pnCopie:=somme sur chaque colonne des bits isolés d'opérandes jamais évalués
		for (*pnCopie=0,uC=1;uC<=knColonneMaX;uC++){
			nSingleton=0;
			for (uL=1;uL<=knLigneMaX;uL++)
				if (nMatrice[uL][uC]<-nEtape)//opérande jamais évalué
					nSingleton++;
			(*pnCopie)+=nSingleton;
		}
	/*//nSingleton:=nb de sommes par ligne
		nSingleton=0;
		for (uL=1;uL<=knLigneMaX;uL++){
			nSingleton+=(nDuo[uL][0]+1)/2;
			si("uL",(nDuo[uL][0]+1)/2);
		}*/
	*pnDuo=nDecompter;
	return(*pnDuo+*pnCopie+*pnRecopie);
}//nDuoCompteR

void DuoDecompteR(long zDecompteMaximal){
	//décompte aléatoirt le nombre max de duos ds une matrice de densité 0.5 ds le coté est un multiple de 4; affiche la complexité pire cas
	eMatricE *pmA;
	int nBit,nCompte;
	int aLigne[1+knLigneMaX];
	int nC,nCompteMax,nDuo,nCopie,nRecopie,nPlace;
	int k1Voir=kV;
	long zFois;
	MatriceAlloueR(&pmA);
	for (nCompteMax=0,zFois=zDecompteMaximal;zFois>0;zFois--){
		//aLigne[]:=knLigneMaX/2 bits placés aléatoirt,0 ailleurs
			for (nC=1;nC<=knLigneMaX;nC++)
				aLigne[nC]=0;
			for (nC=knLigneMaX;nC>knLigneMaX/2;nC--){
				nPlace=uHasard(nC);
				for (nBit=knLigneMaX;nBit>0;nBit--){
					if (aLigne[nBit]==0){
						nPlace--;
						if (nPlace==0){
							aLigne[nBit]=1;
							nBit=0;
						}
					}
				}
			}
		//VecteurVoir("aLigne",aLigne,1,knLigneMaX);
		if (zFois%kE3==0){
			si("zFois",zFois);
			ComplexitehAfficheR(nCompteMax);
		}
		//remplir pmA conformément à aLigne[] et compter les duos
			MatriceRazeR(&pmA);
			for (nBit=0,nC=1;nC<=knLigneMaX;nC++)
				if (aLigne[nC]==1){
					nBit++;
					MatriceBiaiseR(nC,&pmA);
				}
			Assert1("DuoDecompteR",nBit<knLigneMaX);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			if (nCompteMax<nCompte || zFois==0){
				nCompteMax=nCompte;
				MatriceVoir("DuoDecompteR",pmA);
				if (1)
					siii("Duos,copies et recopies",nDuo,nCopie,nRecopie);
				ComplexitehAfficheR(nCompte);
			}
	}
	// N=100: Duos,copies et recopies:2134,    0,    0. Complexité:N**2.6646 au pire.
}//DuoDecompteR

void DuoDenombreR(){
	//compte le nombre max de duos ds une matrice biaisée de densité 0.5 ou moins de coté 4N ; affiche complexité pire cas et moyenne
	eMatricE *pmA;
	int nBit,nCompte;
	int nC,nCompteMax,nDuo,nCopie,nRecopie;
	int k1Voir=kV;
	long zComptage,zCompte,zReste,zVect,zVect0,zVect1,zVectMax;
	MatriceAlloueR(&pmA);
	zVect1=zPuissance(2,knLigneMaX)-1;
	zVect0=(knLigneMaX>24)? 0:0;
	s(sC2("zVect1=",sPar3(zVect1)));
	for (zCompte=zComptage=nCompteMax=0,zVectMax=0,zVect=zVect1;zVect>=zVect0;zVect--){
		zReste=(zVect==zVect0)? zVectMax: zVect;
		for (nBit=0,nC=0;nC<=knLigneMaX;nC++){
			if (zReste%2==1)
				nBit++;
			zReste=zReste/2;
		}
		if (nBit<=knLigneMaX/2){
			MatriceRazeR(&pmA);
			zReste=(zVect==zVect0)? zVectMax: zVect;
			if (zReste%kE3==0){
				si("zReste",zReste);
				ComplexitehAfficheR(nCompteMax);
			}
			for (nC=0;nC<=knLigneMaX;nC++){
				if (zReste%2==1)
					MatriceBiaiseR(nC,&pmA);
				zReste=zReste/2;
			};
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			if (zVect>0){
				//si("nCompte",nCompte);
				zCompte+=nCompte;
				zComptage++;
			}
			if (nCompteMax<nCompte || zVect==zVect0){
				nCompteMax=nCompte;
				zVectMax=zVect;
				MatriceVoir("DuoDenombreR",pmA);
				if (1)
					siii("Duos,copies et recopies",nDuo,nCopie,nRecopie);
				ComplexitehAfficheR(nCompte);
				//zVect=zVect0;// *****************
				//s("Dhhhhhhhhhhh");
			}
		}
	}
	si("zComptage",zComptage);
	si("zCompte",zCompte);
	sr("zCompte moyen",(zCompte*1.0)/zComptage);
	ComplexitehCalculeR((zCompte*1.0)/zComptage);  //moyenne: N=4:2.00   N=8:2.26   N=12:2.40   N=16:2.47
/*
    1    0    0    0
    0    1    0    0
    0    0    1    0
    0    0    0    1
Complexité pr N=4:N**2.00 au pire.Duos,copies et recopies:  0,    4,    0.
    0    0    1    0    1    0    1    1
    1    0    0    1    0    1    0    1
    1    1    0    0    1    0    1    0
    0    1    1    0    0    1    0    1
    1    0    1    1    0    0    1    0
    0    1    0    1    1    0    0    1
    1    0    1    0    1    1    0    0
    0    1    0    1    0    1    1    0
Complexité pr N=8:N**2.44 au pire.Duos,copies et recopies:  20,    0,    0.
    0    0    1    0    0    0    1    0    1    1    1    1
    1    0    0    1    0    0    0    1    0    1    1    1
    1    1    0    0    1    0    0    0    1    0    1    1
    1    1    1    0    0    1    0    0    0    1    0    1
    1    1    1    1    0    0    1    0    0    0    1    0
    0    1    1    1    1    0    0    1    0    0    0    1
    1    0    1    1    1    1    0    0    1    0    0    0
    0    1    0    1    1    1    1    0    0    1    0    0
    0    0    1    0    1    1    1    1    0    0    1    0
    0    0    0    1    0    1    1    1    1    0    0    1
    1    0    0    0    1    0    1    1    1    1    0    0
    0    1    0    0    0    1    0    1    1    1    1    0
Complexité pr N=12:N**2.53 au pire.Duos,copies et recopies:  45,    0,    0.
    0    0    0    0    1    0    1    0    1    1    0    0    1    1    1    1
    1    0    0    0    0    1    0    1    0    1    1    0    0    1    1    1
    1    1    0    0    0    0    1    0    1    0    1    1    0    0    1    1
    1    1    1    0    0    0    0    1    0    1    0    1    1    0    0    1
    1    1    1    1    0    0    0    0    1    0    1    0    1    1    0    0
    0    1    1    1    1    0    0    0    0    1    0    1    0    1    1    0
    0    0    1    1    1    1    0    0    0    0    1    0    1    0    1    1
    1    0    0    1    1    1    1    0    0    0    0    1    0    1    0    1
    1    1    0    0    1    1    1    1    0    0    0    0    1    0    1    0
    0    1    1    0    0    1    1    1    1    0    0    0    0    1    0    1
    1    0    1    1    0    0    1    1    1    1    0    0    0    0    1    0
    0    1    0    1    1    0    0    1    1    1    1    0    0    0    0    1
    1    0    1    0    1    1    0    0    1    1    1    1    0    0    0    0
    0    1    0    1    0    1    1    0    0    1    1    1    1    0    0    0
    0    0    1    0    1    0    1    1    0    0    1    1    1    1    0    0
    0    0    0    1    0    1    0    1    1    0    0    1    1    1    1    0
Complexité pr N=16:N**2.58 au pire.Duos,copies et recopies:  81,    0,    0.
    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1
    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1
    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1
    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1
    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1
    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1    0
    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0    1
    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0    0
    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1    0
    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1    1
    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1    1
    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0    1
    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0    0
    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0    0
    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0    0
    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0    0
    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0    0
    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1    0
    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0    1
    1    0    0    0    0    0    0    1    1    1    0    0    1    0    1    1    1    1    1    0
Complexité pr N=20:N**2.60 au pire.Duos,copies et recopies: 121,    0,    0.
    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1
    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1
    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1
    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1
    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0
    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1
    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1
    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0
    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0
    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0    1
    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0    0
    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1    0
    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0    1
    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0    0
    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0    0
    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1    0
    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1    1
    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1    1
    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0    1
    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0    0
    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0    0
    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1    0
    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0    1
    1    0    0    0    1    1    1    0    0    0    1    0    0    1    0    0    1    1    0    1    1    1    1    0
Complexité pr N=24:N**2.62 au pire.Duos,copies et recopies: 172,    0,    0.
*/
}//DuoDenombreR 

int nDuoEstimeR(eMatricE *pmA,int uFois){
	//rend une estiMation statistique de la complexité en pire cas du nombre de duos à sommer pour multiplier deux Matrices 
	int uBitat;
	int nAccumulationMax;
	int k1Doublons=k1BitsDistincts;
	float fDensiteh;
	float fDensitehMax;
	int nCompte,nDuo;
	int uF;
	int nCopie;
	int nRecopie;
	int k1Voir=kV;
	nAccumulationMax=0;
	printf("Mesures sur %s aléatoirement (dimensions:%dx%d).\n",sPluriel(uFois,"Matrice$ de bits remplie$"),pmA->nLigne,pmA->nLigne);
	//estimer kuFois fois et en déduire zDuoMax ds le pire cas
		for (fDensitehMax=0.0,uF=1;uF<=uFois;uF++){
			MatriceRazeR(&pmA);
			uBitat=knLigneMaX*knLigneMaX;
			fDensiteh=fMatriceRempliR(k1Doublons,uBitat,&pmA);//pose uBitat bits distincts ou non selon k1Doublons
			if (fDensiteh>10)
				sr("Densité max courante",fDensiteh);
			if (fDensiteh>=0.0)
				MatriceVoir(sC3("Matrice n°",sEntier(uF),":"),pmA);
			fDensitehMax=rSup(fDensitehMax,fDensiteh);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//à chaq duo de la multipliante A correspond ds la multipliée B 1 somMation de lignes.
			if (1)
				siii("Duos,copies et recopies",nDuo,nCopie,nRecopie);
			if (0)
				MatriceVoir("Matrice originale:",pmA);
			if (nCompte>nAccumulationMax)
				printf("Matrice %d/%d: %s.\n",uFois-uF+1,uFois,sPluriel(nCompte,"accumulation$ en tout"));
			nAccumulationMax=ySup(nAccumulationMax,nCompte);
		}
	//sr("Complexité au pire",2+nDecompteMax/pow(knLigneMaX,2));
	printf("Dans le pire cas, accumulations/somMations de lignes avec algo naïf: %d/%d.\n",nAccumulationMax,(knLigneMaX-1)*knLigneMaX);
	//nDecompteMax=knLigneMaX*knLigneMaX;
	return(nAccumulationMax);
}//nDuoEstimeR

void DuoMaximiseR(){
	//sélectionne et affiche pire la matrice multipliante pr la multiplication par duos ainsi que la complexité algorithmique ds ce pire cas.
	eMatricE *pmA;
	long zCas,zCasInitial,zCasMax,zCasPire;
	int uBitat,nCompte,nComptePire,nCopie,nDuo,nDuoPire,bCasPire,uPeriode,nRecopie,bVoir;
	int k1Voir=kV;
	uBitat=knLigneMaX*(knLigneMaX-1);//la matrice contient uBitat bits
	zCasMax=2*zPuissance(2,uBitat)-1;//soit zCasMax configuration binaires à envisager
	uPeriode=zPuissance(10,yInf(knLigneMaX,6));
	printf("DuoMaximiseR: %s configurations à examiner (knLigneMaX=%d,uPeriode=%d).\n",sPar3(zCasMax),knLigneMaX,uPeriode);
	MatriceAlloueR(&pmA);
	zCasInitial=257924799;
	zCasInitial=zCasMax;
	for (nComptePire=0,nDuoPire=0,zCas=zCasInitial;zCas>=0;zCas--){
		MatriceConstitueR(zCas,&pmA);
		//MatriceVoir(sC3("Matrice ",sEntier(zCas),":"),pmA);
		nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
		bCasPire=(nCompte>nComptePire || ((nCompte==nComptePire) && nDuo>nDuoPire));//à compte égal, retenir le cas du pire nombre de duos (discutable)
		if (bCasPire){
			zCasPire=zCas;
			nDuoPire=nDuo;
			nComptePire=nCompte;
		}
		bVoir=bCasPire || (zCas>0 && zCas%uPeriode==0) || zCas==zCasMax;
		//bVoir=kF;
		if (bVoir){
			MatriceConstitueR(zCasPire,&pmA);
			MatriceVoir("Matrice de poids maximal:",pmA);
			nCompte=nDuoCompteR(!k1Voir,pmA,&nDuo,&nCopie,&nRecopie);//1 duo de la multipliante A => 1 sommation de lignes ds la multipliée B.
			printf("nCompte (nDuo+nCopie+nRecopie)/zCasPire/Reste: %d (%d+%d+%d) %9ld %9ld\n",nComptePire,nDuo,nCopie,nRecopie,zCasPire,zCasMax-zCas);
			ComplexitehAfficheR(nCompte);
		}
	}
/*Matrice de poids maximal:
    0    1    1    1    1    0
    1    0    1    1    1    0
    1    1    0    1    0    1
    1    1    1    0    0    1
    0    1    1    1    0    1
    1    1    1    1    1    1
nCompte (nDuo+nCopie+nRecopie)/zCasPire/Reste: 15 (15+0+0) 2146164207 2146483647
Complexité:N**2.51 au pire.
    MatriceTester,test n°6: tâche terminée.
Programme terminé.*/
}//DuoMaximiseR

void DuoMinimiseR(){
	//dans C=AxB, minimiser le nombre de paires de vecteurs lignes de B à additionner en mutualisant les sommes ayant les mêmes opérandes
	eMatricE *pmA;
	int nBarre;
	int kuFois=1;//nb total d'estiMations
	s("Minimiser les sommes de vecteurs lignes de B ds C=AxB en factorisant les sommes ayant mêmes opérandes");
	s("Le nbre de duos de 1 distincts ds la multipliante A donne le nbre de lignes à sommer ds la multipliée B");
	MatriceAlloueR(&pmA);
	nBarre=nDuoEstimeR(pmA,kuFois);
	ComplexitehAfficheR(nBarre);
}//DuoMinimiseR

void ListeVoiR(int uListe[]){
	//affiche les uListe[0] éléments de uListe[]
	int uE,nEffectif;
	nEffectif=uListe[0];
	if (nEffectif>0){
		printf("Liste (%s):",sPluriel(uListe[0],"élément"));
		for (uE=1;uE<=nEffectif;uE++){
			printf("%d",uListe[uE]);
			if (uE<nEffectif)
				printf(",");
		}
	}
	else printf("Liste vide");
	printf(".\n");
}//ListeVoiR

void MatriceAlloueR(eMatricE **ppmA){
	*ppmA=malloc(sizeof(eMatricE));
	(*ppmA)->nLigne=knLigneMaX;
	MatriceRazeR(ppmA);
}//MatriceAlloueR

void MatriceAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	bMatriceAmorceR=kV;
	bMatriceOuvertE=kF;
	PremierTabuleR();
}//MatriceAMORCER

void MatriceBandeR(int iBande,eMatricE **ppmC){
	//ajoute une diagonale de 1 sur la bande iBande (=0:diagonale principale,+1:diag suivante,-1:précédente
	int uC,uL;
	Assert1("MatriceBandeR",bCroit(-(*ppmC)->nLigne,iBande,+(*ppmC)->nLigne));
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			if (uC-uL==iBande)
				(*ppmC)->Mat[uL][uC]=1;
		}
}//MatriceBandeR

void MatriceBiaiseR(int iBande,eMatricE **ppmC){
	//ajoute circulairt une diagonale de 1 sur la bande iBande (=0:diagonale principale,+1:diag suivante,-1:précédente
	int uC,uL;
	Assert1("MatriceBandeR",bCroit(-(*ppmC)->nLigne,iBande,+(*ppmC)->nLigne));
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			if (uL+iBande==uC || uL-knLigneMaX+iBande==uC)
				(*ppmC)->Mat[uL][uC]=1;
		}
}//MatriceBiaiseR

void MatriceConfigureR(long zConfigurationVoulue,eMatricE **ppmC){
	long zConfiguration;
	int uBit,uL,uC;
	zConfiguration=zConfigurationVoulue;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			uBit=zConfiguration%2;
			(*ppmC)->Mat[uL][uC]=uBit;
			zConfiguration=zConfiguration/2;
		}
}//MatriceConfigureR

void MatriceConstitueR(long zConfigurationVoulue,eMatricE **ppmC){
	//configure la matrice hors diagonale principale selon zConfigurationVoulue;la diagonale est à 0 sauf le dernier terme
	long zConfiguration;
	int uBit,uL,uC;
	zConfiguration=zConfigurationVoulue;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			if (uL!=uC || uL==knLigneMaX){
				uBit=zConfiguration%2;
				(*ppmC)->Mat[uL][uC]=uBit;
				zConfiguration=zConfiguration/2;
			};
		}
}//MatriceConstitueR

void MatriceCulminer(int uCulminant,eMatricE **ppmC){
	//Mat[uL][uC]=uCulminant-Mat[uL][uC]
	int uC,nEffectif,uL;
	nEffectif=(*ppmC)->nLigne;
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++)
			(*ppmC)->Mat[uL][uC]=uCulminant-(*ppmC)->Mat[uL][uC];
}//MatriceCulminer

void MatriceCulminerAuMieuX(eMatricE *pmC){
	//recherche le culminant qui produit le plus petit le ppcm des éléments horc diagonale de ppmC
	int uC,nEffectif,uL;
	int uCulminant,uCulminantMin,nMaximum;
	long zDiviseurMin,zDiviseur;
	nEffectif=pmC->nLigne;
	for (nMaximum=0,uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++)
			nMaximum=ySup(nMaximum,pmC->Mat[uL][uC]);
	//si("Plus grand élément de la Matrice",nMaximum);
	zDiviseurMin=kxLongintMax;
	for (uCulminant=nMaximum+1;uCulminant<=5000;uCulminant++){
		//si("uCulminant",uCulminant);
		zDiviseur=zMatriceCulminerAuMieuX(uCulminant,pmC);
		if (zDiviseur<0)
			s("zDiviseur<0");
		if (zDiviseurMin>zDiviseur){
			zDiviseurMin=zDiviseur;
			uCulminantMin=uCulminant;
			sii("Culminant optimal et ppcm associé",uCulminantMin,zDiviseurMin);
		}
	}
}//MatriceCulminerAuMieuX

long zMatriceCulminerAuMieuX(int uCulminant,eMatricE *pmC){
	//rend le ppcm des éléments situés en haut et à droite de la diagonale principale, ou kxLongintMax si hors longint
	int uC,nEffectif,uL,bQuitter;
	long zChallenger,xPpcm;
	nEffectif=pmC->nLigne;
	//si("uCulminant",uCulminant);
	for (bQuitter=kF,xPpcm=1,uL=1;(uL<=nEffectif) && (!bQuitter);uL++)
		for (uC=uL+1,1;(uC<=nEffectif) && (!bQuitter);uC++){
			zChallenger=uCulminant-pmC->Mat[uL][uC];
			//sii("xPpcm et zChallenger",xPpcm,zChallenger);
			xPpcm=zPpcm(xPpcm,zChallenger);
			if (xPpcm<=0)
				bQuitter=kV;
		}
	//si("nPpcm",zPpcm);
	if (bQuitter)
		xPpcm=kxLongintMax;
	else si("Culminant à ppcm calculable",uCulminant);
	return(xPpcm);
}//zMatriceCulminerAuMieuX

void MatriceFoisseR(int iFois,eMatricE **ppmC){
	//multiplie tous les termes de la Matrice par iFois
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			(*ppmC)->Mat[uL][uC]*=iFois;
}//MatriceFoisseR

void MatriceIdentiteR(eMatricE **ppmC){
	int uD;
	MatriceRazeR(ppmC);
	for (uD=1;uD<=knLigneMaX;uD++)
		(*ppmC)->Mat[uD][uD]=1;
}//MatriceIdentiteR

void MatriceINITIALISER(){//O(?)
	//relance le présent module
	Assert2("MatriceINITIALISER",bMatriceAmorceR,!bMatriceOuvertE);
}//MatriceINITIALISER

void MatriceModuleR(int uModulo,eMatricE **ppmC){
	//(*ppmC)->Mat[uL][uC]%=uModulo
	int uC,nEffectif,uL;
	nEffectif=(*ppmC)->nLigne;
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++){
			(*ppmC)->Mat[uL][uC]%=uModulo;
		}
	(*ppmC)->nLigne=nEffectif;
}//MatriceModuleR

long zMatriceMultiplieR(eMatricE *pmA,eMatricE *pmB,eMatricE **ppmC){
	//multiplication usuelle, en O(N**3)
	int uC,uK,uL;
	long zCopie=0;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++){
			for ((*ppmC)->Mat[uL][uC]=0,uK=1;uK<=knLigneMaX;uK++)
				(*ppmC)->Mat[uL][uC]+=pmA->Mat[uL][uK]*pmB->Mat[uK][uC];
		}
	zCopie=knLigneMaX*knLigneMaX;
	return(zCopie);
}//zMatriceMultiplieR

void MatriceProduirE(int uListe[],int bDirect,eMatricE **ppmC){
	//remplit ppmC avec ts les produits des diviseurs de uListe
	int uC,nEffectif,uL,nValeur;
	nEffectif=uListe[0];
	for (uL=1;uL<=nEffectif;uL++)
		for (uC=1;uC<=nEffectif;uC++){
			nValeur=(bDirect)? uListe[uL]*uListe[nEffectif+1-uC]: uListe[uC]*uListe[nEffectif+1-uL];
			(*ppmC)->Mat[uL][uC]+=nValeur;
		}
	(*ppmC)->nLigne=nEffectif;
}//MatriceProduirE

void MatriceRazeR(eMatricE **ppmA){
	int uC,uL;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			(*ppmA)->Mat[uL][uC]=0;
}//MatriceRazeR

int nMatriceRempliE(eMatricE *pmA){
	//rend le nombre de cases non vide ds pmA
	int uL,uC;
	int nRemplie=0;
	for (uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			if (pmA->Mat[uL][uC]>0)
				nRemplie++;
	return(nRemplie);
}//nMatriceRempliE

float fMatriceRempliR(int bDoublonPossible,int uEffectif,eMatricE **ppmA){
	//remplit ppmA avec uEffectif 1 placés au hasard,certains au même endroit ssi bDoublonPossible;rend la densité de la Matrice
	int uF,uL,uC,nLibre,nOccurrence,nRemplie;
	float fRemplir;
	Assert1("fMatriceRempliR1",bCroit(1,uEffectif,knLigneMaX*knLigneMaX));
	if (!bDoublonPossible){
		nRemplie=nMatriceRempliE(*ppmA);
		nLibre=knLigneMaX*knLigneMaX-nRemplie;
		Assert1("fMatriceRempliR2",nLibre>=uEffectif);
		for (uF=1;uF<=uEffectif;uF++){
			nOccurrence=uHasard(knLigneMaX*knLigneMaX-nRemplie);
			//remplir la case non vide de rang nOccurrence
				for (uL=1;uL<=knLigneMaX;uL++)
					for (uC=1;uC<=knLigneMaX;uC++)
						if ( (*ppmA)->Mat[uL][uC]==0 ){
							if (--nOccurrence==0) 
								(*ppmA)->Mat[uL][uC]=1;
						}
				nRemplie++;
		}
	}
	else for (uF=1;uF<=uEffectif;uF++){
			uC=uHasard(knLigneMaX);
			uL=uHasard(knLigneMaX);
			(*ppmA)->Mat[uL][uC]=1;
		}
	nOccurrence=nMatriceRempliE(*ppmA);//nb d'éléments non nuls ds (*ppmA)->Mat 
	fRemplir=(nOccurrence*1.0)/(knLigneMaX*knLigneMaX);
	Assert1("fMatriceRempliR3",bCroissant(0.0,fRemplir,1.0));
	return(fRemplir);
}//fMatriceRempliR

void MatriceTESTER(int iTest){
	//teste le présent module
	int nBarre;
	long zBarre;
	float fDensiteh;
	eMatricE *pmA;
	eMatricE *pmB;
	eMatricE *pmC;
	Appel0(sC2("MatriceTester,test n°",sEntier(iTest)));
		switch (iTest) {
			case 1:
				MatriceAlloueR(&pmA);
				MatriceAlloueR(&pmB);
				MatriceAlloueR(&pmC);
					MatriceIdentiteR(&pmA);
					MatriceFoisseR(2,&pmA);
					MatriceIdentiteR(&pmB);
					MatriceFoisseR(3,&pmB);
					MatriceVoir("Matrice A",pmA);
					MatriceVoir("Matrice B",pmB);
					zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
					MatriceVoir("Matrice AxB",pmC);
				break;
			case 2:
				MatriceAlloueR(&pmA);
				MatriceAlloueR(&pmB);
				MatriceAlloueR(&pmC);
					MatriceBandeR(1,&pmA);
					MatriceBandeR(-2,&pmB);
					MatriceVoir("Matrice A",pmA);
					MatriceVoir("Matrice B",pmB);
					zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
					MatriceVoir("Matrice AxB",pmC);
					//MatriceVoir("Matrice finale");
				//MatriceAllouer(0);
				break;
			case 4:
				ModuloParFibonnaccI();
				break;
			case 5://multiplication standard
				MatriceAlloueR(&pmA);
					MatriceAlloueR(&pmB);
						MatriceAlloueR(&pmC);
							fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmA);
							fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmB);
							MatriceVoir("Matrice A",pmA);
							MatriceVoir("Matrice B",pmB);
							zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
							MatriceVoir("Matrice AxB",pmC);
							si("zBarre",zBarre);
							ComplexitehAfficheR(zBarre);
				break;
			case 3://multiplication par duos
				DuoMinimiseR();
				break;
			case 8:
				DuoDenombreR();//décompte exhaustif
				//DuoDecompteR(kE6);//décompte statistique
				break;
			case 9:
				DuoMaximiseR();
				break;
			case 7:
				PpcmOptimalExhibeR();//Chaque produit hors diagonale d'un tenseur aurait 1 pour modulo et 1 multiplicO remplacerait N muliplicOs.
				break;
			case 6://décompostion en produit de nombres premiers
				//PremierVoiR();
				DecomposeR(60);
				DecomposeR(241);
				DecomposeR(904);
				DecomposeR(1);
				break;
			default:
				break;
		}
	Appel1(sC2("MatriceTester,test n°",sEntier(iTest)));
}//MatriceTESTER	

int bMatriceVidE(eMatricE *pmA){
	int uC,uL;
	int bVide;
	for (bVide=kV,uL=1;uL<=knLigneMaX;uL++)
		for (uC=1;uC<=knLigneMaX;uC++)
			bVide=bVide && pmA->Mat[uL][uC]==0;
	return(bVide);
}//bMatriceVidE

void MatriceVoir(char *sMessage,eMatricE *pmA){
	int uC,uL;
	Assert2("MatriceVoir",bMatriceAmorceR,sMessage!=0);
	printf("%s\n",sMessage);
	/*//afficher nCarD après affichage des index de sNexT[]
		printf("index = ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",uS);
		printf("  nCarD=%d\n",nCarD);*/
	//eMat afficher 
		for (uL=1;uL<=pmA->nLigne;uL++){
			for (uC=1;uC<=pmA->nLigne;uC++)
				printf(" %4d",pmA->Mat[uL][uC]);
			printf("\n");
		}
}//MatriceVoir

void MatriceVoirSouS(int bSous,char *sMessage,eMatricE *pmA){
	if (bSous)
		MatriceVoir(sMessage,pmA);
}//MatriceVoirSouS

void ModuloParFibonnaccI(){
	//utiliser la fonction de Fibonacci pour neutraliser les coef hors diagonale
	eMatricE *pmA;
	eMatricE *pmB;
	eMatricE *pmC;
	long zBarre;
	float fDensiteh;
	MatriceAlloueR(&pmA);
		MatriceAlloueR(&pmB);
			MatriceAlloueR(&pmC);
				fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmA);
				fDensiteh=fMatriceRempliR(k1BitsDistincts,knLigneMaX*knLigneMaX,&pmB);
				MatriceVoir("Matrice A",pmA);
				MatriceVoir("Matrice B",pmB);
				zBarre=zMatriceMultiplieR(pmA,pmB,&pmC);
				MatriceVoir("Matrice AxB",pmC);
				si("zBarre",zBarre);
				ComplexitehAfficheR(zBarre);
				/*for (nIndex=0;nIndex<=20;nIndex++)
					printf("F(%d)=%ld\n",nIndex,zFib(nIndex));
				si("F(10)\%F(10)",zFib(10)%zFib(10));
				si("F(20)\%F(10)",zFib(20)%zFib(10));
				si("F(30)\%F(10)",zFib(30)%zFib(10));
				si("F(40)\%F(10)",zFib(40)%zFib(10));*/
}//ModuloParFibonnaccI

void PpcmOptimalExhibeR(){
	//Exhibe un ppcm calculable tel que chaque produit hors diagonale d'un tenseur a pour modulo 1 (remplace N multiplicO par 1 seule)
	eMatricE *pmC;
	int uListe[20];
	s("Soit L la liste des diviseurs d'un nombre N donné");
	//DiviseurS(60,&uListe[0]);
	//DiviseurS(12,&uListe[0]);
	DiviseurS(2*3*5,&uListe[0]);//2,3,5,6,10,15
	ListeVoiR(uListe);
	s("Soit T la Matrice Tenseur, ie tous les produits de deux diviseurs de L");
	MatriceAlloueR(&pmC);
	MatriceProduirE(uListe,1,&pmC);
	MatriceVoir("Matrice tenseur T",pmC);
	s("Soit S la Matrice selle (diagonale principale minimale) obtenue en ajoutant à T la transposée de T");
	MatriceProduirE(uListe,0,&pmC);
	MatriceVoir("Matrice selle S",pmC);
	s("Soit Co le culminant optimal tel que les éléments Eij=Co-Sij hors diagonale ont le plus petit ppcm de type longint");
	MatriceCulminerAuMieuX(pmC);
	s("Bilan:il semble impossible de trouver un tenseur à ppcm calculable lorsque la Matrice NxN vérifie N>6");
	//MatriceModuleR(120,&pmC);
	//MatriceVoir("Matrice modulo",pmC);
}//PpcmOptimalExhibeR

void PremierVoiR(){
	int uN,nPremier;
	printf("Nombre premiers:\n");
	for (nPremier=abPremieR[0],uN=1;uN<=knPremierMaX;uN++)
		if (abPremieR[uN]!=0){
			printf("%3d",uN);
			if (--nPremier>0)
				printf(",");
		}
	printf(".\n");
}//PremierVoiR

void PremierTabuleR(){
	//abPremieR[X]:="X est un nombre premier",1≤X≤knPremierMaX;de plus,abPremieR[0]:=effectif de ces nombres premiers.
	int uDividende,nPremier,uN,uQuotient,nRac;
	Assert1("PremierTabuleR1",knPremierMaX>1);
	nRac=trunc(sqrt(knPremierMaX));//X premier <=>X non divisible par un nombre inférieur ou égal à nRac
	//si("nRac",nRac);
	for (uDividende=1;uDividende<=knPremierMaX;uDividende++)
		abPremieR[uDividende]=1;//d
	for (uDividende=1;uDividende<=knPremierMaX;uDividende++)
		for (uQuotient=2;uQuotient<=yInf(uDividende-1,nRac);uQuotient++)
			if (uDividende%uQuotient==0)
				abPremieR[uDividende]=0;
	//nPremier:=nbre total de nombres premiers
		for (nPremier=0,uN=1;uN<=knPremierMaX;uN++)
			if (abPremieR[uN]!=0)
				nPremier++;
	abPremieR[0]=nPremier;
	Assert1("PremierTabuleR2",nPremier>0);
}//PremierTabuleR


