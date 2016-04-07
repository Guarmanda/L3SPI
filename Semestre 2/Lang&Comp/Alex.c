#include "Outil.h"
#include "Alex.h"
//module d'analyse lexicale
#define knAEFetatMaX 10
#define knByteLiM 256
#define knClasseLexicaleMaX 8
#define kuCodeSourceLgMaX 100
#define knLexemeMaX	52
#define knTrancheMaX 147
#define kbVoiR kV
#define kuHeureHeurePointMinuteMinuteLg 5
int iAEF[1+knAEFetatMaX][1+knClasseLexicaleMaX];
int bAlexAmorceR;
enum eCaractereClassE {ccButoiR,ccDeciT,ccLettrE,ccPoinT,ccSeparateuR,ccOperateuR,ccBlanC,ccDiverS};
int ccCaractereClassE[knByteLiM];
char *sCodeSourcE;//alloué dans AlexAMORCER
enum eLexemeClassE    {lcRieN,lcBlanC,lcInconnU,lcEntieR,lcReeL,lcIdentificateuR,lcOperateuR,lcSeparateuR,lcFinFichieR};
int nLexemeEnTouT;
struct rLexemE{int classe;int indexdebut;int indexfin;} lxmChainE[1+knLexemeMaX];//la chaîne lexicale est générée dans dans lxmChainE
#define knClefMaximum 5
int knClefMax = knClefMaximum;
int tClef[knClefMaximum] = {1,2,3,4,5};


void AutomateAffecteR();
void ClasseCaractereDefiniR();
int bCodeSourceAnalyseR(int bVoiR);
void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche);
void ErreurDiagnostiqueR(int uAnomalie,int uLigne);
void LexemeEmpileR();
void LexemeVoiR();

int bAlexLexeme(int nLexeme){
    int bSucces;
    bSucces=(nLexeme>0 && nLexeme<=nLexemeEnTouT)?  1:0;
    return bSucces;
}

int bAlexClef(int uLexeme){
    int bClef = 0;
    int nClef;
    char sLexeme[knByteLiM];
    
    if(bAlexEntier(uLexeme)){
        CodeSourceTrancheR(lxmChainE[uLexeme].indexdebut,lxmChainE[uLexeme].indexfin,kF,sLexeme);
        sscanf(sLexeme,"%d1",&nClef);
        for(int i=0; i<knClefMax; i++){
            if(nClef==tClef[i]){
                bClef=1;
            }
        }
    }
    
    return bClef;
}

int bAlexHoraire(int uLexeme){
    int bHoraire;
    float rHoraire;
    int nMinute;
    int nHeure;
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
            
            nHeure=trunc(rHoraire);
            bHoraire=bHoraire && bCroit(0,nHeure,23);
        }
    }
    return(bHoraire);
}//bAlexHoraire

int bIndexValid(int iLexeme){
    int bSucces;
    bSucces = (iLexeme > 0 && iLexeme < nLexemeEnTouT);
    return bSucces;
}

int bAlexEntier(int iDebut){
    int bSucces = 0;
    if (bIndexValid(iDebut) && lxmChainE[iDebut].classe == lcEntieR)
            bSucces=1;
    return bSucces;
}
int bAlexFinFichier(int iDebut){
    int bSucces = 0;
    if (lxmChainE[iDebut].classe == lcFinFichieR || iDebut > nLexemeEnTouT)
            bSucces=1;
    return bSucces;
}
int bAlexIdentificateur(int iDebut){
    int bSucces = 0;
    if (bIndexValid(iDebut) && lxmChainE[iDebut].classe == lcIdentificateuR)
            bSucces=1;
    return bSucces;
}
int nAlexInstruction(int iDebut){
    if (bAlexReel(iDebut))
        return 1;
    if (bAlexEntier(iDebut))
        return 2;
    if (bAlexIdentificateur(iDebut))
        return 3;
    
    return 0;
}
int nAlexInstruS(int iDebut){
    if (bAlexReel(iDebut))
        return 3;
    if (bAlexEntier(iDebut))
        return 2;
    if (bAlexIdentificateur(iDebut))
        return 1;
    
    return 0;
}
int bAlexReel(int iDebut){
    int bSucces = 0;
    if (bIndexValid(iDebut) && lxmChainE[iDebut].classe == lcReeL)
            bSucces=1;
    return bSucces;
}


void AlexAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	AutomateAffecteR();
	ClasseCaractereDefiniR();
	sCodeSourcE=malloc(1+kuCodeSourceLgMaX);
	bAlexAmorceR=kV;
}//AlexAMORCER

void AlexDenoncer(int nLexeme){
	//affiche en clair la cause de l'erreur lexicale qui a fait empilé un lexème de classe lcInconnU
	int uLxm;
	int nDenonce,nLigne;
    int nLxmClasse;
    int nLxmDebutInclus;
    int nLxmFinExclue;
    char sLexeme[knByteLiM];
    
	Appel0("AlexDenoncer");
		//nDenonce:=rang1 du premier lexème inconnu;il vérifie lxmChainE[uLxm].classe<0
			for (nDenonce=0,nLigne=1,uLxm=1;(uLxm<=nLexemeEnTouT) && (nDenonce==0);uLxm++){
				if (lxmChainE[uLxm].classe<0)
					nDenonce=uLxm;
				if (lxmChainE[uLxm].classe==lcSeparateuR)
					nLigne++;
			}
    //Assert1("AlexDenoncer",nDenonce>0);
    
        nLxmClasse=lxmChainE[nLexeme].classe;
        nLxmDebutInclus=lxmChainE[nLexeme].indexdebut;
        nLxmFinExclue=lxmChainE[nLexeme].indexfin;
        CodeSourceTrancheR(nLxmDebutInclus,nLxmFinExclue,kF,sLexeme);
    
		printf("   Lexeme n°%2d: (%2d,%2d,%2d) : %s\n",nLexeme,nLxmClasse,nLxmDebutInclus,nLxmFinExclue,sLexeme);
		//recopier la ligne courante au voisinage de laquelle se trouve l'erreur
		
		
		
    //ErreurDiagnostiqueR(nDenonce,nLigne);
	Appel1("AlexDenoncer");
}//AlexDenoncer

void AlexINITIALISER(){//O(?)
	//relance le présent module
	Assert1("AlexINITIALISER",bAlexAmorceR);
}//AlexINITIALISER

void AlexTESTER(int iTest){
	//teste le présent module
	int bSucces;
	Appel0(sC2("AlexTESTER,test n°",sEntier(iTest)));
		sCodeSourcE="27+3.14;AB=5*8$";
		switch (iTest) {
			case  1:	sCodeSourcE="27 + 3.14 ; CD = 5 * 8 $ ";break;
			case  5:	sCodeSourcE="27+3.14;EF      =  5*8$";break;
			case  8:	sCodeSourcE="27+3.14;EF      =  5*8$$";break;
			case  4:	sCodeSourcE="$";break;
			case  3:	sCodeSourcE="";break;
			case  2:	sCodeSourcE="24 ; 5 ; 3...2 ; 4$";break;
			default:break;
		}
		printf("sCodeSourcE=\"%s\".\n",sCodeSourcE);
		bSucces=bCodeSourceAnalyseR(kbVoiR);
		if (!bSucces)
            //AlexDenoncer();
	Appel1(sC2("AlexTESTER,test n°",sEntier(iTest)));
}//AlexTESTER	

int bAlexAnalyser(char *sSource){
    int bSucces = 0;
    
    strcpy(sCodeSourcE,sSource);
    printf("sCodeSourcE=\"%s\".\n",sCodeSourcE);
    bSucces = bCodeSourceAnalyseR(!kbVoiR);
    
    return bSucces;
}


void AutomateAffecteR(){
	//affecte une fois pour toutes l'automate d'états finis iAEF[]
	char *sAEF[1+knAEFetatMaX];
	const int knPas=5;//nombre total de caractères disponibles pour spécifier l'état suivant ds la i-ième ligne de texte sAEF[ligne i]
	int nL,nC;
	int bVoir=kF;
	Appel0("AutomateAffecteR");
		for (nL=0;nL<=knAEFetatMaX;nL++)
			sAEF[nL]=malloc(knPas*knClasseLexicaleMaX);//pas de free plus bas, mais cette routine n'est appelée qu'une fois
	    //classes:    $  0..9  A..Z  .    ;  operH blc autre
		sAEF[ 0]="    8    3    5    0    7    6    1    2";//dispatcheur vers les sous-automates
		sAEF[ 1]="    0    0    0    0    0    0    1    0";//lcBlanC
		sAEF[ 2]="    0    0    0    0    0    0    0    2";//lcInconnU
		sAEF[ 3]="    0    3    0   10    0    0    0    0";//lcEntieR
		sAEF[ 4]="    0    4    0    0    0    0    0    0";//lcReeL
		sAEF[ 5]="    0    0    5    0    0    0    0    0";//lcIdentificateuR
		sAEF[ 6]="    0    0    0    0    0    0    0    0";//lcOperateuR
		sAEF[ 7]="    0    0    0    0    0    0    0    0";//lcSeparateuR
		sAEF[ 8]="    0    0    0    0    0    0    0    0";//lcFinFichieR

		sAEF[10]="   -1    4   -1   -2   -1   -1   -1   -1";//un point a été rencontré;constante réelle attendue
		for (nL=0;nL<=knAEFetatMaX;nL++){
			for (nC=0;nC<=knClasseLexicaleMaX;nC++){
				sscanf(sAEF[nL]+knPas*nC,"%d\n",&iAEF[nL][nC]);
				if (bVoir)
					printf("[%2d,%2d]=%2d ",nL,nC,iAEF[nL][nC]);
			}
			if (bVoir)
				printf("\n");
		}
	Appel1("AutomateAffecteR");
}//AutomateAffecteR

void ClasseCaractereDefiniR(int bVoir){
	//définit une fois pour toutes la classe ClasseDeC au caractère C en mémorisant ClasseDeC dans ccCaractereClassE[C] pour tout C.
	Appel0("ClasseCaractereDefiniR");
		int nC,nClasse;
		for (nC=0;nC<knByteLiM;nC++){
			nClasse=ccDiverS;
			if (isdigit(nC)) nClasse=ccDeciT;
			if (isalpha(nC)) nClasse=ccLettrE;
			if (nC=='.') nClasse=ccPoinT;
			if (nC==';') nClasse=ccSeparateuR;
			if ((nC=='+') || (nC=='-') || (nC=='*') || (nC=='/')) nClasse=ccOperateuR;
			if (nC==' ') nClasse=ccBlanC;//blanc ou assimilé
			if (nC=='$') nClasse=ccButoiR;
			ccCaractereClassE[nC]=nClasse;
			if (/*bVoir*/ kF)
				printf("caractère %3d    classe %2d \n",nC,nClasse);
		}
	Appel1("ClasseCaractereDefiniR");
}//ClasseCaractereDefiniR

int bCodeSourceAnalyseR(int bVoiR){
	//analyse le code source censé figurer dans sCodeSourcE[] et empile la chaîne lexicale dans lxmChainE
	int bAnalyser,nC,nClasse,nClim,nEtat,nEtat0,nDebut;
	Appel0("bCodeSourceAnalyseR");
		Assert1("bCodeSourceAnalyseR",bAlexAmorceR);
		bAnalyser=kV;
		nLexemeEnTouT=0;
		nClim=strlen(sCodeSourcE);
		
		//Si sCodeSourcE est vide
		if(nClim == 0){
			LexemeEmpileR(++nLexemeEnTouT, lcFinFichieR, 0, 1, kV);
			if (kV)
				LexemeVoiR();
			Assert2("bCodeSourceAnalyseR",nLexemeEnTouT>0,(!bAnalyser || lxmChainE[nLexemeEnTouT].classe==lcFinFichieR));
			Appel1("bCodeSourceAnalyseR");
			return bAnalyser;
		}
		
		for (nEtat=0,nC=0,nDebut=nC;nC<nClim;nC++){
			nClasse=ccCaractereClassE[sCodeSourcE[nC]];
			nEtat0=nEtat;
			nEtat=iAEF[nEtat0][nClasse];
			if (kF)
				printf("passe %d: à l'état courant %d, '%c' est lu, de classe %d, donc iAEF[%d][%d] rend %d.\n",nC,nEtat0,sCodeSourcE[nC],nClasse,nEtat0,nClasse,nEtat);
			if (nEtat<=0){
				if (nEtat0!=lcBlanC)//empiler le lexème courant dans la chaîne lexicale de sommet nLexemeEnTouT
					LexemeEmpileR(++nLexemeEnTouT,(nEtat==0)? nEtat0 : nEtat, nDebut, nC, kV);
				bAnalyser=bAnalyser && (nEtat==0);
				nEtat=iAEF[nEtat][nClasse];
				nDebut=nC;
				/*code à compléter*/
			}
			if(lxmChainE[nLexemeEnTouT].classe < 0){
                //AlexDenoncer();
			}
		}
		//Si le dernier Lexeme n'est pas une fin de fichier, l'ajouter
		if(lxmChainE[nLexemeEnTouT].classe != lcFinFichieR){
			LexemeEmpileR(++nLexemeEnTouT, lcFinFichieR, nDebut, nC, kF);
		}
		
		//sb("bAnalyser",bAnalyser);
		if (bVoiR)
			s(sC3b("      Il",sNie("y a",bAnalyser,"un","aucun"),"lexème inconnu"));
		if (kV)
			LexemeVoiR();
		//si("nClim",nClim);
		//si("lcFinFichieR",lcFinFichieR);
		Assert2("bCodeSourceAnalyseR",nLexemeEnTouT>0,(!bAnalyser || lxmChainE[nLexemeEnTouT].classe==lcFinFichieR));
	Appel1("bCodeSourceAnalyseR");
	bAnalyser=(lxmChainE[nLexemeEnTouT].classe==lcFinFichieR);
	return bAnalyser;
}//bCodeSourceAnalyseR

void CodeSourceTrancheR(int nDebutInclus,int nFinExclue,int bVoir,char *sTranche){
	//copie dans sTranche le fragment sCodeSourcE[nDebutInclus..nFinExclue[
	int nC,bDefini;
	bDefini=(0<=nDebutInclus) && (nDebutInclus<nFinExclue) && (nFinExclue-nDebutInclus<knTrancheMaX);
	sTranche[0]='\0';
	if (bDefini){
		for (nC=nDebutInclus;nC<nFinExclue;nC++)
			sTranche[nC-nDebutInclus]=sCodeSourcE[nC];
		sTranche[nFinExclue-nDebutInclus]='\0';
	}
	else (kV && printf("tranche incorrecte [nDebutInclus:%d..nFinExclue[:%d.\n",nDebutInclus,nFinExclue)),Assert1("CodeSourceTrancheR",bDefini);
}//CodeSourceTrancheR

void ErreurDiagnostiqueR(int uAnomalie,int uLigne){
	//affiche en clair un message censé aider l'utilisateur à comprendre facilement la cause de son erreur
	char *sBug;
	Appel0("ErreurDiagnostiqueR");
		Assert2("ErreurDiagnostiqueR",uAnomalie>0,uLigne>0);
		sBug=malloc(100);
		sBug="Compilateur défectueux";//signifiera que le code ci-dessous la clause "default" a été malencontreusement activée
		switch (-lxmChainE[uAnomalie].classe) {
			case  1:	sBug="Bug n°1";break;// *** remplacer ce message par quelque chose de plus constructif SVP
			case  2:	sBug="Bug n°2";break;// *** remplacer ce message par quelque chose de plus constructif SVP
			default:break;
		}
		printf("Erreur lexicale ligne %d: %s.\n",uLigne,sBug);
	Appel1("ErreurDiagnostiqueR");
}//ErreurDiagnostiqueR

void LexemeEmpileR(int nLxmIndex,int nLxmClasse,int nLxmDebutInclus,int nLxmFinExclue, int bVoir){
	char sLexeme[knByteLiM];
	//Appel0("LexemeEmpileR");
		Assert1("LexemeEmpileR1",bCroit(0,nLxmDebutInclus,nLxmFinExclue));
		lxmChainE[nLxmIndex].classe=nLxmClasse;
		lxmChainE[nLxmIndex].indexdebut=nLxmDebutInclus;
		lxmChainE[nLxmIndex].indexfin=nLxmFinExclue;
		CodeSourceTrancheR(nLxmDebutInclus,nLxmFinExclue,bVoir,/**/sLexeme);
		//stocker sLexeme dans le dictionnaire
			/*  *** code à compléter ici pour remplir le dictionnaire*/
		if (bVoir)
			printf("              Empilement du lexème %2d: (classe %d, lexie \"%s\").\n",nLxmIndex,nLxmClasse,sLexeme);
	//Appel1("LexemeEmpileR");
}//LexemeEmpileR

void LexemeVoiR(){
	int uLxm;
	printf("Chaine lexicale (%s):\n",sPluriel(nLexemeEnTouT,"lexème"));
	for (uLxm=1;uLxm<=nLexemeEnTouT;uLxm++)
		printf("   Lexeme n°%2d: (%2d,%2d,%2d)\n",uLxm,lxmChainE[uLxm].classe,lxmChainE[uLxm].indexdebut,lxmChainE[uLxm].indexfin);
}//LexemeVoiR