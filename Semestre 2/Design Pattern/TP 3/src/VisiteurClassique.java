
public class VisiteurClassique extends Visiteur {
	
	// Instance représentant le VisiteurClassique unique.
	private static VisiteurClassique visiteur = null;
	
	/**
	* Constructeur de la classe VisiteurClassique rendu privé.
	*/
	private VisiteurClassique(JeuDeLaVie jeu){
		super(jeu);
	}
	
	/**
	 * Méthode permetant de récupérer l'unique instance de la classe.
	 * @return L'unique instance de la classe.
	 */
	public static VisiteurClassique getInstance(JeuDeLaVie jeu){
		if(visiteur == null)
			visiteur = new VisiteurClassique(jeu);
		return visiteur;
	}
	
	@Override
	public void VisiteCelluleVivante(Cellule cellule) {
		int tmp = cellule.nombreVoisinesVivante(jeu);
		if(tmp<2 || tmp>3)
			jeu.ajouteCommande(new CommandeMeurt(cellule));
	}

	@Override
	public void VisiteCelluleMorte(Cellule cellule) {
		int tmp = cellule.nombreVoisinesVivante(jeu);
		if(tmp==3)
			jeu.ajouteCommande(new CommandeVit(cellule));
	}
}
