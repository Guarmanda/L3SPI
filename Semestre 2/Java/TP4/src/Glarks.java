
public class Glarks {
	private int energie;
	private CaseLibre caseCourante;
		
	
	
	public int getEnergie(){
		return energie;
	}
	public CaseLibre getCase(){
		return caseCourante;
	}
	public void setCase(CaseLibre uneCase){
		caseCourante = uneCase;
	}
	
	public void meurs(){
		energie = 0;
		caseCourante.supprimerGlarks(this);
	}
	
	public void vasY(){
		energie -= 5;
		if (energie == 0){
			this.meurs();
		}else{
			Case uneCase = trouveDestination();
			if (uneCase != caseCourante){
				setCase((CaseLibre)uneCase);
				caseCourante.menu(this);
			}
		}
		
	}
	
	public boolean estBorne(){
		return false;
	}
	
	public void devoreBlurf(){
		energie = 100;
		caseCourante.setBlurf(false);
	}
	
	public void devoreGlarks(Glarks unGlark){
		
	}
	
	
	public Case trouveDestination(){
		return caseCourante;
	}
	
}