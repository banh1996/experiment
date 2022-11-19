import java.io.BufferedWriter;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Scanner;
 
public class HttpClientGet {
 
    public static void main(String[] args) {
         
        ByteArrayOutputStream responseBodyBaos = null;
        Scanner httpResponseBodyScanner = null;
        try {
            // Define server endpoint
            URL robotsUrl = new URL("http://localhost:9876");
            HttpURLConnection urlConnection = (HttpURLConnection) robotsUrl.openConnection(); 
  
            httpResponseBodyScanner = new Scanner(urlConnection.getInputStream());
  
            // Use a ByteArrayOutputStream to store the contents of the HTTP response body
            responseBodyBaos = new ByteArrayOutputStream();
            while(httpResponseBodyScanner.hasNextLine()) {
                responseBodyBaos.write(httpResponseBodyScanner.nextLine().getBytes());
            }
            responseBodyBaos.close();
            httpResponseBodyScanner.close();
  
            // Verify contents of robots.txt
            String robotsContent = responseBodyBaos.toString();
            if (robotsContent.trim().equals("Sitemap: http://www.techcoil.com/sitemap-index.xml")) {
                System.out.println("Able to retrieve robots.txt from server. Server is running fine.");
            }
            else {
                System.out.println("Not able to retrive robots.txt from server.");
            }
  
        } catch(IOException ioException) {
            System.out.println("IOException occurred while contacting server.");
        } finally {
            if (responseBodyBaos != null) {
                try {
                responseBodyBaos.close();
                } catch (IOException ioe) {
                    System.out.println("Error while closing response body stream");
                }
            }
            if (httpResponseBodyScanner != null) {
                httpResponseBodyScanner.close();
            }
        }
}}