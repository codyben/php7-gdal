extern "C" {
#include <gdal/gdal.h>
#include <gdal/gdal_utils.h>
#include <stdlib.h>
#include <strings.h>
}
#include <iostream>
#include <vector>
#include <string>
#include <phpcpp.h>
extern "C" {

	//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
	std::vector<std::string> split (std::string s, std::string delimiter) 
	{
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
			token = s.substr (pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back (token);
		}

		res.push_back (s.substr (pos_start));
		return res;
	}

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
			Php::warning << "No GDAL Drivers detected" << std::flush;
			return false;
	    }

	    Php::Value inter = params[0];

	    std::string f = inter;
	    char** papszArgv = (char**)calloc(1,sizeof(char*));

		papszArgv[0] = "-json\0";

		GDALInfoOptions* rzecz = GDALInfoOptionsNew(papszArgv, NULL);

		free(papszArgv);

		GDALDatasetH ds = GDALOpenEx(f.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL);

		if(ds == NULL){
			Php::warning << "No file found for "+f << std::flush;
			return false;
		}

		char* vals = GDALInfo(ds, rzecz);

		GDALInfoOptionsFree(rzecz);
		GDALClose(ds);

		std::string returnValue(vals);
		free(vals);

		return returnValue; //this outputs JSON, which I'll ideally convert into a native PHP Array

	}

	Php::Value gdal_translate(Php::Parameters &params) //todo
	{
		if(gdal_registered_drivers() == 0){
			Php::warning << "No GDAL Drivers detected" << std::flush;
			return false;
	    }

		Php::Value fileNameInput = params[0];
		std::string fileNameInputcpp = fileNameInput;

		

		GDALDatasetH ds = GDALOpenEx(fileNameInputcpp.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL);
		if(ds == NULL) {
			Php::warning << "No file found for "+fileNameInput << std::flush;
			return false;
		}


		Php::Value fileNameOutput = params[1];
		std::string fileNameOutputcpp = fileNameOutput;
		const char* fNOC = fileNameOutputcpp.c_str();

		Php::Value opString = params[2];

		std::string opStringcpp = opString;

		std::vector<std::string> parsedArgs = split(opStringcpp, " ");

		char** papszArgv = (char**)calloc(parsedArgs.size(),sizeof(char*));

		int i = 0;
		char* intermediate;
		for(i = 0; i < parsedArgs.size(); i++) {
			intermediate = (char*)parsedArgs.at(i).c_str();
			papszArgv[i] = intermediate; //push all the input strings into a const char* array for gdal_translate
		} 
	

		GDALTranslateOptions* papszOptions = GDALTranslateOptionsNew(papszArgv, NULL);

		GDALDatasetH dsH = GDALTranslate(fNOC, ds, papszOptions, NULL); //pass the 
		
		GDALClose(ds);

		if(dsH != NULL){
			GDALClose(dsH);
			return true;
		}
		else
			return false;
		

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