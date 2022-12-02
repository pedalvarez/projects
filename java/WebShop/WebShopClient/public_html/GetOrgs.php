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

function getOrganizations(){
    $client = new SoapClient("http://127.0.0.1:9985/webshop?wsdl");
    $params = array ();
    $orgs = $client->__soapCall("getOrganizations",$params);	

    $json_array = array();
    $obj = array(
    "name" => "",
    "ParentOrgName" => "");

    $array_contents = ArrayTools::parseObjectArrayToPhpArray($orgs);

    if (isset($array_contents['item'])) {
        for ($i = 0; $i < count($array_contents['item']); $i++) {
            if (isset($array_contents['item'][$i]['name']))
                $obj['name'] = $array_contents['item'][$i]['name'];
            if (isset($array_contents['item'][$i]['ParentOrgName']))
                $obj['ParentOrgName'] = $array_contents['item'][$i]['ParentOrgName'];
            
            array_push($json_array, $obj);
        }
    }
    echo json_encode($json_array);
}	
if (isset($_POST['getOrganizations'])) {
    getOrganizations();
}
?>
