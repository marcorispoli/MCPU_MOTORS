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
    #define SLIDE_CANID "SLIDE_CANID"
    #define CARM_CANID  "CARM_CANID"
    #define BODY_CANID  "BODY_CANID"
    #define MVERT_CANID "MVERT_CANID"


    // your class constructor
    boardConfig():configFile( (const configFile::fileDescriptorT)
        {
            CONFIG_FILENAME, REVISION,
            {{
                { TRX_CANID,     {{ "3" }},  "TRX Motor Address"},
                { CARM_CANID,   {{ "4" }},  "SLIDE Motor Address"},
                { SLIDE_CANID,   {{ "5" }},  "CARM Motor Address"},
                { BODY_CANID,   {{ "6" }},  "CARM Motor Address"},
                { MVERT_CANID,   {{ "7" }},  "CARM Motor Address"},

            }}
        })
    {
        // Your constructor code ...
        this->loadFile();
    };


}; // End class definition

#endif // BOARDCONFIG_H
