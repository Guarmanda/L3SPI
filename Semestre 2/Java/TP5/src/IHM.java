import java.awt.*;
import java.awt.event.ActionEvent;
import javax.swing.*;


public class IHM extends JFrame {
	
	private JButton btConnection;
	private JButton btEnvoyer;
	private JTextField txNom;
	private JTextField txIP;
	private JTextField txPort;
	private JTextArea txConnectes;
	private JTextArea txDiscussion;
	private JTextArea txMessage;
	
	
	public IHM(){

		setSize(500,600);
		setLocationRelativeTo(null);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		
		BorderLayout bord = new BorderLayout();
		bord.setVgap(20);
		bord.setHgap(20);
		
		getContentPane().setLayout(bord);
		getContentPane().add(pannelNord(), BorderLayout.NORTH);
		getContentPane().add(pannelOuest(), BorderLayout.WEST);
		getContentPane().add(pannelCentre(), BorderLayout.CENTER);
		
		setVisible(true);
	}
	

	
	private JPanel pannelNord(){
		GridLayout grid = new GridLayout(0,4);
		JPanel box = new JPanel(grid);
		
		grid.setVgap(10);
		
		JLabel lbNom = new JLabel("Nom");
		JLabel lbVide = new JLabel("");
		JLabel lbIP = new JLabel("IP");
		JLabel lbPort = new JLabel("Port");
		lbNom.setHorizontalAlignment(0);
		lbIP.setHorizontalAlignment(0);
		lbPort.setHorizontalAlignment(0);
		
		this.txNom = new JTextField();
		this.txIP = new JTextField();
		this.txPort = new JTextField();
		this.btConnection = new JButton("Connection");
		
		box.add(lbNom);
		box.add(txNom);
		box.add(lbVide);
		box.add(btConnection);
		box.add(lbIP);
		box.add(txIP);
		box.add(lbPort);
		box.add(txPort);
		
		
		return box;
	}
	private JPanel pannelOuest(){
		JPanel box = new JPanel(new BorderLayout());
		
		JLabel lbConnectes = new JLabel("Connectés");
		lbConnectes.setHorizontalAlignment(0);
		
		JTextArea txConnectes = new JTextArea();
		txConnectes.setColumns(15);
		
		box.add(lbConnectes, BorderLayout.NORTH);
		box.add(txConnectes, BorderLayout.CENTER);
		
		return box;
	}
	private JPanel pannelCentre(){
		BorderLayout nwBord = new BorderLayout();
		JPanel box = new JPanel(nwBord);
		nwBord.setVgap(10);
		
		
		JLabel lbDiscussion = new JLabel("Discussion");
		lbDiscussion.setHorizontalAlignment(0);
		JLabel lbMessage = new JLabel("Message");
		
		this.txDiscussion = new JTextArea();
		this.txMessage = new JTextArea();
		
		this.btEnvoyer = new JButton("Envoyer");
		
		JPanel bordNord = new JPanel(new BorderLayout());
		bordNord.add(lbDiscussion, BorderLayout.NORTH);
		bordNord.add(txDiscussion, BorderLayout.CENTER);
		
		JPanel bordCentre = new JPanel(new BorderLayout());
		bordCentre.add(lbMessage, BorderLayout.NORTH);
		bordCentre.add(txMessage, BorderLayout.CENTER);
		
		JPanel bordCentreBis = new JPanel(new BorderLayout());
		bordCentreBis.add(bordNord, BorderLayout.CENTER);
		bordCentreBis.add(bordCentre, BorderLayout.SOUTH);
		
		JPanel bordSud = new JPanel();
		bordSud.add(btEnvoyer);
		
		
		box.add(bordCentreBis, BorderLayout.CENTER);
		box.add(bordSud, BorderLayout.SOUTH);
		
		return box;
	}
	
	public static void main(String[] args){
		JFrame fenetre = new IHM();
		
	}
	
	public void actionPerformed(ActionEvent argO){
		if(argO.getActionCommand().equals("Connection")){
			btConnection.setText("Deconnection");
		}
		if(argO.getActionCommand().equals("Deconnection")){
			
		}
		if(argO.getActionCommand().equals("Envoyer")){
			
		}
	}
	
	
}
