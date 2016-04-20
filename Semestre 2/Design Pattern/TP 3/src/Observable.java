
public interface Observable {
	/**
	 * Méthode attachant un observateur.
	 * @param o Observateur à attacher.
	 */
	public void attacheObservateur(Observateur o);
	/**
	 * Méthode détachant un observateur.
	 * @param o Observateur à détacher.
	 */
	public void detacheObservateur(Observateur o);
	/**
	 * Méthode actualisent l'observateur. 
	 */
	public void notifieObservateur();
}
