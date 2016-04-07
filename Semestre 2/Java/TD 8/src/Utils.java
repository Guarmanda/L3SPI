import java.util.List;
//import java.util.ArrayList;
import static java.util.Comparator.comparing;
import static java.util.stream.Collectors.toList;


public class Utils {
	
	public static List<Personne> personnesNom(String nom, List<Personne> lstPers){
		List<Personne> personnes = lstPers.stream().filter(p -> p.getNom().equals(nom)).collect(toList());
		return personnes;
	}
	
	public static List<Personne> personnesMajeurs(List<Personne> lstPers){
		List<Personne> personnes = lstPers.stream().filter(p -> p.getAge() >= 18).collect(toList());
		return personnes;
	}
	
	public static boolean existeProfession(String profession, List<Personne> lstPers){
		return lstPers.stream().anyMatch(p -> p.getProfession().equals(profession));
	}
	
	public static List<String> professions(List<Personne> lstPers){
		List<String> professions = lstPers.stream().map(Personne::getProfession).sorted().collect(toList());
		return professions;
	}
	
	
}
