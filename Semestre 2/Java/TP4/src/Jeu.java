import java.util.List;
import java.util.LinkedList;


public class Jeu {
	private Damier damier;
	private List<Glarks> listeDesGlarks;
	
	
	public Jeu(){
		listeDesGlarks = new LinkedList<Glarks>();
	}
	
	public void initialiseToi(){
		damier = new Damier(10);
		
	}
	
	public void lanceToi(){
		
		for(Glarks c : listeDesGlarks){
			if (c.getEnergie() == 0) {
				c.vasY();
			}
		}
	}
	
}