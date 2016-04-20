/**
* @author YANN GUENVER
* @version 0.1 : Date : Tue Jan 26 09:49:30 CET 2016
*
*/
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class Test {

	public static void main(String[] args) throws InvalidDateException{

		System.out.println("Teste de création de trois date :");
		
		Date uneDate1 = new Date(1,10,1335);
		System.out.println(uneDate1.toString());
		Date uneDate2 = new Date(5,6,1567);
		System.out.println(uneDate2.toString());

		//System.out.println("La derniere date doit renvoyer une erreur :");
		Date uneDate3 = new Date(20,5,1563);
		System.out.println(uneDate3.toString());


		List liste = new ArrayList();
		liste.add(uneDate1);
		liste.add(uneDate2);
		liste.add(uneDate3);

		Collections.sort(liste);
		System.out.println(liste);

		System.out.println("Teste de comparaison des deux premiere dates :");
		System.out.println(uneDate1.compareTo(uneDate2));
	}
}