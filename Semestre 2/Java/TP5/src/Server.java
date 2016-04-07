import java.net.*;
import java.io.*;

public class Server{
	private Socket          socket   = null;
    private ServerSocket    server   = null;
    private DataInputStream streamIn =  null;

    public Server(int port){
    	try{
    		System.out.println("Binding to port " + port + ", please wait  ...");
            server = new ServerSocket(port);
            System.out.println("le serveur est à l'écoute du port : "+server.getLocalPort());
            System.out.println("Server started: " + server);
            System.out.println("Waiting for a client ..."); 
            socket = server.accept();
            System.out.println("Client accepted: " + socket);
            open();
            boolean done = false;
            while (!done){
            	try{
            		String line = streamIn.readUTF();
        		    System.out.println(line);
                    done = line.equals("bye");
                }
                catch(IOException ioe){
            	    done = true;
                }
            }
            close();
        }
    	catch(IOException ioe){
    	   ioe.printStackTrace();
        }
    }
    public void open() throws IOException {
	    streamIn = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
    }
    public void close() throws IOException{
	    if (socket != null)    socket.close();
        if (streamIn != null)  streamIn.close();
    }
    public static void main(String args[]){  
	    Server server = new Server(0);
    }
}