package WebShopImpl;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;
import java.util.concurrent.Executors;
import javax.xml.ws.Endpoint;

/**
 *
 * @author peal
 */
public class WebShopMain {
    
    private static final String CONFIG_PATH = "WebShop.properties";  
    Endpoint webservice = null;
    
    public static final Properties prop = new Properties();
            
    public class RunWhenShuttingDown extends Thread
     {
        @Override
        public void run() {            
                        
            if(webservice!=null){                
               try{
                    webservice.stop();
               } catch (NullPointerException expectedWellKnownBug) {
                   // do nothing was because of 0.0.0.0
               }
            }
        }
    }

    public void runProgram(String[] args) throws InterruptedException
    {
         try {
            prop.load(new FileReader(CONFIG_PATH));
            Runtime.getRuntime().addShutdownHook(new RunWhenShuttingDown());
            String Wsdl = prop.getProperty("WSDL_ADRESS");
            System.out.println("Starting WebShop service at: "+Wsdl);

            webservice = Endpoint.create(WebShopImpl.getInstance());
            webservice.setExecutor(Executors.newFixedThreadPool(6));
            webservice.publish(Wsdl);
        } catch (IOException ex) {
            System.out.println("Couldn't load config: " + CONFIG_PATH +". " + ex.getMessage());
        } catch (Exception ex) {
            System.out.println("Fatal error: " + ex.getMessage());
        }
    }
    
    public static void main(String[] args) throws InterruptedException{
         new WebShopMain().runProgram(args);
    }
}
