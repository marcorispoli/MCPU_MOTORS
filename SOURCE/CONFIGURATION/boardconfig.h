#ifndef BOARDCONFIG_H
#define BOARDCONFIG_H

#include <QObject>
#include "configfile.h"

class boardConfig : public configFile
{
    public:


    #define REVISION     1  // This is the revision code
    #define CONFIG_FILENAME     "C:\\OEM\\Gantry\\Config\\mcpu_motors.cnf" // This is the configuration file name and path

    // This section defines labels helping the param identification along the application
    #define TRX_CANID   "TRX_CANID"
    #define SLIDE_CANID  "SLIDE_CANID"


    // your class constructor
    boardConfig():configFile( (const configFile::fileDescriptorT)
        {
            CONFIG_FILENAME, REVISION,
            {{
                { TRX_CANID,     {{ "3" }},  "TRX Motor Address"},
                { SLIDE_CANID,   {{ "4" }},  "TRX Motor Address"},

            }}
        })
    {
        // Your constructor code ...
        this->loadFile();
    };


}; // End class definition

#endif // BOARDCONFIG_H
