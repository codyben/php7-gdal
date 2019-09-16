<?php

function expects(bool $a, String $e, String $s) { //we'll move to PHPUnit eventually
	if($a) {
		echo "Test passed: ".$s;
	} else {
		echo "Test failed: ".$e;
	}

	echo PHP_EOL;
}

//check if ou extension has been loaded
expects(extension_loaded('php7-gdal'),"extension not loaded successfully", "extension loaded successfully.");

//check if implemented functions exist
expects(function_exists('gdal_registered_drivers'), "gdal_registered_drivers() is not available.", "gdal_registered_drivers() is available");
expects(function_exists('gdal_register_all_drivers'), "gdal_register_all_drivers() is not available", "gdal_register_all_drivers() is available.");
expects(function_exists("gdal_info"), "gdal_info() is not available", "gdal_info is available.");

expects(gettype(gdal_registered_drivers()) === "integer", "Invalid type returned for gdal_registered_drivers()", "Valid type returned for gdal_registered_drivers()");

gdal_register_all_drivers(); //load drivers to check next test

expects(gettype(gdal_info("../resources/b.tif")) === "string", "Invalid type returned for gdal_info()","Valid type returned for gdal_info()");