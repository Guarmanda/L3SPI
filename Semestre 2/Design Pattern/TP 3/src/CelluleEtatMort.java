
public class CelluleEtatMort implements CelluleEtat {
	// Instance représentant le CelluleEtatMort unique.
	private static CelluleEtatMort etat = null;
	
	/**
	 * Constructeur de la classe CelluleEtatMort rendu privé.
	 */
	private CelluleEtatMort(){
		
	}
	
	/**
	 * Méthode permetant de récupérer l'unique instance de la classe.
	 * @return L'unique instance de la classe.
	 */
	public static CelluleEtatMort getInstance(){
		if(etat == null)
			etat = new CelluleEtatMort();
		return etat;
	}
	
	@Override
	public CelluleEtat vit() {
		return CelluleEtatVivante.getInstance();
	}
	@Override
	public CelluleEtat meurt() {
		return this;
	}
	@Override
	public boolean estVivante() {
		return false;
	}
	@Override
	public void accepte(Visiteur visiteur, Cellule cellule){
		visiteur.VisiteCelluleMorte(cellule);
	}

}
