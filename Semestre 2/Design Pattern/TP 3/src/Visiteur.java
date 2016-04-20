
public abstract class Visiteur {
	// Jeu courant
	protected JeuDeLaVie jeu;
	
	/**
	 * Constructeur de la classe Visiteur.
	 * @param jeu Le jeu courant.
	 */
	public Visiteur(JeuDeLaVie jeu){
		this.jeu = jeu;
	}
	
	/**
	 * Méthode assignant une commande à une cellule vivante.
	 * @param cellule La cellule concernée.
	 */
	public abstract void VisiteCelluleVivante(Cellule cellule);
	/**
	 * Méthode assignant une commande à une cellule morte.
	 * @param cellule La cellule concernée.
	 */
	public abstract void VisiteCelluleMorte(Cellule cellule);
}
