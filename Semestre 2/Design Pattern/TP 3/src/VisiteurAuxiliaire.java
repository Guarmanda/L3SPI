
public class VisiteurAuxiliaire extends Visiteur {

	// Instance représentant le VisiteurAuxiliaire unique.
	private static VisiteurAuxiliaire visiteur = null;
	
	/**
	* Constructeur de la classe VisiteurAuxiliaire rendu privé.
	*/
	public VisiteurAuxiliaire(JeuDeLaVie jeu){
		super(jeu);
	}
	
	/**
	 * Méthode permetant de récupérer l'unique instance de la classe.
	 * @return L'unique instance de la classe.
	 */
	public static VisiteurAuxiliaire getInstance(JeuDeLaVie jeu){
		if(visiteur == null)
			visiteur = new VisiteurAuxiliaire(jeu);
		return visiteur;
	}
	
	@Override
	public void VisiteCelluleVivante(Cellule cellule) {
		int tmp = cellule.nombreVoisinesVivante(jeu);
		if(tmp<3 || tmp==5)
			jeu.ajouteCommande(new CommandeMeurt(cellule));
	}

	@Override
	public void VisiteCelluleMorte(Cellule cellule) {
		int tmp = cellule.nombreVoisinesVivante(jeu);
		if(tmp==3 || tmp>=6)
			jeu.ajouteCommande(new CommandeVit(cellule));
	}
}
