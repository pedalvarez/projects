<?php 
header('Access-Control-Allow-Origin: *');
header("Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept");
   
function getUserByCartId($id){
    $client = new SoapClient("http://127.0.0.1:9985/webshop?wsdl");
    $params = array ($id);
    $user = $client->__soapCall("getUserForShoppingCart",$params);        
    echo json_encode($user);
}

$id = $_POST['id'];
if (isset($_POST['getUserByCartId'])) {
    getUserByCartId($id);
}
?>