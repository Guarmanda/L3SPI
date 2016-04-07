import java.util.ArrayList;
import java.util.List;


public class Ville {
	private String nom;
	private List<Personne> habitants;
	
	public Ville(String nom){
		super();
		this.nom = nom;
		habitants = new ArrayList<Personne>();
	}
	
	/**
	 * @return the nom
	 */
	public String getNom(){
		return nom;
	}
	/**
	 * @return the habitants
	 */
	public List<Personne> getHabitants(){
		return habitants;
	}
	
	public int getPopulation(){
		return habitants.size();
	}
	
	public void ajoutehabitant(Personne p){
		this.habitants.add(p);
	}
}
