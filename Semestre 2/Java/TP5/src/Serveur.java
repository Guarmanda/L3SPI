
import java.net.*;
import java.io.*;

public class Serveur extends Thread{
	private Socket clientSocket;
	
	public Serveur(Socket c){
		clientSocket=c;
	}	
		
	public static void main(String[] args){
		InetAddress ip;
		ServerSocket serveur;
		
		//BufferedReader in;
		PrintWriter out;
		
		try{
			//creation de l'ip
			ip=InetAddress.getByName("127.0.0.1");
			
			//creation du serveur sur le premier port dispo, limité à 10 connexion simultané, sur l'ip ip
			serveur=new ServerSocket(0,10,ip); 
			System.out.println("le serveur est à l'écoute du port : "+serveur.getLocalPort());
			
			
			while(true){
				//attente d'un connexion
				Socket sockServ=serveur.accept();
				System.err.println("Connexion from : "+sockServ.getInetAddress());
				Serveur thread = new Serveur(sockServ);
				thread.start();
				thread.run();
				
			}			
		}
		catch(UnknownHostException e){
			System.out.println("adresse inconnue");
		} 
		catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void doService(Socket c){
		//communication à gerer 
		try {
			DataInputStream in=new DataInputStream(new BufferedInputStream(c.getInputStream()));
			PrintStream out=new PrintStream(c.getOutputStream());
			while(true){
				String ligne=in.readUTF();
				System.out.println(ligne);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} 
	}
	
	public void run(){
		doService(clientSocket);
		
	}
}