#!/usr/bin/php

<?php

	#===================================================================
	$port 	= 8080;
	$host 	= '0.0.0.0';
	$wsdl 	= 'http://' . $host . ':' . $port . '?wsdl';
	#-------------------------------------------------------------------
	$soap = new SoapClient( $wsdl, array('cache_wsdl' => WSDL_CACHE_NONE) );
	$message = trim(fgets(STDIN));
	$soap->say_hello(["msg"=>$message]);
	#===================================================================
?>
