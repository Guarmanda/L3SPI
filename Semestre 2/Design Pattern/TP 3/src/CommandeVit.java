
public class CommandeVit extends Commande {
	
	/**
	 * Constructeur de la classe CommandeVit.
	 * @param c La cellule concernée par la commande.
	 */
	public CommandeVit(Cellule c){
		cellule = c;
	}
	
	@Override
	public void executer(){
		cellule.vit();
	}
}
