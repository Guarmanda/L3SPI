
public class CommandeMeurt extends Commande {
	
	/**
	 * Constructeur de la classe CommandeMeurt.
	 * @param c La cellule concernée par la commande.
	 */
	public CommandeMeurt(Cellule c){
		cellule = c;
	}
	
	@Override
	public void executer(){
		cellule.meurt();
	}
}
