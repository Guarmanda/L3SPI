
public class JeuDeLaVieTer implements Observateur {
	// Jeu courant
	private JeuDeLaVie jeu;
	// Génération courante
	private int gen=0;
	
	/**
	 * Constructeur de la classe JeuDeLaVieUI.
	 * @param jeu Le jeu courant.
	 */
	public JeuDeLaVieTer(JeuDeLaVie jeu){
		this.jeu = jeu;
	}
	
	@Override
	public void actualise(){
		this.gen++;
		System.out.print("Generation n°"+Integer.toString(this.gen)+
				":\nIl reste "+Integer.toString(jeu.nombreCellulesVivante())+
				" Cellule(s) vivante(s).\n");
	}
}
