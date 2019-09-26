<?php

/* GDAL Function Speed Comparison */

$ts_n = microtime(true); 

gdal_register_all_drivers();

for($i = 0; $i < 1000; $i++)
	json_decode(gdal_info("../resources/b.tif"));

$te_n = microtime(true); 

$et_n = ($te_n -$ts_n);

echo PHP_EOL."STARTING NEW".PHP_EOL;

$ty_n = microtime(true); 

for($i = 0; $i < 1000; $i++)
	shell_exec("gdalinfo ../resources/b.tif");

$tr_n = microtime(true); 

$ey_n = ($tr_n -$ty_n);

echo "GDAL Extension Time: ".$et_n.PHP_EOL;
echo "GDAL Shell Exec Time: ".$ey_n.PHP_EOL;