
public abstract class Commande {
	// Cellule concernée par la commande.
	protected Cellule cellule;
	/**
	 * Méthode executant la commande.
	 */
	public abstract void executer();
}
