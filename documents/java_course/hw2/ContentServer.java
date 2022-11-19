import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;
import java.util.logging.StreamHandler;

import javax.naming.Context;

import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.Scanner;

import org.xml.sax.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.sax.*;


public class ContentServer {
    static String PUT_message = "PUT /atom.xml HTTP/1.1\r\nUser-Agent: ATOMClient/1/0\r\nContent-Type: application/xml/";
    static int lamportclock = 0;

    static String parse_xml(String input_file) {
        String result = "<?xml version=\'1.0\' encoding=\'iso-8859-1\' ?>\r\n<feed xml:lang=\"en-US\" xmlns=\"http://www.w3.org/2005/Atom\">\r\n";
        // /Scanner scanner = new Scanner(new File("context.txt"));
        //Parse content file follow xml format
        int countentry = 0;
        String spaces = "    ";
        BufferedReader filereader;
        try{
            filereader = new BufferedReader(new FileReader(input_file));
            String readline = filereader.readLine();
            while (readline != null) {
                if(readline.substring(0, 3).equals("id:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<id>" + readline.substring(3, readline.length()) + "</id>\r\n";
                }
                else if(readline.substring(0, 5).equals("link:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<link> href=\"" + readline.substring(5, readline.length()) + "\"</link>\r\n";
                }
                else if(readline.substring(0, 5).equals("entry") == true)
                {
                    countentry++;
                    countentry &= 0x01;
                    if(countentry == 1)
                    {
                        result += (spaces + "<entry>\r\n");
                    }
                    else
                    {
                        result += (spaces + "</entry>\r\n");
                    }
                }
                else if(readline.substring(0, 6).equals("title:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<title>" + readline.substring(6, readline.length()) + "</title>\r\n";
                }
                else if(readline.substring(0, 8).equals("updated:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<updated>" + readline.substring(7, readline.length()) + "</updated>\r\n";
                }
                else if(readline.substring(0, 7).equals("author:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<author>\r\n";
                    result += (countentry==0?spaces:(spaces+"  ")) + "  " + "<name>"+ readline.substring(7, readline.length()) +"</name>\r\n";
                    result += (countentry==0?spaces:(spaces+"  ")) + "</author>\r\n";
                }
                else if(readline.substring(0, 8).equals("summary:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<summary>" + readline.substring(7, readline.length()) + "</summary>\r\n";
                }
                else if(readline.substring(0, 9).equals("subtitle:") == true)
                {
                    result += (countentry==0?spaces:(spaces+"  ")) + "<subtitle>" + readline.substring(9, readline.length()) + "</subtitle>\r\n";
                }
                readline = filereader.readLine();
            }
            filereader.close();
        } catch(IOException e){
            e.printStackTrace();
        }

        result += "</feed>\r\n";

        return result;
    }
    

    public static void main(String args[] ) throws IOException {
        //parse IP and port from URL
        String[] stringarray = args[0].split(":");
        String IP = stringarray[1].substring(2);
        String PORT = stringarray[2];
        String ContentPath = args[1];
        String PUTresult = "";
        String xml_content = "";
        xml_content = parse_xml(ContentPath);
        PUTresult = PUT_message + String.valueOf(++lamportclock) + "\r\nContent-Length: " + String.valueOf(xml_content.length()) + "\r\n\r\n" + xml_content;
        //System.out.println(parse_xml(ContentPath));
        try {
            BufferedReader in =  null;
            Socket s=new Socket(IP, Integer.parseInt(PORT));
            DataOutputStream dout=new DataOutputStream(s.getOutputStream());
            in = new BufferedReader(new InputStreamReader(s.getInputStream()));

            s.setTcpNoDelay(true);
            s.setKeepAlive(true);
            s.setSoTimeout(12000); //alive/heartbeat 12s

            //send PUT message
            System.out.println(PUTresult);
            dout.write(PUTresult.getBytes("UTF-8"));
            dout.flush();

            //get response here, should be http 201 created
            String responseLine;
            System.out.println("Aggregator-server response:");
            while ((responseLine = in.readLine()) != null) {
                System.out.println(responseLine);
                if (responseLine.substring(0, 20).equals("HTTP/1.1 201 Created") == true) {
                    //System.out.println("Status is OK");
                    //break;
                }
                //System.out.println("Status is not OK");
                //break;
            }

            dout.close();
            s.close();
        } catch(Exception e){System.out.println(e);}
    }
}