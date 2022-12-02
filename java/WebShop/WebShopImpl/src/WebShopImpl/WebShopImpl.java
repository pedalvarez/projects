package WebShopImpl;

import java.net.MalformedURLException;
import java.util.List;
import javax.jws.WebService;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.Unmarshaller;
import WebShopInterface.WebShopInterface;
import WebShopObjects.*;
import java.util.Map;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamReader;
import javax.xml.transform.stream.StreamSource;

/**
 *
 * @author peal
 */
@WebService(endpointInterface = "WebShopInterface.WebShopInterface")
public class WebShopImpl implements WebShopInterface {
 
    private String repository;    
    
    private WebShopObjects.Organization[] orgs;    
    private WebShopObjects.ShoppingCart[] shopingCarts;    
    private WebShopObjects.User[] users;    
    private WebShopObjects.Product[] products;
    
    Map<String, WebShopObjects.User> userMap;     
    
    private static volatile WebShopImpl INSTANCE;
    public static WebShopImpl getInstance() throws MalformedURLException, Exception {
        if(INSTANCE==null) {
            //synchronized(WebShopImpl.class) {
                if(INSTANCE==null) {
                    INSTANCE = new WebShopImpl();
                }
            //}
        }
        return INSTANCE;
    }
   
    public WebShopImpl() throws Exception {

        this.repository = WebShopMain.prop.getProperty("FILE_REPOSITORY");

        JAXBContext jaxb = JAXBContext.newInstance(WebShopObjects.Data.class.getPackage().getName());
            Unmarshaller unmarshaller = jaxb.createUnmarshaller();
            XMLInputFactory xif = XMLInputFactory.newFactory();
            xif.setProperty(XMLInputFactory.SUPPORT_DTD, false);
            XMLStreamReader xsr = xif.createXMLStreamReader(new StreamSource("Organzations.xml"));            
            
            WebShopObjects.Data Data = (WebShopObjects.Data)unmarshaller.unmarshal( xsr);
            List<Organization> orgList  = Data.getDataOrganization();
            orgs = new WebShopObjects.Organization[orgList.size()];
            int c = 0;
            for(Object o :orgList){
                orgs[c] = (WebShopObjects.Organization)o;
                c++;
            }
            
            XMLStreamReader xsr2 = xif.createXMLStreamReader(new StreamSource("ShopingCarts.xml"));            
            WebShopObjects.Data Data2 = (WebShopObjects.Data)unmarshaller.unmarshal( xsr2);
            List<ShoppingCart> scList  = Data2.getDataShoppingCart();
            shopingCarts = new WebShopObjects.ShoppingCart[scList.size()];
            c = 0;
            for(Object o :scList){
                shopingCarts[c] = (WebShopObjects.ShoppingCart)o;
                c++;
            }
            
            XMLStreamReader xsr3 = xif.createXMLStreamReader(new StreamSource("User.xml"));        
            WebShopObjects.Data Data3 = (WebShopObjects.Data)unmarshaller.unmarshal( xsr3);
            List<User> userList  = Data3.getDataUser();
            users = new WebShopObjects.User[userList.size()];
            c = 0;
            for(Object o :userList){
                users[c] = (WebShopObjects.User)o;
                c++;
            }
            
            XMLStreamReader xsr4 = xif.createXMLStreamReader(new StreamSource("Products.xml"));
            WebShopObjects.Data Data4 = (WebShopObjects.Data)unmarshaller.unmarshal( xsr4);
            List<Product> productList  = Data4.getDataProduct();
            products = new WebShopObjects.Product[productList.size()];
            c = 0;
            for(Object o :productList){
                products[c] = (WebShopObjects.Product)o;
                c++;
            }   
    }
    
    /**
     * Get name
     * @return 
     */
    @Override
    public String getName() {
        return "PEAL::WEBSHOP";
    }

    /**
     * Get title
     * @return 
     */
    @Override
    public String getTitle() {
        return "PEAL::WEBSHOP";
    }

    /**
     * Get version
     * @return 
     */
    @Override
    public String getVersion() {
        return "0.1.0";
    }   

    @Override
    public String getOrganizationsAsHtml() throws Exception {
        throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public WebShopObjects.Organization[] getOrganizations() throws Exception {
        System.out.println("getOrganizations()");
        return orgs;
    }

    @Override
    public ShoppingCart[] getShoppingCarts() throws Exception {
        System.out.println("getShoppigCarts()");
        return shopingCarts;
    }

    @Override
    public User getUserById(String id) throws Exception {
       for(User u: users){
           if(u.getUserId().equals(id)){
               return u;
           }
       } 
       return new User();
    }

    @Override
    public Product getProductById(String id) throws Exception {
        for(Product p: products){
           if(p.getProductId().equals(id)){
               return p;
           }
       }
       return new Product();
    }

    @Override
    public User getUserForShoppingCart(String id) throws Exception {
        System.out.println("getUserForShoppingCart(" + id + ")");
        String userId= "";
        
        for(ShoppingCart sc: shopingCarts){
           if(sc.getId().equals(id)){
               userId = sc.getUserId();
               break;
           }
        }
        if( userId.length() > 0){
            for(User u: users){
               if(u.getUserId().equals(userId)){
                   return u;
               }
           }
        }
       return new User();
    }

    @Override
    public Product[] getProductsForShoppingCart(String id) throws Exception {
        List<ProductPost> postsList= null;
        
        for(ShoppingCart sc: shopingCarts){
           if(sc.getId().equals(id)){
               postsList= sc.getItem();
               break;
           }
        }
        
        if(postsList != null && postsList.size() > 0){
            Product[] productList = new WebShopObjects.Product[postsList.size()];
            int counter = 0;
            for(ProductPost pp: postsList){
               for(Product p: products){ 
                   if(p.getProductId().equals(pp.getProductId())){
                    productList[counter] = p;
                    break;
                   }
               }
               counter++;
            }
            return productList;
        }
        else{
            return new WebShopObjects.Product[1];
        }
    }
}
