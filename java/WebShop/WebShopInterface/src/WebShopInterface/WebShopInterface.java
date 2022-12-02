package WebShopInterface;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;
import WebShopObjects.*;
/**
 * @author peal
 */

//Service Endpoint Interface
@WebService
@SOAPBinding(style = Style.RPC)
public interface WebShopInterface {
    
    @WebMethod String getVersion();
    
    @WebMethod String getName();
    
    @WebMethod String getTitle();     
    
    @WebMethod public String getOrganizationsAsHtml() throws Exception;
    
    @WebMethod public Organization[] getOrganizations() throws Exception;
    
    @WebMethod public ShoppingCart[] getShoppingCarts() throws Exception;
    
    @WebMethod public User getUserForShoppingCart(String id) throws Exception;
    
    @WebMethod public Product[] getProductsForShoppingCart(String id) throws Exception;
    
    @WebMethod public User getUserById(String id) throws Exception;
    
    @WebMethod public Product getProductById(String id) throws Exception;
}
