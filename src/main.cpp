#include "../include/gd_functions.h"


/**
 *  tell the compiler that the get_module is a pure C function
 */

extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("php7-gdal", "1.0");
        
        // @todo    add your own functions, classes, namespaces to the extension
        extension.add<gdal_info>("gdal_info", {Php::ByVal("fileName",Php::Type::String)});
        extension.add<gdal_warp>("gdal_warp");
        extension.add<gdal_registered_drivers>("gdal_registered_drivers");
        extension.add<gdal_register_all_drivers>("gdal_register_all_drivers");
        extension.add<gdal_translate>("gdal_translate", {Php::ByVal("InputFile",Php::Type::String), Php::ByVal("OutputFile", Php::Type::String), Php::ByVal("ArgString",Php::Type::String)});
        // return the extension
        return extension;
    }
}
