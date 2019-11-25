<?php
$time_start = microtime(true); 

gdal_register_all_drivers();

$beginX = 0;
$beginY = 0;
$midX = 256;
$midY = 256;

echo "cropping to:"."-srcwin $beginX $beginY $midX $midY";

gdal_translate('../resources/b.tif', 'output_cropped.tif',"-srcwin $beginX $beginY $midX $midY"); //cut the image in half
$time_end = microtime(true); 

echo PHP_EOL.($time_end-$time_start)." seconds elapsed".PHP_EOL;