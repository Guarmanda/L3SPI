
public class CelluleEtatVivante implements CelluleEtat{
	// Instance représentant le CelluleEtatMort unique.
	private static CelluleEtatVivante etat = null;
	
	/**
	 * Constructeur de la classe CelluleEtatVivante rendu privé.
	 */
	private CelluleEtatVivante(){
		
	}
	
	/**
	 * Méthode permetant de récupérer l'unique instance de la classe.
	 * @return L'unique instance de la classe.
	 */
	public static CelluleEtatVivante getInstance(){
		if(etat == null)
			etat = new CelluleEtatVivante();
		return etat;
	}
	
	@Override
	public CelluleEtat vit(){
		return this;
	}
	@Override
	public CelluleEtat meurt(){
		return CelluleEtatMort.getInstance();
	}
	@Override
	public boolean estVivante(){
		return true;
	}
	@Override
	public void accepte(Visiteur visiteur, Cellule cellule){
		visiteur.VisiteCelluleVivante(cellule);
	}

}
