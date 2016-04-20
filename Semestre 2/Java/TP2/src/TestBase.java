/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 11:56:48 CET 2016
*
*/
import java.util.*;

public class TestBase {
	public static void main(String [] args) throws InvalidDateException{
		Date date1 = new Date(25,5,1957);
		Date date2 = new Date(24,3,2043);
		Date date3 = new Date(25,3,2043);
		Auteur auteur = new Auteur("John",date1,date2);
		Document doc1 = new Document(auteur,"Coucou");
		Document doc2 = new Document(auteur,"Coucou le monde");
		BaseDocuments base = new BaseDocuments();
		
		doc2.modifierEtat();
		
		base.ajoute(doc1);
		base.ajoute(doc2);
		
		NomEmprunteSelectionneur s = new NomEmprunteSelectionneur();
		AuteurVivantSelectionneur s2 = new AuteurVivantSelectionneur(date2);
		MotDansTitreSelectionneur s3 = new MotDansTitreSelectionneur("le");
		
		Iterator i = base.selectionne(s);
		while(i.hasNext()){
			System.out.println(i.next());
		}

		i = base.selectionne(s2);
		while(i.hasNext()){
			System.out.println(i.next());
		}

		i = base.selectionne(s3);
		while(i.hasNext()){
			System.out.println(i.next());
		}
	}
}