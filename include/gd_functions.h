#include <phpcpp.h>
extern "C" {
	//at this point, I'm more concerned with making sure everything links correctly and PHP behaves, hence all the void types
	Php::Value gdal_info(Php::Parameters &params); //mirrors gdalinfo functionality
	void gdal_translate(); //mirrors gdal_translate functionality
	void gdal_warp(); //mirrors gdalwarp functionality
	void gdal_register_all_drivers(); //load all available drivers
	Php::Value gdal_registered_drivers(); //get numeric count of loaded drivers
}