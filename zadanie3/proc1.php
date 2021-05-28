  
#!/usr/bin/php

<?php

	$message ="";
	#===================================================================
	ini_set("soap.wsdl_cache_enabled", 0);
	$port 	= 8080;
	$host 	= '127.0.0.1';
	$wsdl 	= 'http://' . $host . ':' . $port . '?wsdl';
	#-------------------------------------------------------------------
	$soap = new SoapClient( $wsdl, array('cache_wsdl' => WSDL_CACHE_NONE) );
	$message .= rtrim(fgets(STDIN), "\n");
	$soap->say_hello(["msg"=>trim($message)]);
	#===================================================================
?>
