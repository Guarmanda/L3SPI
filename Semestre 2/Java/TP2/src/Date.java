/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 09:06:33 CET 2016
*
*/

class InvalidDateException extends Exception {
	private String msg;
	public InvalidDateException(String m){
		msg = m;
	}

	public String toString(){
		return "Exception InvalidDateException "+msg;
	}
}


public class Date implements Comparable {
	private int jour;
	private int mois;
	private int annee;
	
	public Date(int unJour, int unMois, int uneAnnee) throws InvalidDateException{
		if ((unJour > 31) || (unJour < 1))
			throw new InvalidDateException("Jour invalide.");
		if ((unMois > 12) || (unMois < 1))
			throw new InvalidDateException("Mois invalide.");
		
		jour = unJour;
		mois = unMois;
		annee = uneAnnee;
	}

	public int getJour(){
		return jour;
	}
	public int getMois(){
		return mois;
	}
	public int getAnnee(){
		return annee;
	}

	public int compareTo(Object o) throws ClassCastException{
		if (!(o instanceof Date))
			throw new ClassCastException();
		int uneAnnee = ((Date) o).getAnnee();
		int unMois = ((Date) o).getMois();
		int unJour = ((Date) o).getJour();
		if ((this.getAnnee() - uneAnnee) == 0){
			if ((this.getMois() - unMois) == 0)
				return this.getJour() - unJour;
			return this.getMois() - unMois;
		}
		return this.getAnnee() - uneAnnee;
	}

	public boolean equals(Object o) throws ClassCastException{
		if (!(o instanceof Date))
			throw new ClassCastException();
		int uneAnnee = ((Date) o).getAnnee();
		int unMois = ((Date) o).getMois();
		int unJour = ((Date) o).getJour();
		if (uneAnnee == (annee))
			if (unMois  == (mois))
				if (unJour == (jour))
					return true;
		return false;
	}
	
	
	public String toString(){
		return "Jour : "+jour+" Mois : "+mois+" Annee : "+annee+".";
	}
	
}