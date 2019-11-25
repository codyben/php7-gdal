<?php

/* GDAL Function Speed Comparison */
define("NUMBER_RUNS", 100);

$ts_n = microtime(true); 

gdal_register_all_drivers();

for($i = 0; $i < NUMBER_RUNS; $i++)
	gdal_translate("../resources/b.tif", "../resources/output.png","-of png"); //timing may be skewed if all tests don't pass

$te_n = microtime(true); 

$et_n = ($te_n -$ts_n);

echo PHP_EOL."STARTING NEW".PHP_EOL;

$ty_n = microtime(true); 

for($i = 0; $i < NUMBER_RUNS; $i++)
	shell_exec("gdal_translate ../resources/b.tif output.png -of PNG");

$tr_n = microtime(true); 

$ey_n = ($tr_n -$ty_n);

echo "GDAL Extension Time: ".$et_n.PHP_EOL;
echo "GDAL Shell Exec Time: ".$ey_n.PHP_EOL;