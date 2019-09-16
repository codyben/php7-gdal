<?php

/**
 * Get a count of registered drivers (GDAL)
**/
echo gdal_registered_drivers().PHP_EOL;

/**
 * It should return a 0, thats OK. 
 * I don't currently register all drivers on PHP init for performance reasons.
 * The function below will register all drivers available to GDAL
**/

/** 
 * Now we ask GDAL to register all the available drivers.
**/

gdal_register_all_drivers();

/**
 * Depending on the number of drivers you have available, your count should now increase.
 * For reference, I have around ~200.
**/

echo gdal_registered_drivers().PHP_EOL;

/**
 * Now, for the *fun*.
 * Using the example geotiff in this directory, return a JSON representation of it, then call json_decode() to get a native PHP array.
 * In the future, I plan on returning a native php array directly from the function.
**/

$json = gdal_info("../resources/b.tif"); //if everything goes well, we return a native string		
if($json === false) {		//else, return a bool(false)
	echo "Failed to find file. Which isn't good. I must've messed up.".PHP_EOL;
} else {
	$gdal_info_arr = json_decode($json);

	var_dump($gdal_info_arr);
}