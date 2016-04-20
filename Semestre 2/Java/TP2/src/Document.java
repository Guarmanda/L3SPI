/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 11:05:25 CET 2016
*
*/
public class Document {
	private Auteur auteur;
	private String titre;
	private String etat;

	public Document(Auteur unAuteur, String unTitre){
		auteur = unAuteur;
		titre = unTitre;
		etat = "disponible";
	}

	public Auteur getAuteur(){
		return auteur;
	}
	public String getTitre(){
		return titre;
	}
	public String getEtat(){
		return etat;
	}
	public void modifierEtat(){
		if (etat.equals("disponible"))
			etat = "emprunté";
		else
			etat = "disponible";
	}

	public boolean equals(Object o) throws ClassCastException{
		if (!(o instanceof Document))
			throw new ClassCastException();
		Auteur unAuteur = ((Document) o).getAuteur();
		String unTitre = ((Document) o).getTitre();
		if (unAuteur.equals(auteur))
			if (unTitre.equals(titre))
				return true;
		return false;
	}
	public String toString(){
		return titre+", écrit par "+auteur+", est "+etat+".";
	}


}