#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#define kF 0 //constante booléenne FALSE
#define kV 1 //constante booléenne TRUE
#define kuByteMax 255
#define kuByteLim 256
#define  kE0 1
#define  kE1 10
#define  kE2 100
#define  kE3 1000
#define  kE4 10000
#define  kE5 100000
#define  kE6 1000000
#define  kE7 10000000
#define  kE8 100000000
#define  kE9 1000000000
#define kE10 10000000000
#define kE11 100000000000
#define kE12 1000000000000
#define kE13 10000000000000
#define kE14 100000000000000
#define kE15 1000000000000000
#define kE16 10000000000000000
#define kE17 100000000000000000
#define kE18 1000000000000000000
#define kE19 10000000000000000000
#define kE20 100000000000000000000
#define kE21 1000000000000000000000
#define kE22 10000000000000000000000
#define kE23 100000000000000000000000
#define kE24 1000000000000000000000000
#define kE25 10000000000000000000000000
#define kE26 100000000000000000000000000
#define kE27 1000000000000000000000000000
#define kE28 10000000000000000000000000000
#define kE29 100000000000000000000000000000
#define kE30 1000000000000000000000000000000
#define kE31 10000000000000000000000000000000
#define kE32 100000000000000000000000000000000
#define kuIntegerMax INT_MAX //constante prédéfinie dans la bibliothèque <limits.h>
#define kxLongintMax LONG_MAX //constante prédéfinie dans la bibliothèque <limits.h>
#define kyLongintMin LONG_MIN //constante prédéfinie dans la bibliothèque <limits.h>
#define kuMajusculeOffset 1 //A est la 1ère lettre de l'alphabet
#define kuMinusculeOffset 27 //a est la 27ème lettre de l'alphabet à 52 lettres obtenu en complétant les majuscules par les minuscules. 
void b(int bBooleen);//affiche "faux" si bBooleen=0, et "vrai" sinon.
void i(long yEntier1);//affiche la valeur de yEntier1
void ii(long yEntier1,long yEntier2);//affiche les valeurs des 2 entiers
void iii(long yEntier1,long yEntier2,long yEntier3);//affiche les valeurs des 3 entiers
void s(char *sString);//affiche la valeur de la chaîne sString
void sb(char *sString,int bBooleen);
void si(char *sString,long yEntier1);//affiche la valeur de sString puis celle de yEntier1: se("eA",eA) affiche "eA:2" si eA vaut 2
void sii(char *sString,long yEntier1,long yEntier2);
void siii(char *sString,long yEntier1,long yEntier2,long yEntier3);
void siiii(char *sString,long yEntier1,long yEntier2,long yEntier3,long yEntier4);
void sr(char *sString,double dReel1);//affiche la valeur de sString puis celle du réel dReel1: se("eA",dA) affiche dA:2.5 si dA vaut 2.5
void srr(char *sString,double dReel1,double dReel2);
void srrr(char *sString,double dReel1,double dReel2,double dReel3);
void ss(char *sString1,char *sString2);//affiche sString1 et sString2 séparés par une virgule
void sss(char *sString1,char *sString2,char *sString3);
void ssss(char *sString1,char *sString2,char *sString3,char *sString4);
void sssss(char *sString1,char *sString2,char *sString3,char *sString4,char *sString5);
long zAbs(long yEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction abs() du C qui rend une valeur négative
void Appel0(char *sMessage);//associer à Appel1;à placer en tête de routine (pour tracer les appels de routine)
void Appel1(char *sQuoi);//associer à Appel0;à placer en fin de routine (pour tracer les appels de routine)
void Assert1(char *sContexte,int bAssertion1);//comme assert() du langage C, mais affiche sContexte si bAssertion1 est faux
void Assert2(char *sContexte,int bAssertion1,int bAssertion2);//comme assert(bAssertion1 && bAssertion2);affiche sContexte si une assertion est fausse.
void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3);
void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
int bBit(char cCaractere);//rend vrai ssi cCaractere est '0' ou '1'
int bBool(long yEntier);//rend vrai ssi yEntier vaut 0 ou 1
char *sBool(long yValeur);//rend "faux" si yValeur est nul, et "vrai" sinon.
int bByte(long yEntier);//0 ≤ yEntier ≤ 255
char *sC(char cAlphaNumeriqueOuEspace);//convertit un char en string
char *sC1(char *sA);//vérifie sA!=0 puis rend sA
char *sC1p(char *sA);//complète sA par un point terminal
char *sC2(char *sA,char *sB);
char *sC2b(char *sA,char *sB);//concatène en ajoutant un blanc entre sA et sB
char *sC2bp(char *sA,char *sB);//blanc entre sA et sB et point terminal
char *sC2p(char *sA,char *sB);//point terminal
char *sC2v(char *sA,char *sB);//concatène en ajoutant une virgule entre sA et sB
char *sC3(char *sA,char *sB,char *sC);
char *sC3b(char *sA,char *sB,char *sC);
char *sC3bp(char *sA,char *sB,char *sC);
char *sC3p(char *sA,char *sB,char *sC);
char *sC3v(char *sA,char *sB,char *sC);
char *sC4(char *sA,char *sB,char *sC,char *sD);
char *sC4b(char *sA,char *sB,char *sC,char *sD);
char *sC4bp(char *sA,char *sB,char *sC,char *sD);
char *sC4p(char *sA,char *sB,char *sC,char *sD);
char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
int nCaractere(char *sString);//rend le nombre de caractères, contrairement à strlen() qui rend le nombre de CODES caractères,donc 2 pour "é", pas 1. 
int bChiffre(char cCaractere);//'0'..'9',comme bDecit
int nChainePos(char cQuoi,char *sDansQuoi);//rend le rang0 de cQuoi dans sDansQuoi, ou -1 si échec
char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative);//cf (bOptionSinonAlternative)? sOption: sAlternative
char *sChoix0(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide
void Confirmer(char *sMessage);//affiche sMessage et demande à l'utilisateur de valider
char *sCouple(long yEntierA,long yEntierB);//eg "(3,5)" 
void Croissant(double dMinInclus,double dDedans,double dMaxInclus);//vérifie dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissant(double dMinInclus,double dDedans,double dMaxInclus);//rend vrai ssi dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);//vérifie dMinInclus < dDedans < dMaxInclus
void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);
void Croit(long yMinInclus,long yDedans,long yMaxInclus);//vérifie iMinInclus ≤ iDedans ≤ iMaxInclus
int bCroit(long yMinInclus,long yDedans,long yMaxInclus);
void CroitStrict(long yMinExclu,long yDedans,long yMaxExclu);
int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu);
int bDecit(char cCaractere);//alias bChiffre
void Dis(char *sString);//affiche la valeur de la chaîne et ajoute un point final.
char *sE(int nEspace);//rend nEspace blancs consécutifs
char *sEntier(long yEntier);
char *sEntier2(long yEntier);//résultat sur 2 caractères
char *sEntier3(long yEntier);//résultat sur 3 caractères
char *sEntierAvecSigne(long yEntier);// "+5" ou "-5" ou " 0"
char *sEst(int bAssertion);//rend "est" ou "n'est pas"
int bFaux(int iQuelconque);//vrai ssi iQuelconque==0
long zFib(int nIndex);//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0
void FlipFlop(int bNouvelEtat,int *pbFlipFlop);// "pb" pour "pointeur sur booléen"
char *sFois(int nFois,char cMotif);//rend cMotif juxtaposé nFois
int nHasard(int uBorneLim);//[0..uBorneLim[
int uHasard(int uBorneMax);//[1..uBorneMax]
int bImpair(int iEntier);
double rInf(double dA,double dB);//inf(dA,dB)
long yInf(long yA,long yB);//identique à yMin(yA,yB)
int bLettre(char cCaractere);
void Ligne();//passe à la ligne
int bLigne();//passe à la ligne et rend vrai
double rLog(double dN);//logarithme népérien
double rLog2(double dN);//logarithme en base 2
double rMax(double dA,double dB);//sup(dA,ddB)
long yMax(long yA,long yB);//sup(yA,yB)
void MemIntRaz(int piMemOrigine[],int nItemEnTout);
void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur);
void MemLongRaz(int pyMemOrigine[],int nItemEnTout);
void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur);
int bMajuscule(char cCaractere);
double rMin(double dA,double dB);//inf(dA,dB)
long yMin(long yA,long yB);//inf(yA,yB)
int bMinuscule(char cCaractere);
int uModulo1(int uDividende,int uDiviseur);//résultat dans [1..uDiviseur];calcule un modulo classique,mais 0 est remplacé par uDiviseur
char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation);//encadre sVerbe avec "ne" et sNegation, ou complète avec sAffirmation 
void OutilAMORCER();
void OutilINITIALISER();
void OutilTESTER(int iTest);
char *sP(char *sEntreParenthese);//rend sEntreParenthese entre 2 parenthèses,eg sP("oui") rend "(oui)"
int bPair(int iEntier);
char *sPar3(long yEntier);//convertit yEntier en chaîne en séparant les groupes de 3 chiffres, eg sPar3(12345) rend "12 345".
char *sPas(char *sVerbe,int bNegativer);//encadre avec "ne" et "pas" si bNegativer
void Pause();//suspend l'exécution et attend une frappe clavier minimale
long zPgcd(long xA,long xB);//plus grand commun diviseur
char *sPluriel(long zEffectif,char *sSingulier);//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges".
long zPpcm(long xA,long xB);//plus petit commun multiple
int mPoidsFort(long yEntier);//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2
long zPuissance(long yOperande,int nExposant);//nExposant positif ou nul
char *sSigne(long yEntier);//"+" ou "-" ou " " selon le signe de yEntier ("+" pour yEntier=0)
long muSigne(int bSigneInverser,long yValeur);//si bSigneInverser est vrai,rend -yValeur;sinon,rend yValeur.
void Stop(int byMassacre);//sortie catastrophe;affiche byMassacre compris entre 0 et 255 puis stoppe l'exécution.
double rSup(double dA,double dB);//identique à rMax(dA,dB)
long ySup(long yA,long yB);//identique à yMax(yA,yB)
void Titrer(char *sTitre);//affiche sTitre centré sur 40 caractères et passe à la ligne
int bVecteurContient(int nEnquis,int nCardinal,int iVecteur[]);
void VecteurVoir(char *sNom,int piQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les valeurs du vecteurs d'entiers de type integer
void VecteurVoyr(char *sNom,long pyQuelVecteur[],long zIndexMin,long zIndexMax);//affiche les valeurs du vecteurs d'entiers de type longint
int bVoyelle(char *sString,int nCodeCaractereRg);
void Vrai(int bAssertion);//vrai ssi iQuelconque!=0
int bVrai(int iQuelconque);//rend 1 ssi iQuelconque est non nul;rend 0 sinon
void Vrai2(int bAssertion1,int bAssertion2);
void Vrai3(int bAssertion1,int bAssertion2,int bAssertion3);
void Vrai4(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Vrai5(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Vrai6(int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void While(long zIterationMax);//prend note du nombre maximum d'itérations à exécuter dans le while qui suit l'appel de cette routine
int bWhile(int bExpressionBooleenne);//rend bExpressionBooleenne après avoir vérifié que l'itération en cours ne dépasse pas zIterationMax spécifié li-1

