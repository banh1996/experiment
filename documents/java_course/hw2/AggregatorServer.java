import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

import javax.xml.parsers.DocumentBuilderFactory;  
import javax.xml.parsers.DocumentBuilder;   

import java.io.*;

import java.lang.Thread;


public class AggregatorServer {
	public final static int SOCKET_PORT = 4567; 
	static String xml_content = "";
	static boolean is_content_ready = false;

	public static void main(String args[] ) throws IOException {
		String ContentPORT = args[0];
		String ClientPORT = args[1];


		/* client processing */
		Thread clienthandler = new Thread(new Runnable() {
			@Override
            public void run() {
				ServerSocket server = null;
				try {
					server = new ServerSocket(Integer.parseInt(ClientPORT));
				}
				catch(IOException ee) {
					ee.printStackTrace();
				}
				System.out.println("client handler Thread: Listening for connection on port " + ClientPORT + " ....");
				while (true) {
					Socket socket = null;
					try {
						socket = server.accept();
						InputStreamReader isr = new InputStreamReader(socket.getInputStream());
						BufferedReader reader = new BufferedReader(isr);
						String line = "";
						DataOutputStream dout = new DataOutputStream(socket.getOutputStream());

						/* enable hearbeat */
						socket.setTcpNoDelay(true);
						socket.setKeepAlive(true);
						socket.setSoTimeout(12000); //12s

						//get GET request, return error code 400 if receive requests other than GET/PUT
						line = reader.readLine();
						if (line.substring(0, 3).equals("GET") == true)
						{
							//send http GET response + xml content
							String reponse = "HTTP/1.1 200 OK\r\n" + "Connection: Keep-Alive\r\n" + "Keep-Alive: timeout=5\r\n" + "Content-Length: " + String.valueOf(xml_content.length()) + "\r\n" + xml_content + "\r\n";
							dout.write(reponse.getBytes("UTF-8"));
						}
						else
						{
							//send error message
							String reponse = "HTTP/1.1 400 Bad Request\r\n\r\n";
							dout.write(reponse.getBytes("UTF-8"));
						}
					}
					catch (Exception e){
						try {
							socket.close();
						}
						catch(IOException ee) {
							ee.printStackTrace();
						}
						e.printStackTrace();
					}
				}
			}
        });

		/* content server processing */
		Thread contenthandler = new Thread(new Runnable() {
			@Override
            public void run() {
				ServerSocket server = null;
				boolean is_content = false;
				int contentservernum = 0;
				try {
					server = new ServerSocket(Integer.parseInt(ContentPORT));
				}
				catch(IOException ee) {
					ee.printStackTrace();
				}
				System.out.println("content handler thread: Listening for connection on port " + ContentPORT + " ....");
				while (true) {
					Socket socket = null;
					try {
						socket = server.accept();
						InputStreamReader isr = new InputStreamReader(socket.getInputStream());
						BufferedReader reader = new BufferedReader(isr);
						DataOutputStream dout = new DataOutputStream(socket.getOutputStream());  
						String responseLine = "";

						//read PUT request, get xml content
						responseLine = reader.readLine();
						//System.out.println(responseLine);
						if (responseLine.substring(0, 3).equals("PUT") == true)
						{
							while ((responseLine = reader.readLine()) != null) {
								//System.out.println(responseLine);
								if (is_content == true)
								{
									//System.out.println(responseLine);
									xml_content += responseLine + "\n";
								}
								if (responseLine.indexOf("Content-Length:") != -1)
								{
									is_content = true;
								}
								else if (responseLine.indexOf("</feed>") != -1)
								{
									break;
								}
							}
							//send http 201 created message
							String reponse = "HTTP/1.1 201 Created\r\nConnection: Keep-Alive\r\nContent-Type: text/xml; charset=utf-8; CS" + String.valueOf(++contentservernum) + "\r\nKeep-Alive: timeout=12\r\n";
							dout.write(reponse.getBytes("UTF-8"));

							//store xml content
							//System.out.println(xml_content);
							FileOutputStream outputStream = new FileOutputStream("CS"+String.valueOf(contentservernum));
							byte[] strToBytes = xml_content.getBytes();
							outputStream.write(strToBytes);
							outputStream.close();

							is_content_ready = true;
						}
						else {
							//while ((responseLine = reader.readLine()) != null) {}
							//send error message
							String reponse = "HTTP/1.1 400 Bad Request\r\n\r\n";
							dout.write(reponse.getBytes("UTF-8"));
						}
					}
					catch (Exception e){
						try {
							socket.close();
						}
						catch(IOException ee) {
							ee.printStackTrace();
						}
						e.printStackTrace();
					}
				}
            }
        });
					  
		try {
			clienthandler.start();
			contenthandler.start();
			clienthandler.join();
			contenthandler.join();
			System.out.println("\nPrinting over");
		} catch (Exception e) {
		}
    }
}
