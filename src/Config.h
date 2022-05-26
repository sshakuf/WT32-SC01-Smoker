#ifndef _CONFIG_H
#define _CONFIG_H


#include "SPIFFS.h"
#include <SPIFFSIniFile.h>

class Config
{
    public:
    
        void Load(const char *inFilename)
        {
            strcpy(filename, inFilename);
            char buffer[bufferLen];
        
            if (!SPIFFS.begin())
            while (1)
            Serial.println("SPIFFS.begin() failed");
        
            ini = new SPIFFSIniFile(filename);
            if (!ini->open()) {
            Serial.print("Ini file ");
            Serial.print(filename);
            Serial.println(" does not exist");
            // Cannot do anything else
            while (1)
            ;
        }
        Serial.println("Ini file exists");

        // Check the file is valid. This can be used to warn if any lines
        // are longer than the buffer.
        if (!ini->validate(buffer, bufferLen)) {
            Serial.print("ini file ");
            Serial.print(ini->getFilename());
            Serial.print(" not valid: ");
            Serial.println(ini->getError());
            // // Cannot do anything else
            // while (1)
            //   ;
        }
        

            GetIniValue("network", "ssid", ssid, bufferLen);
            GetIniValue("network", "password", password, bufferLen);

        
        };

        bool GetIniValue(const char* category, const char* param, char* buffer, const size_t bufferLen) 
        {
        bool retVal = false;  
        // Fetch a value from a key which is present
        if (ini->getValue(category, param, buffer, bufferLen)) {
            Serial.print("section 'network' has an entry 'ssid' with value ");
            Serial.println(buffer);
            retVal = true;
        }
        else {
            Serial.print("Could not read 'network' from section 'ssid', error was ");
            Serial.println(ini->getError());
        }

        return retVal;
        }


        char* getSSID()
        {
        return ssid;
        }
        char* getPassword()
        {
            return password;
        }


    private:
    char filename[250];
    static const size_t bufferLen = 80;
    // const char *filename = "/data.ini";
  

    SPIFFSIniFile* ini;

    char ssid[bufferLen];
    char password[bufferLen];


};



#endif // _CONFIG_H.H


