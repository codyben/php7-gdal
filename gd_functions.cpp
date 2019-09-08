#include <phpcpp.h>
extern "C" {
#include <gdal/gdal.h>
#include <gdal/gdal_utils.h>
#include <stdlib.h>
}
#include <iostream>
#include <string>

extern "C" {

Php::Value gdal_registered_drivers()
{
	int count = GDALGetDriverCount(); //returns the number of currently registered drivers (int)

	return count;
}

Php::Value gdal_register_all_drivers()
{
	GDALAllRegister(); //not sure how to treat errors here, so its a void
}

Php::Value gdal_info(Php::Parameters &params) //todo
{
    if(gdal_registered_drivers() == 0){
		Php::error << "No GDAL Drivers detected" << std::flush;
		return FALSE;
    }

    Php::Value inter = params[0];

    std::string f = inter;
    char** papszArgv = (char**)calloc(1, sizeof(char*));

	papszArgv[0] = "-json\0";

	GDALInfoOptions* rzecz = GDALInfoOptionsNew(papszArgv, NULL);

	GDALDatasetH ds = GDALOpenEx(f.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL);

	if(ds == NULL){
		Php::warning << "No file found for "+f << std::flush;
	}

	char* vals = GDALInfo(ds, rzecz);

	std::string returnValue(vals);

	return returnValue; //this outputs JSON, which I'll ideally convert into a native PHP Array





}

Php::Value gdal_translate(Php::Parameters &params) //todo
{
    Php::out << "example output" << std::endl;
    return -1;
}

Php::Value gdal_warp(Php::Parameters &params)
{
    Php::out << "example output" << std::endl;
    return -1;
}
}