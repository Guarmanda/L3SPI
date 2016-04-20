import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;


public class JeuDeLaVieUI extends JFrame implements Observateur,ActionListener,ChangeListener{
	// Jeu courant
	private JeuDeLaVie jeu;
	// Bouton d'action
	private JButton btAction;
	// Bouton de pas
	private JButton btPas;
	// Bouton de règle
	private JButton btRegle;
	// Slider
	private JSlider slider;
	
	/**
	 * Constructeur de la classe JeuDeLaVieUI.
	 * @param jeu Le jeu courant.
	 */
	public JeuDeLaVieUI(JeuDeLaVie jeu){
		this.jeu = jeu;
		
		setSize(600,680);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		BorderLayout bord = new BorderLayout();
		getContentPane().setLayout(bord);
		getContentPane().add(this.pannel(), BorderLayout.SOUTH);
		
		setVisible(true);
	}
	
	/**
	 * Méthode créant un panneau de bouton.
	 * @return Le panneau de bouton.
	 */
	private JPanel pannel(){
		GridLayout grid1 = new GridLayout(0,1);
		GridLayout grid2 = new GridLayout(1,3);
		JPanel box1 = new JPanel(grid1);
		JPanel box2 = new JPanel(grid2);
		grid1.setVgap(10);
		grid2.setHgap(10);
		
		btAction = new JButton("Stop");
		btAction.addActionListener(this);
		btPas = new JButton("Génération suivante");
		btPas.setEnabled(false);
		btPas.addActionListener(this);
		btRegle = new JButton("Changer les règles");
		btRegle.addActionListener(this);
		
		slider = new JSlider(JSlider.HORIZONTAL, 0, 20, 10);
		slider.addChangeListener(this);
		
		slider.setMajorTickSpacing(10);
		slider.setMinorTickSpacing(10);
		slider.setPaintTicks(true);
		slider.setPaintLabels(false);
		
		box2.add(btAction);
		box2.add(btPas);
		box2.add(btRegle);
		
		box1.add(box2);
		box1.add(slider);
		
		return box1;
	}
	
	public void paint(Graphics g){
		super.paint(g);
		for(int x=0; x<jeu.getXMax(); x++)
			for(int y=0; y<jeu.getYMax(); y++)
				if(jeu.getGrilleXY(x, y).estVivante())
					g.fillOval(x*3, y*3, 3, 3);
	}
	
	@Override
	public void actualise() {
		repaint();
	}

	@Override
	public void stateChanged(ChangeEvent e) {
        JSlider source = (JSlider)e.getSource();
        if (!source.getValueIsAdjusting()) {
            int time = (int)source.getValue();
            if (time == 0) {
            	jeu.changeFlag(false);
            } else {
            	if(btAction.getText().equals("Stop"))
            		jeu.changeFlag(true);
            	jeu.setVitesse(time*100);
            }
        }
    }
	
	@Override
	public void actionPerformed(ActionEvent e){
		if(e.getActionCommand().equals("Executer")){
			jeu.changeFlag(true);
			btPas.setEnabled(false);
			btAction.setText("Stop");
		}
		else if(e.getActionCommand().equals("Stop")){
			jeu.changeFlag(false);
			btPas.setEnabled(true);
			btAction.setText("Executer");
		}
		else if(e.getActionCommand().equals("Génération suivante")){
			jeu.calculerGenerationSuivante();
		}
		else if(e.getActionCommand().equals("Changer les règles")){
			jeu.changeVisiteur();
		}
	}
}
