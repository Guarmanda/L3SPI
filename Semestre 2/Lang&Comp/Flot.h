void FlotAfficher(graf *pgG,int bTout,char *sMessage);//si non bTout,censure les arcs dont le flot est nul
void FlotAMORCER();
int bFlotCalculer(graf *pgG,int sSource,int sTrappe,int nFlotRequis);
void FlotCapaciter(graf *pgG,int sOrigine,int sDestination,int nCapacitehMaximale);//attribue une capacité
void FlotCouter1(graf *pgG,int sOrigine,int sDestination,int nCout);//attribue un coût (champ nCout)
void FlotCouter2(graf *pgG,int sOrigine,int sDestination,int nCout);//attribue un coût (champ nPrix)
void FlotINITIALISER();
void FlotTESTER(int iTest);
