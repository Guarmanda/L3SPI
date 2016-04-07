
public class Personne {
	private String nom;
	private String profession;
	private int age;
	private Ville ville;
	
	public Personne(String nom, String profession, int age, Ville ville){
		this.nom = nom;
		this.age = age;
		this.ville = ville;
		this.profession = profession;
		this.ville.ajoutehabitant(this);
	}
	
	/**
	 * @return the nom
	 */
	public String getNom(){
		return nom;
	}
	/**
	 * @return the profession
	 */
	public String getProfession(){
		return profession;
	}
	/**
	 * @return the age
	 */
	public int getAge(){
		return age;
	}
	/**
	 * @return the ville
	 */
	public Ville getVille(){
		return ville;
	}
	
	public String toString(){
		return nom+", "+profession+", "+age;
	}
}
