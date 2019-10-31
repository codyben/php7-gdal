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
	/**
	 * Description: calls out to the GDAL C API and returns the count of currently loaded GDAL drivers
	 * Returns: PHP int
	 */
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
			Php::warning << "No GDAL Drivers detected" << std::flush; // if we have no drivers loaded, error the user out.
			return false;
	    }

	    Php::Value inter = params[0]; //grab the file name from PHP userspace

	    std::string f = inter; //convert our PHP::String into a string
	    char** papszArgv = (char**)calloc(1,sizeof(char*)); //allocate memory for the arguments to the command

		papszArgv[0] = "-json\0"; //pass the json argument

		GDALInfoOptions* rzecz = GDALInfoOptionsNew(papszArgv, NULL); //Allocate a pointer for our options.

		free(papszArgv[0]); //free up option
		free(papszArgv); //with our args passed in, we can free the memory now.

		GDALDatasetH ds = GDALOpenEx(f.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL); //open the dataset in a read-only fashion

		if(ds == NULL){
			Php::warning << "No file found for "+f << std::flush; //if we can't open the file, send a warning to the user.
			return false;
		}

		char* vals = GDALInfo(ds, rzecz); //the json array returned to us.

		if(vals == NULL) { //if we have null here, something bad happened so return a false and flash a warning.
			Php::warning << "An error occured in returning information on the dataset." << std::flush;
			return false;
		} 

		GDALInfoOptionsFree(rzecz); //free up our options and opened dataset.
		GDALClose(ds);

		std::string returnValue(vals);
		free(vals); //with our values put into our PHP string, free them.

		return returnValue; //this outputs JSON, which I'll ideally convert into a native PHP Array

	}

	Php::Value gdal_translate(Php::Parameters &params) //todo
	{
		if(gdal_registered_drivers() == 0){
			Php::warning << "No GDAL Drivers detected" << std::flush;
			return false;
	    }

		Php::Value fileNameInput = params[0];
		std::string fileNameInputcpp = fileNameInput; //put our php string into a string.

		

		GDALDatasetH ds = GDALOpenEx(fileNameInputcpp.c_str(), GDAL_OF_READONLY | GDAL_OF_RASTER | GDAL_OF_VERBOSE_ERROR | GDAL_OF_VECTOR, NULL, NULL, NULL); //open the dataset as readonly
		if(ds == NULL) {
			Php::warning << "No file found for "+fileNameInput << std::flush; //error out if we can't find the dataset to open.
			return false;
		}


		Php::Value fileNameOutput = params[1]; //grab PHP String for output.
		std::string fileNameOutputcpp = fileNameOutput; //convert to cpp string.
		const char* fNOC = fileNameOutputcpp.c_str(); //convert to const 

		Php::Value opString = params[2]; //PHP String of our operators.

		std::string opStringcpp = opString; //convert to cpp string.

		std::vector<std::string> parsedArgs = split(opStringcpp, " "); //parse our argument string.

		char** papszArgv = (char**)calloc(parsedArgs.size(),sizeof(char*)); //create a character array to store our args.

		int i = 0;
		char* intermediate;
		for(i = 0; i < parsedArgs.size(); i++) {
			intermediate = (char*)parsedArgs.at(i).c_str();
			papszArgv[i] = intermediate; //push all the input strings into a const char* array for gdal_translate
		} 
	

		GDALTranslateOptions* papszOptions = GDALTranslateOptionsNew(papszArgv, NULL);

		GDALDatasetH dsH = GDALTranslate(fNOC, ds, papszOptions, NULL); //pass the 
		
		GDALClose(ds);
		free(papszArgv);

		GDALTranslateOptionsFree(papszOptions);

		if(dsH != NULL){
			GDALClose(dsH);
			return true;
		}
		else
			return false;
		

	}

	/**
	 * Description: Unload all loaded GDAL drivers from memory.
	 * Returns: void
	 */ 
	Php::Value gdal_unload_drivers() {
		GDALDestroyDriverManager();
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