<?php 
header('Access-Control-Allow-Origin: *');
header("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");

class ArrayTools {
    public static function parseObjectArrayToPhpArray($array){
        if(is_object($array)) {
            $array = get_object_vars($array);
        }
        if(is_array($array)){
            return array_map(__METHOD__, $array);
        }
        else {
            return $array;
        }
    }
}
 
function getProductsFromCartId($id){
    $client = new SoapClient("http://127.0.0.1:9985/webshop?wsdl",array('features'=> SOAP_SINGLE_ELEMENT_ARRAYS));
    $params = array ($id);
    $products = $client->__soapCall("getProductsForShoppingCart",$params);	

    $json_array = array();

    $obj = array(
         "name" => "",            
         "attributes" => "");

    $array_contents = ArrayTools::parseObjectArrayToPhpArray($products);
     if (isset($array_contents['item'])) {
        for ($i = 0; $i < count($array_contents['item']); $i++) {
            if (isset($array_contents['item'][$i]['name']))
             $obj['name'] = $array_contents['item'][$i]['name'];
            if (isset($array_contents['item'][$i]['Attribute'])){
                $obj['attributes'] = $array_contents['item'][$i]['Attribute'];
            }
            array_push($json_array, $obj);
        }
    }
    echo json_encode($json_array);
 }
   	
 $id = $_POST['id'];
 if (isset($_POST['getProductsFromCartId'])) {
    getProductsFromCartId($id);
 }
?>