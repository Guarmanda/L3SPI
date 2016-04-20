
public interface CelluleEtat {
	/**
	 * Méthode retournant l'état "Vivante".
	 * @return Un CelluleEtatVivante
	 */
	public CelluleEtat vit();
	/**
	 * Méthode retournant l'état "Morte".
	 * @return Un CelluleEtatMorte
	 */
	public CelluleEtat meurt();
	/**
	 * Méthode vérifiant l'état.
	 * @return Vrai si l'état courant est "Vivante", faux sinon.
	 */
	public boolean estVivante();
	/**
	 * Méthode permetant à l'état courant d'accepter un visiteur.
	 * @param visiteur Le visiteur à donner.
	 * @param cellule La cellule concernée.
	 */
	public void accepte(Visiteur visiteur, Cellule cellule);
}
