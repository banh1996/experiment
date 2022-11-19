import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

import javax.xml.parsers.DocumentBuilderFactory;  
import javax.xml.parsers.DocumentBuilder;  
import org.w3c.dom.Document;  
import org.w3c.dom.NodeList;  
import org.w3c.dom.Node;  
import org.w3c.dom.Element;  
import java.io.File;  

import java.io.File;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import org.w3c.dom.Document;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.io.*;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;


public class SimpleHTTPServer {
	
	private static final String FILENAME = "response.xml";
	public final static int SOCKET_PORT = 9876; 
	
	
	public static void main(String args[] ) throws IOException {
		
		
	FileInputStream fis = null;
    BufferedInputStream bis = null;
    OutputStream os = null;
    ServerSocket servsock = null;
    Socket sock = null;
		
		File myFile = new File("response.xml");
		
		ServerSocket server = new ServerSocket(9876);
        System.out.println("Listening for connection on port 9876 ....");
        while (true) {
            try (Socket socket = server.accept()) {
				//String str = Files.readString(fileName);
				//System.out.println(str);
				/*
				Socket sock = server.accept();
				byte[] mybytearray = new byte[(int) myFile.length()];
				BufferedInputStream bis = new BufferedInputStream(new FileInputStream(myFile));
				bis.read(mybytearray, 0, mybytearray.length);
				OutputStream os = sock.getOutputStream();
				os.write(mybytearray, 0, mybytearray.length);
				os.flush();
				sock.close();*/
				//Path filePath = Path.of("C:\\money\\javaTest\\response.xml");
				//String content = Files.readString(filePath);
				InputStreamReader isr 
				=  new InputStreamReader(socket.getInputStream());
				BufferedReader reader = new BufferedReader(isr);
				String line = reader.readLine();      
				DataOutputStream dout=new DataOutputStream(socket.getOutputStream());  
				
				//read line by line
				/*
				try (FileReader fr = new FileReader(myFile);
				  BufferedReader br = new BufferedReader(fr);) {
				  String linetemp;
				  String linetest = "HTTP/1.1 200 OK\r\n\r\n";
				  while ((linetemp = br.readLine()) != null) {
					  linetest = "HTTP/1.1 200 OK\r\n\r\n" + linetemp;
					dout.write(linetest.getBytes("UTF-8"));
				  }
				} catch (IOException e) {
				  e.printStackTrace();
				}
				*/
				//Read to string
				Path fileName
				= Path.of("response.xml");
				String str = Files.readString(fileName);
				
				
				String hung = "HTTP/1.1 200 OK\r\n\r\n" + str;
				dout.write(hung.getBytes("UTF-8"));  
				//while (!line.isEmpty()) {
				//	System.out.println(line);
				//	line = reader.readLine();
				//}
							/*
				  while (true) {
					System.out.println("Waiting...");
					try {
					  sock = server.accept();
					  System.out.println("Accepted connection : " + sock);
					  // send file
					  File sendFile = new File (FILENAME);
					  byte [] mybytearray  = new byte [(int)sendFile.length()];
					  fis = new FileInputStream(sendFile);
					  bis = new BufferedInputStream(fis);
					  bis.read(mybytearray,0,mybytearray.length);
					  os = sock.getOutputStream();
					  System.out.println("Sending " + FILENAME + "(" + mybytearray.length + " bytes)");
					  os.write(mybytearray,0,mybytearray.length);
					  os.flush();
					  System.out.println("Done.");
					}
					finally {
					  if (bis != null) bis.close();
					  if (os != null) os.close();
					  if (sock!=null) sock.close();
					}
				  }
				  */
				
				
				/*
                Date today = new Date();
				String httpResponse = "HTTP/1.1 200 OK\r\n\r\n" + today;
                socket.getOutputStream()
                      .write(httpResponse.getBytes("UTF-8"));
					  */
					  
			}
            
        }
    }

}
