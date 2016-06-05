#include "Outil.h"
#include "Alex.h"
#include "Deque.h"
#include "Graphe.h"
#include "Cycle.h"
#include "Flot.h"
#include "Matrice.h"
#include "Tas.h"
#include "Asynt.h"
#include "Erreur.h"

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module)
	OutilAMORCER();
	AlexAMORCER();
	AsyntAMORCER();
	ErreurAMORCER();
	//DequeAMORCER();
	//GrapheAMORCER();
	//CycleAMORCER();
	//FlotAMORCER();
	//MatriceAMORCER();
	//TasAMORCER();
}//ModuleAmorceR


void Compiler(char *sSource){
    int bSucces = 1;
    
    bSucces = bAlexAnalyser(sSource);
    //bSucces = bAsyntAnalyser();
    bSucces = bSucces && bAsyntAnalyser(asSyntaxique);
    bSucces = bSucces && bAsyntAnalyser(asSemantique);
    bSucces = bSucces && bAsyntAnalyser(asGenerationCode);
    
    ErreurDenoncer();
    
}

int main (int argc, const char * argv[]) {
	graf *pgG;
	int  bCheminer,bCircuit,uSommet;
	int kbAfficher=1;
	const int ksSource=1;
	Appel0("");
		ModuleAmorceR();
		//OutilTESTER(55);
	    //AlexTESTER(2);
	
		int i=1 ;
		for (i=1; i<=4; i++)
		    switch(i){
			case 1 : Compiler("AZE 5 5.2 15.50$"); break;
			case 2 : Compiler("AZE 5 5.2 25.50$"); break;
			case 3 : Compiler("AZE 5 5.2 15.60$"); break;
			case 4 : Compiler("AZE 5 5.2 25.60$");
		    }
    
    
		if (0) for (uSommet=1;uSommet<10;uSommet++){
			GrapheCreer(uSommet,&pgG);
				GrapheAfficher(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
				bCheminer=bGrapheCheminerCourt(pgG,ksSource,pgG->nSommetEnTout,kbAfficher);
				if (!kbAfficher)
					printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
			GrapheCreer(0,&pgG);
		}
		if (0) for (uSommet=10;uSommet<=10;uSommet++){
			GrapheCreer(uSommet,&pgG);
				GrapheArquer(pgG, 1, 4);
				bGrapheDesarquer(pgG, 4, 2);
				GrapheAfficher(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
				bCheminer=bGrapheCheminerLong(pgG,ksSource,pgG->nSommetEnTout,kbAfficher);
				if (!kbAfficher)
					printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
			GrapheCreer(0,&pgG);
		}
		if (0) for (uSommet=3;uSommet<10;uSommet++){
			GrapheCreer(uSommet, &pgG);
				GrapheInverser(pgG);
				GrapheAfficher2(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
				bCircuit=bGrapheCircuite(pgG);
				s(sC3bp("Il",sNie("y a",!bCircuit,"un","aucun"),"circuit"));
			GrapheCreer(0,&pgG);
		}
		//if (0) FlotTESTER(11);
		if (0){
			GrapheCreer(4,&pgG);
				GrapheEtager(pgG);
				GrapheAfficher(pgG,sC4b("Le graphe étagé a",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
			GrapheCreer(0,&pgG);
		}
	Appel1("");
    return 0;
}
