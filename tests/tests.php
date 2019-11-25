<?php

function expects(bool $a, String $e, String $s) { //we'll move to PHPUnit eventually
	if($a) {
		echo "Test passed: ".$s;
	} else {
		echo "Test failed: ".$e;
	}

	echo PHP_EOL;
}

/* checks if the extension has been successfully loaded into the PHP runtime */
expects(extension_loaded('php7-gdal'),"extension not loaded successfully", "extension loaded successfully.");

/* make sure the runtime has registered all of the available functions*/
expects(function_exists('gdal_registered_drivers'), "gdal_registered_drivers() is not available.", "gdal_registered_drivers() is available");
expects(function_exists('gdal_register_all_drivers'), "gdal_register_all_drivers() is not available", "gdal_register_all_drivers() is available.");

expects(function_exists("gdal_info"), "gdal_info() is not available", "gdal_info is available.");

expects(function_exists("gdal_translate"), "gdal_translate() is not available", "gdal_translate() is available.");

expects(gettype(gdal_registered_drivers()) === "integer", "Invalid type returned for gdal_registered_drivers()", "Valid type returned for gdal_registered_drivers()");

/* Register all drivers available to GDAL */
gdal_register_all_drivers(); 

/* make sure we get a valid return type from GDALInfo */
expects(gettype(gdal_info("../resources/b.tif")) === "string", "Invalid type returned for gdal_info()","Valid type returned for gdal_info()");

/* make sure we can translate a file without error */
expects(gdal_translate("../resources/b.tif", "../resources/example.png", "-of PNG"), "False returned on translate", "Translate successful.");

/* make sure that the file exists after conversion */
expects(file_exists("../resources/example.png"), "Converted file does not exist","Converted file exists");

/* make sure cropping goes as expected */
expects(gdal_translate('../resources/b.tif', '../resources/output_cropped.tif',"-srcwin 0 0 0 0"), "False returned on translate", "Translate successful.");

/* make sure we have a cropped file */

expects(file_exists("../resources/output_cropped.tif"), "Cropped file does not exist","Cropped file exists");