#define knArcLiM 100
#define knSommetLiM 32
typedef struct{
	int nSommetEnTout;
	int nArcEnTout;
	int aHed[knSommetLiM];//numéros d'arcs
	int sSuk[knArcLiM];//sommet destination de l'arc courant
	int aDeh[knSommetLiM];//numéros d'arcs ds le graphe inverse
	int sKus[knArcLiM];//sommet origine de l'arc courant
	int aInv[knArcLiM];//arc inverse aL associé à l'arc direct aK
	int nCapa[knArcLiM];//capacité maximale de l'arc courant
	int nCout[knArcLiM];//coût n°1 associé à l'arc courant
	int nPrix[knArcLiM];//coût n°2 associé à l'arc courant
	int aArcTo[knArcLiM];
	int nAugVal[knArcLiM];
	int coulh[knArcLiM];
	int sPer[knSommetLiM];
	int nPhi[knArcLiM];
	int nVal[knArcLiM];
} graf;
int bGraphe(graf *pgG);//O(A)
void GrapheAfficher(graf *pgG,char *sMessage);
void GrapheAfficher0(graf *pgG,int bDontCouleur,char *sMessage);
void GrapheAfficher2(graf *pgG,char *sMessage);
void GrapheAfficher3(graf *pgG,char *sMessage);
void GrapheAMORCER();
int bGrapheArc(graf gG,int sOrigine,int sDestination);//O(S)
void GrapheArquer(graf *pgG,int sOrigine,int sDestination);//O(A)
int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bAfficher);//O(S2)
int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int bAfficher);//O(S2)
int bGrapheCircuite(graf *pgG);//O(A)
void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur);
int nGrapheCouleur(graf gG,int sOrigine,int sDestination);//O(S)
void GrapheCreer(int nSommet,graf **ppgG);
void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]);
void GrapheDecrire(graf *pgG);//O(A)
void GrapheDedoubler(graf *pgG);//O(A)
int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheDesarquerTout(graf *pgG,int sAccroche);//retire tout arc lié à sAccroche
void GrapheEtager(graf *pgG);//O(SA)
int bGrapheEulerien(graf *pgG,int szSource,int szTrappe);//O(A);sz:sommet ou 0
void GrapheINITIALISER();
void GrapheInverser(graf *pgG);//O(A)
void GraphePolariser(graf *pgG,int *psSource,int *psTrappe);//O(A)
void GraphePonderer(graf *pgG);//O(A)
int bGrapheSimple(graf *pgG);//O(A)
void GrapheSommer(graf *pgG,int bEmpilerSinonDepiler);//O(1)
int bGrapheSommet(graf *pgG,int sSommet);
int bGrapheSymetrique(graf gG);
void GrapheSymetriser(graf *pgG);
void GrapheTESTER(int iTest);
