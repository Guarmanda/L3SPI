/**
* @author YANN GUENVER
* @version 0.1 : Date : Mon Feb 01 11:06:40 CET 2016
*
*/
public class MotDansTitreSelectionneur implements Selectionneur{

	public String mot;

	public MotDansTitreSelectionneur(String unMot){
		mot = unMot;
	}
	
	/** vérifie si le document satisfait un critère
	 * @param d le document concerné
	 * @return true si le document satisfait un critère, false sinon
	 */
	public boolean estSatisfaitPar(Document d){
		if ( (d.getTitre().indexOf(mot)) != -1 )
			return true;
		return false;
	}
	
}