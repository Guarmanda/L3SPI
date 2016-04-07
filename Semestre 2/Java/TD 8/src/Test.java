

public class Test {
	public static void main(String[] args){
		Pays france = new Pays("France");
		Ville leMans = new Ville("LeMans");
		Ville ecommoy = new Ville("Ecommoy");
		france.ajouteVille(leMans);
		france.ajouteVille(ecommoy);
		
		Personne yann = new Personne("Yann", "Glandeur", 22, leMans);
		Personne wajdi = new Personne("Wajdi", "Chieur", 23, leMans);
		Personne Charlotte = new Personne("Charlotte", "L3 Droit", 20, ecommoy);
		Personne Corentin = new Personne("Corentin", "L1 SPI", 17, ecommoy);
		
		System.out.println(Utils.personnesNom("Wajdi", leMans.getHabitants()));
		System.out.println(Utils.personnesMajeurs(ecommoy.getHabitants()));
		System.out.println(Utils.existeProfession("Glandeur", leMans.getHabitants()));
		System.out.println(Utils.professions(ecommoy.getHabitants()));
		System.out.println(france.plusGrosseVille().getNom());
	}
}
