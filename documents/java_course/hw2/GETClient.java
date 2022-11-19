import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

import javax.xml.parsers.*;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class GETClient {
    public static void main(String args[] ) throws IOException {
        //parse IP and port from URL
        String[] stringarray = args[0].split(":");
        String IP = stringarray[1].substring(2);
        String PORT = stringarray[2];
        String response = "";
        try {
            BufferedReader in =  null;
            Socket s=new Socket(IP, Integer.parseInt(PORT));
            DataOutputStream dout=new DataOutputStream(s.getOutputStream());  
            in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            dout.write("GET /echo/put/xml HTTP/1.1\r\nConnection: Keep-Alive\r\n".getBytes("UTF-8"));
            dout.flush();

            String responseLine;
            while ((responseLine = in.readLine()) != null) {
                //System.out.println("Server: " + responseLine);
                if (responseLine.indexOf("HTTP/1.1 200 OK") != -1) {
                    break;
                }
            }
            in.readLine();
            in.readLine();
            in.readLine();
            in.readLine();

            //get xml file
            while ((responseLine = in.readLine()) != null) {
                response += responseLine + "\n";
                if (responseLine.indexOf("</feed>") != -1)
                {
                    break;
                }
            }

            // display xml file
            try {
                final InputStream stream = new ByteArrayInputStream(response.getBytes());
                DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
                Document doc = dBuilder.parse(stream);
                doc.getDocumentElement().normalize();
                NodeList nList = doc.getElementsByTagName("feed");
                for (int temp = 0; temp < nList.getLength(); temp++) {
                    Node nNode = nList.item(temp);
                    if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                        Element eElement = (Element) nNode;
                        System.out.println("title:" 
                            + eElement
                            .getElementsByTagName("title")
                            .item(0)
                            .getTextContent());
                        System.out.println("subtitle:" 
                            + eElement
                            .getElementsByTagName("subtitle")
                            .item(0)
                            .getTextContent());
                        System.out.println("link:"
                            + eElement
                            .getElementsByTagName("link")
                            .item(0)
                            .getTextContent().substring(5));
                        System.out.println("updated:"
                            + eElement
                            .getElementsByTagName("updated")
                            .item(0)
                            .getTextContent());
                        System.out.println("author:"
                            + eElement
                            .getElementsByTagName("name")
                            .item(0)
                            .getTextContent());
                        System.out.println("id:"
                            + eElement
                            .getElementsByTagName("id")
                            .item(0)
                            .getTextContent());
                    }
                }

                //parse entry
                try {
                    NodeList entrylist = doc.getElementsByTagName("entry");
                    for (int temp = 0; temp < entrylist.getLength(); temp++) {
                        Node nNode = entrylist.item(temp);
                        if (nNode.getNodeType() == Node.ELEMENT_NODE) {
                            System.out.println("entry");
                            Element eElement = (Element) nNode;
                            System.out.println("title:" 
                                + eElement
                                .getElementsByTagName("title")
                                .item(0)
                                .getTextContent());
                            System.out.println("link:" 
                                + eElement
                                .getElementsByTagName("link")
                                .item(0)
                                .getTextContent().substring(5));
                            System.out.println("id : " 
                                + eElement
                                .getElementsByTagName("id")
                                .item(0)
                                .getTextContent());
                            System.out.println("updated:" 
                                + eElement
                                .getElementsByTagName("updated")
                                .item(0)
                                .getTextContent());
                            System.out.println("summary:" 
                                + eElement
                                .getElementsByTagName("summary")
                                .item(0)
                                .getTextContent());
                            System.out.println("entry");
                        }
                    }
                } catch (Exception e) {
                e.printStackTrace();
                }

             } catch (Exception e) {
                e.printStackTrace();
             }

            dout.close();
            s.close();
        } catch(Exception e){System.out.println(e);}  
    }
}


