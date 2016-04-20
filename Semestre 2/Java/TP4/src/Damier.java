
public class Damier {
	public Case plateau[][];
	
	public Damier(int taille){
		plateau = new Case[taille][taille];
	}
	
	public Case donneTaCase(int i, int j){
		return plateau[i][j];
	}
	
	public void modifieTaCase(int i, int j, Case uneCase){
		plateau[i][j] = uneCase;
	}
}