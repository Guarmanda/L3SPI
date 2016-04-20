import java.util.List;
import java.util.LinkedList;


public class JeuDeLaVie implements Observable{
	// Matrice de cellule
	private Cellule[][] grille;
	// Dimention horizontal de la grille
	private int xMax;
	// Dimantion verticale de la grille
	private int yMax;
	// Liste des observateurs
	private List<Observateur> observateurs;
	// Liste des commandes
	private List<Commande> commandes;
	// Visiteur du jeu
	private Visiteur visiteur;
	// Vitesse à laquelle la génération siuvante est calculée
	private int vitesse;
	// Flag représentant l'activité du jeu
	private boolean flag;
	
	/**
	 * Constructeur de la classe JeuDeLaVie.
	 * @param x Dimention horizontal de la grille.
	 * @param y Dimantion verticale de la grille.
	 */
	public JeuDeLaVie(int x, int y){
		xMax = x;
		yMax = y;
		vitesse = 1000;
		flag = true;
		grille = new Cellule[xMax][yMax];
		observateurs = new LinkedList<Observateur>();
		commandes = new LinkedList<Commande>();
	}
	
	/**
	 * Méthode initialisent la grille de jeu. 
	 */
	public void initialiseGrille(){
		int x;
		int y;
		
		for(x=0 ; x<xMax ; x++){
			for(y=0 ; y<yMax ; y++){
				if(Math.random() < 0.5)
					grille[x][y] = new Cellule(x,y,CelluleEtatMort.getInstance());
				else
					grille[x][y] = new Cellule(x,y,CelluleEtatVivante.getInstance());
			}
		}
	}
	
	/**
	 * Méthode retournant la cellule aux coordonnées données.
	 * @param x Abscice de la cellule.
	 * @param y Ordonné de la cellule.
	 * @return La cellule aux coordonnées données, revoit null si les coordonnées sont incorrecte
	 */
	public Cellule getGrilleXY(int x, int y){
		if(x<0 || y<0 || x>=xMax || y>=yMax)
			return null;
		return grille[x][y];
	}
	
	/**
	 * Méthode retournant la dimention horizontale de la grille.
	 * @return La dimention horizontale de la grille.
	 */
	public int getXMax(){
		return xMax;
	}
	/**
	 * Méthode retournant la dimention verticale de la grille.
	 * @return La dimention verticale de la grille.
	 */
	public int getYMax(){
		return yMax;
	}
	
	@Override
	public void attacheObservateur(Observateur o){
		observateurs.add(o);
	}
	@Override
	public void detacheObservateur(Observateur o){
		observateurs.remove(o);
	}
	@Override
	public void notifieObservateur(){
		for(Observateur o : observateurs)
			o.actualise();
	}
	
	/**
	 * Méthode ajoutant une commande à la liste des commandes.
	 * @param c La commande à ajouter.
	 */
	public void ajouteCommande(Commande c){
		commandes.add(c);
	}
	
	/**
	 * Méthode executant toutes les commandes de la liste des commandes, puis efface la liste.
	 */
	public void executeCommandes(){
		for(Commande c : commandes)
			c.executer();
		commandes.clear();
	}
	/**
	 * Méthode modifiant le visiteur.
	 * @param visiteur Le nouveau visiteur.
	 */
	public void setVisiteur(Visiteur visiteur){
		this.visiteur = visiteur;
	}
	
	/**
	 * Méthode distribuant le visiteur à chaque cellule de la grille.
	 */
	public void distribueVisiteur(){
		for(int x=0 ; x<xMax ; x++){
			for(int y=0 ; y<yMax ; y++){
				getGrilleXY(x,y).accepte(visiteur);
			}
		}
	}
	
	/**
	 * Méthode calculant la prochaine génération du jeu.
	 */
	public void calculerGenerationSuivante(){
		distribueVisiteur();
		executeCommandes();
		notifieObservateur();
	}
	
	/**
	 * Méthode calculant le nombre de cellules encores vivantes.
	 * @return Le nombre de cellules encores vivantes.
	 */
	public int nombreCellulesVivante(){
		int nb=0;
		int x;
		int y;
		
		for(x=0 ; x<xMax ; x++)
			for(y=0 ; y<yMax ; y++)
				if(grille[x][y].estVivante())
					nb++;
		return nb;
	}
	
	/**
	 * Méthode modifiant le visiteur courant.
	 */
	public void changeVisiteur(){
		if (this.visiteur.getClass().getName().equals("VisiteurClassique"))
			this.visiteur = VisiteurAuxiliaire.getInstance(this);
		else 
			this.visiteur = VisiteurClassique.getInstance(this);
	}
	
	/**
	 * Méthode modifiant le flag.
	 * @param f Le nouveau flag.
	 */
	public void changeFlag(boolean f){
		this.flag = f;
	}
	
	/**
	 * Méthode retournant le flag.
	 * @return Le flag courant.
	 */
	public boolean getFlag(){
		return this.flag;
	}
	
	/**
	 * Méthode modifiant la vitesse courante.
	 * @param t Le temps.
	 */
	public void setVitesse(int t){
		this.vitesse = 2000-t;
	}
	
	/**
	 * Méthode main.
	 * @param args
	 */
	public static void main(String[] args){
		JeuDeLaVie jeu = new JeuDeLaVie(200,200);
		jeu.initialiseGrille();
		
		
		Visiteur v = VisiteurClassique.getInstance(jeu);
		jeu.setVisiteur(v);
		
		Observateur jeuUI = new JeuDeLaVieUI(jeu);
		Observateur jeuTer = new JeuDeLaVieTer(jeu);
		jeu.attacheObservateur(jeuUI);
		jeu.attacheObservateur(jeuTer);
		
		
		while(true){
			try{
				Thread.sleep(jeu.vitesse);
			}
			catch(InterruptedException e){
				e.printStackTrace();
			}
			if(jeu.getFlag()){
				jeu.calculerGenerationSuivante();
			}
		}
	}
}
