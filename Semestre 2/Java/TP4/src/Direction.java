
public class Direction {
	private enum dir{NORD,EST,SUD,OUEST};
	public dir sens;
	
	public Direction(dir s){
		sens = s;
	}
	
	public void setDir(dir s){
		sens = s;
	}
	
	
	public Case voisineDansDir(CaseLibre uneCase){
		switch(sens){
			case NORD: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()-1];
			case EST: return uneCase.getDamier().plateau[uneCase.geti()+1][uneCase.getj()];
			case SUD: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()+1];
			default: return uneCase.getDamier().plateau[uneCase.geti()-1][uneCase.getj()];
		}
	}
	
	public Case CaseGauche(CaseLibre uneCase){
		switch(sens){
			case NORD: return uneCase.getDamier().plateau[uneCase.geti()+1][uneCase.getj()];
			case EST: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()+1];
			case SUD: return uneCase.getDamier().plateau[uneCase.geti()-1][uneCase.getj()];
			default: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()-1];
		}
	}
	
	public Case CaseDroit(CaseLibre uneCase){
		switch(sens){
			case NORD: return uneCase.getDamier().plateau[uneCase.geti()-1][uneCase.getj()];
			case EST: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()-1];
			case SUD: return uneCase.getDamier().plateau[uneCase.geti()+1][uneCase.getj()];
			default: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()+1];
		}
	}
	
	public Case CaseOpposee(CaseLibre uneCase){
		switch(sens){
			case NORD: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()+1];
			case EST: return uneCase.getDamier().plateau[uneCase.geti()-1][uneCase.getj()];
			case SUD: return uneCase.getDamier().plateau[uneCase.geti()][uneCase.getj()-1];
			default: return uneCase.getDamier().plateau[uneCase.geti()+1][uneCase.getj()];
		}
	}
	
}