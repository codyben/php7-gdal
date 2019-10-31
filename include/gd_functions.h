#include <phpcpp.h>
extern "C" {
	//at this point, I'm more concerned with making sure everything links correctly and PHP behaves, hence all the void types
	Php::Value gdal_info(Php::Parameters &params); //mirrors gdalinfo functionality
	Php::Value gdal_translate(Php::Parameters &params); //mirrors gdal_translate functionality
	Php::Value gdal_warp(Php::Parameters &params); //mirrors gdalwarp functionality
	Php::Value gdal_register_all_drivers(); //load all available drivers & print number loaded
	Php::Value gdal_registered_drivers(); //get numeric count of loaded drivers
	Php::Value gdal_addo(); //build or rebuild an overview image
	Php::Value gdal_rasterize(); //move vector geometry onto an image
	Php::Value gdal_config(); //output information about the gdal installation
	Php::Value gdal_unload_drivers(); //unload all gdal drivers
}