/**
* @author YANN GUENVER
* @version 0.1 : Date : Mon Feb 01 10:58:39 CET 2016
*
*/
public class NomEmprunteSelectionneur implements Selectionneur{

	/** vérifie si le document est emprunté
	 * @param d le document concerné
	 * @return true si le document est emprunté, false sinon
	 */
	public boolean estSatisfaitPar(Document d){
		if ( "disponible".equals(d.getEtat()))
			return true;
		return false;
	}
}