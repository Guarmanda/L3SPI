import java.net.*;
import java.io.*;


public class Client {
	
	private Socket socket              = null;
	private DataInputStream  console   = null;
	private DataOutputStream streamOut = null;
	
	public Client(String serverName,int serverPort){
		try{
			socket = new Socket(serverName, serverPort);
			start();
		}
		catch(UnknownHostException uhe){
			uhe.printStackTrace();
		}
		catch(IOException ioe){
			ioe.printStackTrace();
		}
		String line = "";
	   while (!line.equals("bye")){
		   try{
			   line = console.readLine();
	           streamOut.writeUTF(line);
	           streamOut.flush();
	       }
	       catch(IOException ioe){
	    	   ioe.printStackTrace();
	       }
	    }
	}
	
	public void start() throws IOException{
		console   = new DataInputStream(System.in);
	    streamOut = new DataOutputStream(socket.getOutputStream());
	}
	public void stop(){
		try{
			if (console   != null)  console.close();
	        if (streamOut != null)  streamOut.close();
	        if (socket    != null)  socket.close();
	    }
	    catch(IOException ioe){
	    	ioe.printStackTrace();
	    }
	 }
	 public static void main(String args[]){
		 Client client = new Client("127.0.0.1",Integer.parseInt(args[0]));
	 }
}
