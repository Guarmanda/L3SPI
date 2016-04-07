#include "Outil.h"
#include "Alex.h"
#include "Asynt.h"
#include "Erreur.h"
//module d'analyse synntaxique
#define kbVoiR kV
int nAPPEL;//nombre total d'appels associés aux règles terminales de la grammaire,ie bAlexIdentificateur(), etc
int bAsyntAmorceR;
int bkEclaireuR;
int bModeSem = 0;

int bCalcuL(int iDebut,int *piFin);
int bEntieR(int iDebut,int *piFin);
int bFinFichieR(int iDebut,int *piFin);
int bIdentificateuR(int iDebut,int *piFin);
int bLecturE(int iDebut,int *piFin);
int bEcriturE(int iDebut,int *piFin);
int bInstructioN(int iDebut,int *piFin);
int bInstructionS(int iDebut,int *piFin);
int bProgrammE(int iDebut,int *piFin);
int bReeL(int iDebut,int *piFin);

//Programme->Instructions || FinFichier
//Instructions->Instrus.Programme
//Instruction->Lecture || Ecriture || Calcul
//Instrus->Instru1 || Instru2 || Instru3
//Instru1->Id.Clef.Reel.Horaire
//Instru2->Entier.Entier
//Instru3->Reel
//Horaire->Reel
//Clef->Entier
//Calcul->Reel.Entier.Identificateur
//Ecriture->Entier.Identificateur
//Lecture->Identificateur.Entier

int bCleF(int iDebut,int *piFin){
    //Clef->Entier
    int bSucces,iFin;
    bSucces=bEntieR(iDebut,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    if(bModeSem && !bAlexClef(iDebut)){
        ErreurEmpiler(eAlexReel,iDebut);
    }
    return(bSucces);
}//bCleF

int bHorairE(int iDebut,int *piFin){
    //Horaire->Reel
    int bSucces,iFin;
    bSucces=bReeL(iDebut,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    if(bModeSem && !bAlexHoraire(iDebut)){
        ErreurEmpiler(eSemHoraire,iDebut);
    }
    return(bSucces);
}//bHorairE

int bInstru1(int iDebut,int *piFin){
    //Instru1->Id.Clef.Reel.Horaire
    int bSucces,iFin,iMilieu,iSuivant,iSuivant2;
    bSucces=bIdentificateuR(iDebut,&iMilieu) && bCleF(iMilieu,&iSuivant) && bReeL(iSuivant,&iSuivant2) && bHorairE(iSuivant2,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    return(bSucces);
}//bInstru1

int bInstru2(int iDebut,int *piFin){
    //Instru2->Entier.Entier
    int bSucces,iFin,iMilieu;
    bSucces=bEntieR(iDebut,&iMilieu) && bEntieR(iMilieu,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    return(bSucces);
}//bInstru2

int bInstru3(int iDebut,int *piFin){
    //Instru3->Reel
    int bSucces,iFin;
    bSucces=bReeL(iDebut,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    return(bSucces);
}//bInstru3

int bInstruS(int iDebut,int *piFin){
    //Instrus->Instru1 || Instru2 || Instru3
    int nChoix3,bSucces,iFin;
    if (bkEclaireuR){
        nChoix3=nAlexInstruS(iDebut);//pré-vision instruction courante: 1 si identificateur, 2 si entier, 3 si reel, et 0 si échec
        switch(nChoix3){
            case  1:	bSucces=bInstru1(iDebut,&iFin);break;
            case  2:	bSucces=bInstru2(iDebut,&iFin);break;
            case  3:	bSucces=bInstru3(iDebut,&iFin);break;
            default:break;
        }
    }else bSucces=bInstru1(iDebut,&iFin) || bInstru2(iDebut,&iFin) || bInstru3(iDebut,&iFin);
    *piFin=(bSucces)? iFin:iDebut;
    return(bSucces);
}//bInstruS

int bAsyntAnalyser(int bModeSemantique){
    Appel0("bAsyntAnalyser");
    //printf("bModeSemantique = %d\n",bModeSemantique);
    bModeSem = bModeSemantique;
    int bSucces = 0;
    int iFin;
    bkEclaireuR=kV;
    bSucces = bProgrammE(1,&iFin);
    Appel1("bAsyntAnalyser");
    
    return bSucces;
}//bAsyntAnalyser


/*
int bAsyntAnalyser(){
    int bSucces = 0;
    int iFin;
    bkEclaireuR=kV;
    bSucces = bProgrammE(1,&iFin);
    
    return bSucces;
}//bAsyntAnalyser
*/


void AsyntAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
	bkEclaireuR=kF;
	bAsyntAmorceR=kV;
}//AsyntAMORCER

void AsyntINITIALISER(){//O(?)
	//relance le présent module
	Assert1("AsyntINITIALISER",bAsyntAmorceR);
}//AsyntINITIALISER

void AsyntTESTER(int iTest){
	//teste le présent module
	int bAnalyser=kF;
	int iFin;
	Appel0(sC2("AsyntTESTER,test n°",sEntier(iTest)));
		nAPPEL=0;
		bkEclaireuR=kV;
		switch (iTest) {
			case  1:	bkEclaireuR=kF;bAnalyser=bProgrammE(1,&iFin);break;
			case  2:	bkEclaireuR=kV;bAnalyser=bProgrammE(1,&iFin);break;
			default:break;
		}
		printf("%s de l'analyse syntaxique après %s.\n",(bAnalyser)? "Succès":"Echec",sPluriel(nAPPEL,"appel"));
	Appel1(sC2("AsyntTESTER,test n°",sEntier(iTest)));
}//AsyntTESTER	

int bCalcuL(int iDebut,int *piFin){
	//Calcul->Reel.Entier.Identificateur
	int bSucces,iFin,iMilieu,iSuivant;
	bSucces=bReeL(iDebut,&iMilieu) && bEntieR(iMilieu,&iSuivant) && bIdentificateuR(iSuivant,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bCalcuL

int bEcriturE(int iDebut,int *piFin){
	//Ecriture->Entier.Identificateur
	int bSucces,iFin,iMilieu;
	bSucces=bEntieR(iDebut,&iMilieu) && bIdentificateuR(iMilieu,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bEcriturE

int bEntieR(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexEntier(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	nAPPEL++;
	si("bEntieR",iDebut);
	return(bSucces);
}//bEntieR

int bFinFichieR(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexFinFichier(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	nAPPEL++;
	si("bFinFichieR",iDebut);
	return(bSucces);
}//bFinFichieR

int bIdentificateuR(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexIdentificateur(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	nAPPEL++;
	si("bIdentificateuR",iDebut);
	return(bSucces);
}//bIdentificateuR

int bInstructioN(int iDebut,int *piFin){
	//Instruction->Lecture || Ecriture || Calcul
	int nChoix3,bSucces,iFin;
	if (bkEclaireuR){
		nChoix3=nAlexInstruction(iDebut);//pré-vision instruction courante: 1 si réel, 2 si entier, 3 si identificateur, et 0 si échec
		switch(nChoix3){
				case  1:	bSucces=bCalcuL(iDebut,&iFin);break;
				case  2:	bSucces=bEcriturE(iDebut,&iFin);break;
				case  3:	bSucces=bLecturE(iDebut,&iFin);break;
				default:break;
		}
	}else bSucces=bCalcuL(iDebut,&iFin) || bEcriturE(iDebut,&iFin) || bLecturE(iDebut,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bInstructioN

int bInstructionS(int iDebut,int *piFin){
	//Instructions->Instruction.Programme
	int bSucces,iFin,iMilieu;
    //bSucces=bInstructioN(iDebut,&iMilieu) && bProgrammE(iMilieu,&iFin);
    bSucces=bInstruS(iDebut,&iMilieu) && bProgrammE(iMilieu,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bInstructionS

int bLecturE(int iDebut,int *piFin){
	//Lecture->Identificateur.Entier
	int bSucces,iFin,iMilieu;
	bSucces=bIdentificateuR(iDebut,&iMilieu) && bEntieR(iMilieu,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bLecturE

int bProgrammE(int iDebut,int *piFin){
	//Programme->Instructions || FinFichier
	int bSucces,iFin,bFinFichier;
	if (bkEclaireuR){
		bFinFichier=bAlexFinFichier(iDebut);
		if (!bFinFichier)
			bSucces=bInstructionS(iDebut,&iFin);
		else bSucces=bFinFichieR(iDebut,&iFin);
	}else bSucces=bInstructionS(iDebut,&iFin) || bFinFichieR(iDebut,&iFin);
	*piFin=(bSucces)? iFin:iDebut;
	return(bSucces);
}//bProgrammE

int bReeL(int iDebut,int *piFin){
	int bSucces;
	bSucces=bAlexReel(iDebut);
	*piFin=(bSucces)? iDebut+1:iDebut;
	nAPPEL++;
	si("bReeL",iDebut);
	return(bSucces);
}//bReeL