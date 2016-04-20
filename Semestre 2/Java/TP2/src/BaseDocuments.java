/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 11:22:57 CET 2016
*
*/
import java.util.*;

public class BaseDocuments {
    // COMPLETER // attribut(s) et constructeur(s)
    private List liste;

	public BaseDocuments(){
		liste = new ArrayList();
	}

    /** ajoute un document dans la base de documents
    * @param d le document à ajouter
    */
        // COMPLETER méthode ajoute
    public void ajoute(Document d){
    	liste.add(d);
    }
	
    /** supprime un document de la base de documents (si il est plusieurs
    * fois présents, une seule des occurrences est supprimée). Il
    * importe peu que le document soit emprunté ou non au moment de sa
    * suppression.
    * @param d le document à supprimer
    * @return le document supprimé, null s’il n’existe pas
    */
        // COMPLETER méthode supprime
    public Document supprime(Document d){
    	if (liste.remove(d))
    		return d;
    	return null;
    }

    /** affiche tous les documents de la mediathèque (pour impression
    * du catalogue par exemple)
    */
       // COMPLETER méthode affiche
    public void affiche(){
    	System.out.println(liste);
    }

    /** indique si le document donné est disponible (non emprunté)
    * @param d le document concerné
    * @return true si le document donné est disponible (non emprunté)
    * @exception NoSuchElementException si le document n’existe
    * pas dans la mediathèque
    */
       // COMPLETER méthode estDisponible
    public boolean estDisponible(Document d) throws NoSuchElementException{
    	if ( !(liste.contains(d)) )
    		throw new NoSuchElementException();
    	int i = liste.indexOf(d);
    	if ( ((Document) liste.get(i)).getEtat().equals("disponible"))
    		return true;
    	return false;
    }

    /** permet d’emprunter un document
    * @param d le document concerné
    * @exception NoSuchElementException si le document n’existe
    * pas dans la mediathèque
    * @return true si le document donné était disponible et a pu être emprunté
    */
       // COMPLETER méthode emprunte
    public boolean emprunte(Document d){
    	if ( this.estDisponible(d) ){
			int i = liste.indexOf(d);
    		((Document) liste.get(i)).modifierEtat();
    		return true;
    	}else
    		return false;
    		
    }

    /** permet de rendre un document
    * @param d le document concerné
    */
       // COMPLETER méthode rend
    public void rend(Document d){
    	int i = liste.indexOf(d);
    	((Document) liste.get(i)).modifierEtat();
    }

	/** 
	 * @param s le selectionneur
	 */
	public Iterator selectionne(Selectionneur s){
		List l = new ArrayList();
		Iterator i = liste.iterator();

		while(i.hasNext()) {
			Document d = (Document) i.next();
			if (  s.estSatisfaitPar(d) )
				l.add(d);
		}
		return l.iterator();
	}
    
}