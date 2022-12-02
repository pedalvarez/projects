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

function getShoppingCarts(){
    $client = new SoapClient("http://127.0.0.1:9985/webshop?wsdl",array('features'=> SOAP_SINGLE_ELEMENT_ARRAYS));
    $params = array ();
    $carts = $client->__soapCall("getShoppingCarts",$params);	

    $json_array = array();

    $obj = array(
        "Id" => "",
        "userId" => "",
        "productPost" => array(
            "productId" => "",
            "quantity" => ""
         )
    );

    $array_contents = ArrayTools::parseObjectArrayToPhpArray($carts);

    if (isset($array_contents['item'])) {
        for ($i = 0; $i < count($array_contents['item']); $i++) {
            if (isset($array_contents['item'][$i]['Id']))
                $obj['Id'] = $array_contents['item'][$i]['Id'];
            if (isset($array_contents['item'][$i]['userId']))
                $obj['userId'] = $array_contents['item'][$i]['userId'];
            if (isset($array_contents['item'][$i]['item'])){      
                for ($o = 0; $o < count($array_contents['item'][$i]['item']); $o++) {
                    $obj['productPost'][$o]['productId'] = $array_contents['item'][$i]['item'][$o]['productId'];
                    $obj['productPost'][$o]['quantity'] = $array_contents['item'][$i]['item'][$o]['quantity'];
                }
            }
            array_push($json_array, $obj);
        }
    }
    echo json_encode($json_array);
}	

if (isset($_POST['getShoppingCarts'])) {
    getShoppingCarts();
}
?>