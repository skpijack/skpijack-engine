#pragma once

#include <string>
#include <iostream> 

class mog {
    // ERROR TYPES
    // 0 -> Fatal | Close Application
    // 1 -> Error
    // 2 -> Warning
    // 3 -> Info
    // 4 -> Debug Info
public:
    static void it(std::string prompt, const unsigned int errortype) {
        switch (errortype) {
            case 0: {
            std::cerr << "FATAL: " << prompt << std::endl;
            std::exit(-1);
            }; break;
            case 1: {
            std::cerr << "ERROR: " << prompt << std::endl;
            }; break;
            case 2: {
            std::cout << "Warning: " << prompt << std::endl;
            }; break;
            case 3: {
            std::cout << "Info: " << prompt << std::endl;
            }; break;
            case 4: {
            #ifndef NDEBUG
            std::cout << "DEBUG: " << prompt << std::endl;
            #endif
            }; break;
        };
    }
};