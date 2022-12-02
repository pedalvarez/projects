/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package WebShopJavaClient;

//import TestWSInterface.HelloWorld; 
import java.net.MalformedURLException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.xml.namespace.QName;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.ws.Service;
import WebShopInterface.WebShopInterface;
import WebShopObjects.*;

/**
 *
 * @author peal
 */
public class WebShopJavaClient{
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws TransformerConfigurationException, TransformerException {
        try {
                URL url = new URL("http://127.0.0.1:9985/webshop");
                QName qname = new QName("http://WebShopImpl/", "WebShopImplService");
                Service service = Service.create(url, qname);
                System.out.println("---WebShop--");
                WebShopInterface wsi = service.getPort(WebShopInterface.class);
            try {
                Organization[] orgs =  wsi.getOrganizations();
            } catch (Exception ex) {
                Logger.getLogger(TestWSRpcStyleClient.class.getName()).log(Level.SEVERE, null, ex);
            }
            System.out.println("---end--");
        } catch (MalformedURLException ex) {
            Logger.getLogger(TestWSRpcStyleClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
