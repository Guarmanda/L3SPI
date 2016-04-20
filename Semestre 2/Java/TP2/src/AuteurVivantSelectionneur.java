/**
* @author YANN GUENVER
* @version 0.1 : Date : Mon Feb 01 11:06:32 CET 2016
*
*/
public class AuteurVivantSelectionneur implements Selectionneur{

	public Date date = null;

	public AuteurVivantSelectionneur(Date uneDate){
		date = uneDate;
	}
	
	/** vérifie si l'auteur était encore vivant à une année donnée
	 * @param d le document concerné
	 * @return true si le document satisfait un critère, false sinon
	 */
	public boolean estSatisfaitPar(Document d){
		if ( d.getAuteur().getDeces() == null )
			return true;
		else if ( (d.getAuteur().getDeces().compareTo( date )) >= 0 )
			return true;
		return false;
	}
}