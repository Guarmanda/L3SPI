#include "Outil.h"
#include "Tas.h"
//NB:pour créer un minimier contenant 20 éléments au plus,encadrer tous les accès au tas par TasAllouer(20) et TasAllouer(0);

#define knEffectifMaX 9 //nb max d'éléments admissible physiquement dans le tas; k comme constante;n comme entier naturel. 
int bTasAmorceR;//ie le module a effectivement été amorcé
int ukTasHauteurMaX;//u:un ou plus,k:constante.uk désigne une variable>1 vue comme une constante après initialisation. ku désignerait une vraie constante>1.
int bTasOuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un tas est actuellement alloué
int nTasVoiR;//dédié TasVoir();numéro du tas affiché
struct Tas{//ci-dessous,l'indice 0 est inutilisé;partir de l'index 1 facilite l'implémentation du tas.
	int uEtiquette[1+knEffectifMaX];//étiquette de l'élément stocké dans le tas,censé être un entier dans [1..knEffectifMaX] 
	int nPlace[1+knEffectifMaX];//nPlace[E]>0 donne l'emplacement de l'élément E dans le tas. Si nPlace[E]=0,alors E n'est pas dans le tas.
	int nPoids[1+knEffectifMaX];//poids positif ou nul associé à l'élément considéré.
	int nVolume;//nombre d'éléments stockés actuellement dans le tas
}TaS,*pTaS;

void TasDescendrE(int uElement);
void TasMonteR(int uElement);
void TasSatureR();
void TasTesterExhaustivemenT(int uEffectifMax);

void TasAllouer(int nEffectifMax){//O(1)
	//si nEffectifMax>0, alloue un tas à nEffectifMax éléments;si nEffectifMax=0, restitue le tas.
	Assert2("TasAllouer",bTasAmorceR,bCroit(0,nEffectifMax,knEffectifMaX));
	FlipFlop(bVrai(nEffectifMax>0),&bTasOuverT);
	if (nEffectifMax>0)
		pTaS=malloc(sizeof(TaS));
	else free(pTaS);
	if (bTasOuverT)
		TasRazer();//dc en O(nEffectifMax) et pas en O(knEffectifMaX),ce qui changerait la complexité des petits tas
}//TasAllouer

void TasAMORCER(){
	//amorce le présent module une fois pour toutes
	ukTasHauteurMaX=1+mPoidsFort(knEffectifMaX);//affectation définitive indiquée par le préfixe qui contient un "k" comme constante
	nTasVoiR=0;
	bTasAmorceR=kV;
	bTasOuverT=kF;
}//TasAMORCER

int bTasContient(int uElement){//O(1)
	//vrai ssi uElement désigne un élément qui est actuellement présent dans le tas
	int bContient;
	Assert3("bTasContient",bTasAmorceR,bTasOuverT,bCroit(1,uElement,knEffectifMaX));
	bContient=bCroit(1,uElement,knEffectifMaX) && (pTaS->nPlace[uElement]>0);
	return(bContient);
}//bTasContient

void TasDescendrE(int uElement){//O(1)
	int uFils,uPere;
	Assert1("TasDescendrE",bCroit(1,uElement,knEffectifMaX));
	uPere=pTaS->nPlace[uElement];
	uFils=2*uPere;
	if (uFils<pTaS->nVolume && pTaS->nPoids[pTaS->uEtiquette[uFils+1]]<pTaS->nPoids[pTaS->uEtiquette[uFils]])
		uFils++;
	While(ukTasHauteurMaX);
	while (bWhile(uFils<=pTaS->nVolume && pTaS->nPoids[pTaS->uEtiquette[uFils]]<pTaS->nPoids[pTaS->uEtiquette[uElement]])) {
		//sii("père et fils",uPere,uFils);
		//faire remonter de 1 niveau l'élément indexé par uFils pour que uElement puisse descendre
			pTaS->uEtiquette[uPere]=pTaS->uEtiquette[uFils];
			pTaS->nPlace[pTaS->uEtiquette[uFils]]=uPere;
		//descendre de 1 niveau
			uPere=uFils;
			uFils=2*uPere;
			if (uFils<pTaS->nVolume && pTaS->nPoids[pTaS->uEtiquette[uFils+1]]<pTaS->nPoids[pTaS->uEtiquette[uFils]])
				uFils++;
	};//while
	//placer uElement dans le tas à l'index uPere
		pTaS->uEtiquette[uPere]=uElement;
		pTaS->nPlace[uElement]=uPere;
}//TasDescendrE

int eTasExtraire(){//O(1)
	//rend l'élément situé à la racine du tas,ou déroute si extraction non définie
	int eDernier;
	int eExtraire;//élément pour lequel la valeur associée est minimale;le tas étant un minimier, cet élément est situé à la racine, d'index 1.
	Assert1("eTasExtraire1",pTaS->nVolume>0);
	eExtraire=0;//aucun élément extrait par défaut
	if (pTaS->nVolume>0) {//attribuer à l'élément extrait un poids maximal afin que cet élément migre au fond du tas
		pTaS->nVolume--;
		eExtraire=pTaS->uEtiquette[1];
		pTaS->nPlace[eExtraire]=0;
		eDernier=pTaS->uEtiquette[pTaS->nVolume+1];
		//si("eDernier",eDernier);
		if (kF){
			pTaS->uEtiquette[1]=eDernier;//code correct mais superflu vu le code de TasDescendrE() li+4
			pTaS->nPoids[1]=pTaS->nPoids[eDernier];//code correct mais superflu vu le code de TasDescendrE() li+3
		}
		pTaS->nPlace[eDernier]=1;//place à la racine le dernier des éléments situés en bas du tas
		TasDescendrE(eDernier);//si le poids associé à cet élément est trop grand,TasDescendrE() le fait migrer plus bas dans le tas.
	}
	Assert2("eTasExtraire2",bCroit(1,eExtraire,knEffectifMaX),pTaS->nVolume>=0);
	return(eExtraire);
}//eTasExtraire

void TasInsererValuer(int uElement,int nPoids){
	//insère (uElement,nPoids) dans le tas si uElement est absent et s'il reste de la place dans le tas;si uElement est déjà présent,ne fait rien.
	Assert4("TasInsererValuer",bTasAmorceR,bTasOuverT,bCroit(1,uElement,knEffectifMaX),nPoids>=0);
	if (!bTasContient(uElement)){
		pTaS->nVolume++;
		pTaS->nPlace[uElement]=pTaS->nVolume;
		pTaS->uEtiquette[pTaS->nVolume]=uElement;
		pTaS->nPoids[pTaS->nVolume]=nPoids;
		TasMonteR(uElement);
	}
}//TasInsererValuer

void TasINITIALISER(){//O(?)
	//relance le présent module
	Assert2("TasINITIALISER",bTasAmorceR,!bTasOuverT);
}//TasINITIALISER

void TasMonteR(int uElement){//O(1)
	int uFils,nPere;
	Assert3("TasMonteR1",bTasAmorceR,bTasOuverT,uElement>0);
	uFils=pTaS->nPlace[uElement];
	nPere=uFils/2;
	While(ukTasHauteurMaX);
	while (bWhile(uFils>1 && pTaS->nPoids[pTaS->uEtiquette[nPere]]>pTaS->nPoids[uElement])) {
		//faire descendre de 1 niveau l'élément indexé par nPere pour que uElement puisse monter
			pTaS->uEtiquette[uFils]=pTaS->uEtiquette[nPere];
			pTaS->nPlace[pTaS->uEtiquette[nPere]]=uFils;
		//monter
			uFils=nPere;
			nPere=uFils/2;
	}//while
	Assert2("TasMonteR2",bCroit(1,uFils,pTaS->nVolume),bCroit(0,nPere,uFils-1));
	//installer uElement au rang uFils
		pTaS->uEtiquette[uFils]=uElement;
		pTaS->nPlace[uElement]=uFils;
}//TasMonteR

void TasRazer(){//O(nCardinalMax)
	int uE;
	Assert2("TasRazer",bTasAmorceR,bTasOuverT);
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->uEtiquette[uE]=0;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPlace[uE]=0;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPoids[uE]=0;
	pTaS->nVolume=0;
}//TasRazer

void TasSatureR(){//O(knEffectifMaX)
	//remplit le tas avec knEffectifMaX éléments uE de poids 10*uE
	int uE;
	Assert2("TasSatureR",bTasAmorceR,bTasOuverT);
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->uEtiquette[uE]=uE;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPlace[uE]=uE;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPoids[uE]=10*uE;
	pTaS->nVolume=knEffectifMaX;
}//TasSatureR

int eTasSommet(){//O(1)
	//rend l'élément situé à la racine du tas, ou 0 si le tas est vide
	int eSommet;
	Assert2("eTasSommet1",bTasAmorceR,bTasOuverT);
	if (bTasVide())
		eSommet=0;
	else eSommet=pTaS->uEtiquette[1];
	Assert2("eTasSommet2",bCroit(0,eSommet,knEffectifMaX),(eSommet==0)==bTasVide());
	return(eSommet);
}//eTasSommet

void TasTESTER(int iTest){
	//teste le présent module
	int eExtrait,uE,bContient;
	Appel0(sC2("TasTESTER,test n°",sEntier(iTest)));
		TasAllouer(knEffectifMaX);
			switch (iTest) {
				case 2:
					TasSatureR();
					TasVoir("TasSatureR");
					break;
				case 1:
					TasSatureR();
					TasVoir("TasSatureR");
					eExtrait=eTasSommet();
					sii("sommet et volume A",eExtrait,pTaS->nVolume);
					for (uE=pTaS->nVolume;uE>0;uE--){
						eExtrait=eTasExtraire();//qui décrémente pTaS->nVolume, mais lu 1 fois au début du for
						TasVoir(sC2b("extraction de l'élément",sEntier(eExtrait)));
					}
					eExtrait=eTasSommet();
					sii("sommet et volume B",eExtrait,pTaS->nVolume);//affiche 0 et 0
					bContient=bTasContient(2);sb("bContient 2",bContient);
					TasInsererValuer(2,50);TasVoir("insertion (2,50)");
					bContient=bTasContient(2);sb("bContient 2",bContient);
					bContient=bTasContient(4);sb("bContient 4",bContient);
					TasInsererValuer(4,20);TasVoir("insertion (4,20)");
					bContient=bTasContient(4);sb("bContient 4",bContient);
					TasInsererValuer(3,80);TasVoir("insertion (3,80)");
					TasInsererValuer(6,90);TasVoir("insertion (6,90)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					eExtrait=eTasSommet();//non défini puisque tas vide
					sii("sommet et volume C",eExtrait,pTaS->nVolume);
					break;
				case 3:
					TasTesterExhaustivemenT(6);
					break;
				default:
					Assert1("TasTESTER",0);
					break;
			}
		TasAllouer(0);
	Appel1(sC2("TasTESTER,test n°",sEntier(iTest)));
}//TasTESTER	

void TasTesterExhaustivemenT(int uEffectifMax){
	//génère 2**uEffectifMax configurations d'éléments distinctes;construit chaque fois le tas correspondant puis le vide par extractions successives.
	#define kuPoidsMax kE2
	float rEffectifMax;
	long zEffectifMax;
	int asConfig[1+knEffectifMaX];
	long zGeant;
	int nPlace;
	long zReste;
	int eRetrait;
	int uRetrait;
	Assert1("TasTesterExhaustivemenT",uEffectifMax>0);
	rEffectifMax=zPuissance(2,uEffectifMax)-1;
	for (zGeant=zEffectifMax=trunc(rEffectifMax);zGeant>=0;zGeant--){
		//i(zGeant);
		//décomposer zGeant en base zCardinalMax sur uEffectifMax digits
			for(zReste=zGeant,nPlace=1;nPlace<uEffectifMax;nPlace++){
				asConfig[nPlace]=1+zReste % uEffectifMax;
				zReste=zReste/uEffectifMax;
			}
		//construire le tas décrit par la configuration asConfig[] ——et le voir
			TasRazer();
			for(nPlace=1;nPlace<uEffectifMax;nPlace++)
				if (!bTasContient(asConfig[nPlace])){
					TasInsererValuer(asConfig[nPlace],uHasard(kuPoidsMax));
				}
			TasVoir(sC2("Tas généré n°",sEntier(zGeant)));
		//vider le tas par extractions successives --et voir le tas résultant
			for(uRetrait=1;uRetrait<=pTaS->nVolume;uRetrait++){
				eRetrait=eTasExtraire();
				TasVoir(sC2b("retrait de l'élément",sEntier(eRetrait)));
			}
	}
}//TasTesterExhaustivemenT

int bTasVide(){//O(1)
	int bVide;
	Assert2("bTasVide",bTasAmorceR,bTasOuverT);
	bVide=(pTaS->nVolume==0);
	return(bVide);
}//bTasVide

void TasVoir(char *sMessage){//O(nCardMaX)
	#define kuLargeurMax 200
	#define kncCouple 8
	char acCouple[1+kncCouple];//description en caractères d'un couple (élément,poids de l'élément)
	int nbDeport;//nombre de blancs insérés entre les couples pour faire apparaître un tas binaire
	int bDernier;
	char acEtage[1+kuLargeurMax];//suite des caractères qui décrit l'étage courant du tas
	int nEtage;
	int nEtageMax;
	int uIndex;
	Assert3("TasVoir",bTasAmorceR,bTasOuverT,sMessage!=0);
	nTasVoiR++;
	printf("Tas n°%d après %s:\n",nTasVoiR,sMessage);
	if (pTaS->nVolume>0)
		for (nEtageMax=mPoidsFort(pTaS->nVolume),nEtage=0;nEtage<=nEtageMax;nEtage++){
			nbDeport=kncCouple*(zPuissance(2,nEtageMax-nEtage)-1);
			for (strcpy(acEtage,sE(nbDeport/2)),uIndex=zPuissance(2,nEtage);uIndex<=yInf(zPuissance(2,nEtage+1)-1,pTaS->nVolume);uIndex++){
				bDernier=(uIndex==yInf(zPuissance(2,nEtage+1)-1,pTaS->nVolume));
				sprintf(acCouple,"(%2d,%2d)",pTaS->uEtiquette[uIndex],pTaS->nPoids[pTaS->uEtiquette[uIndex]]);
				strcat(acEtage,acCouple);
				if (!bDernier)
					strcat(acEtage,sE(1+nbDeport));
			}
			printf("    %s\n",acEtage);
		}
	else printf("    Le tas est vide.\n");
	if (0)
		Pause();
}//TasVoir

