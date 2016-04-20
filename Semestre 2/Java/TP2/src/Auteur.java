/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 10:05:13 CET 2016
*
*/
public class Auteur {
	private String nom;
	private Date naissance;
	private Date deces;

	public Auteur(String unNom, Date uneDateDeNaissance){
		nom = unNom;
		naissance = uneDateDeNaissance;
		deces = null;
	}

	public Auteur(String unNom, Date uneDateDeNaissance, Date uneDateDeDeces){
		this(unNom, uneDateDeNaissance);
		deces = uneDateDeDeces;
	}

	public String getNom(){
		return nom;
	}
	public Date getNaissance(){
		return naissance;
	}
	public Date getDeces(){
		return deces;
	}

	public boolean equals(Object o) throws ClassCastException{
		if (!(o instanceof Auteur))
			throw new ClassCastException();
		String unNom = ((Auteur) o).getNom();
		Date uneDateDeNaissance = ((Auteur) o).getNaissance();
		Date uneDateDeDeces = ((Auteur) o).getDeces();
		if ( unNom.equals(nom))
			if ( uneDateDeNaissance.equals(naissance))
				if ( uneDateDeDeces.equals(deces))
					return true;
		return false;
	}

	public String toString(){
		return nom.toString();
	}
}