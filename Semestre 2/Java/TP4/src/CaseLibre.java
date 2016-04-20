import java.util.List;
import java.util.LinkedList;

public class CaseLibre extends Case {
	private Damier damier;
	private boolean blurf;
	private List<Glarks> listeDesGlarks;
	
	public CaseLibre(Damier unDamier){
		damier = unDamier;
		blurf = false;
		listeDesGlarks = new LinkedList<Glarks>();
	}
	
	public Damier getDamier(){
		return damier;
	}
	
	public void setBlurf(boolean b){
		blurf = b;
	}
	
	public void ajouteGlark(Glarks g){
		listeDesGlarks.add(g);
	}
	
	public Glarks getGlarks(int i){
		return listeDesGlarks.get(i);
	}
	
	public void supprimerGlarks(Glarks g){
		listeDesGlarks.remove(g);
	}
	
	public void menu(Glarks unGlarks){
		if(blurf){
			unGlarks.devoreBlurf();
		}
		
		unGlarks.devoreGlarks();
	}
	
	
}