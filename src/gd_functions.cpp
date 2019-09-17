extern "C" {
#include <gdal/gdal.h>
#include <gdal/gdal_utils.h>
#include <stdlib.h>
#include <strings.h>
}
#include <iostream>
#include <string>
#include <phpcpp.h>
extern "C" {

	Php::Value gdal_registered_drivers()
	{
		Php::Value count = GDALGetDriverCount(); //returns the number of currently registered drivers (int)
		return count;
	}

	Php::Value gdal_register_all_drivers()
	{
		GDALAllRegister();
		return gdal_registered_drivers(); //return number of registered drivers.
	}

	Php::Value gdal_info(Php::Parameters &params) //todo
	{
	    if(gdal_registered_drivers() == 0){
			Php::error << "No GDAL Drivers detected" << std::flush;
			return false;
	    }
	    //Php::warning << params.size() << std::endl;
	    Php::Value inter = params[0];
	 	//Php::warning << "no fault4" << std::endl;
	    std::string f = inter;
	    char** papszArgv = (char**)calloc(1,sizeof(char*));
	   //Php::warning << "no fault1" << std::endl;

	    //Php::warning << "no fault" << std::endl;
		papszArgv[0] = "-json\0";

		GDALInfoOptions* rzecz = GDALInfoOptionsNew(papszArgv, NULL);

		free(papszArgv);

		GDALDatasetH ds = GDALOpenEx(f.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL);

		if(ds == NULL){
			Php::warning << "No file found for "+f << std::flush;
			return false;
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

	Php::Value gdal_warp(Php::Parameters &params) //todo
	{
	    Php::out << "example output" << std::endl;
	    return -1;
	}

	Php::Value gdal_rasterize(Php::Parameters &params) //todo
	{
		return -1;
	}

	Php::Value gdal_addo(Php::Parameters &params) //todo
	{
		return -1;
	}

	Php::Value gdal_config(Php::Parameters &params) //todo
	{
		return -1;
	}
}