
public class Cellule {
	// Abscisse de la cellule
	private int x;
	// Ordonné de la cellule
	private int y;
	// Etat de la cellule
	private CelluleEtat etat;
	
	/**
	 * Constructeur de la classe Cellule.
	 * @param x Abscisse de la cellule.
	 * @param y Ordonné de la cellule.
	 * @param etat Etat de la cellule.
	 */
	public Cellule(int x, int y, CelluleEtat etat){
		this.x = x;
		this.y = y;
		this.etat = etat;
	}
	
//	/**
//	 * méthode calculant le nombre de cellule voisine vivante.
//	 * @param jeu Objet contenant la matrice de jeu.
//	 * @return le nombre de cellule voisine vivante.
//	 */
//	public int nombreVoisinesVivante(JeuDeLaVie jeu){
//		int nb=0;
//		int xtmp;
//		int ytmp;
//		
//		for(xtmp = x-1 ; xtmp <= x+1 ; xtmp++){
//			for(ytmp = y-1 ; ytmp <= x+1 ; ytmp++){
//				if (xtmp!=x || ytmp!=y){
//					Cellule uneCellule = jeu.getGrilleXY(xtmp,ytmp);
//					if(uneCellule != null)
//						if(uneCellule.estVivante())
//							nb+=1;
//				}
//			}
//		}
//		return nb;
//	}
	
	/**
	 * Méthode calculant le nombre de cellule voisine vivante.
	 * @param jeu Objet contenant la matrice de jeu.
	 * @return Le nombre de cellule voisine vivante.
	 */
	public int nombreVoisinesVivante(JeuDeLaVie jeu){
		int nb=0;
			
		Cellule uneCellule = jeu.getGrilleXY(x-1,y-1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x-1,y);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x-1,y+1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x,y-1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x,y+1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x+1,y-1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x+1,y);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		uneCellule = jeu.getGrilleXY(x+1,y+1);
		if(uneCellule != null)
			if(uneCellule.estVivante())
				nb+=1;
		
		return nb;
	}
	
	/**
	 * Méthode modifiant l'état de la cellule à "vivante".
	 */
	public void vit(){
		etat = CelluleEtatVivante.getInstance();
	}
	/**
	 * Méthode modifiant l'état de la cellule à "morte".
	 */
	public void meurt(){
		etat = CelluleEtatMort.getInstance();
	}
	/**
	 * Méthode vérifiant l'état de la cellule.
	 * @return vrai si la cellule est vivante, faux sinon.
	 */
	public boolean estVivante(){
		return etat.estVivante();
	}
	/**
	 * Méthode permetant à la cellule d'accepter un visiteur.
	 * @param visiteur Le visiteur à donner.
	 */
	public void accepte(Visiteur visiteur){
		etat.accepte(visiteur, this);
	}
}
