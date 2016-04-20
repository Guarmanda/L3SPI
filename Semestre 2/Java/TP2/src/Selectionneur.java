/**
* @author YANN GUENVER
* @version 0.1 : Date : Mon Feb 01 09:29:57 CET 2016
*
*/
public interface Selectionneur {

	/** vérifie si le document satisfait un critère
	 * @param d le document concerné
	 * @return true si le document satisfait un critère, false sinon
	 */
	public boolean estSatisfaitPar(Document d);
}
