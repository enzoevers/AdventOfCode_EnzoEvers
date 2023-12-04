#include "../include/LineCalibrationParserOnlyDigits.hpp"

int LineCalibrationParserOnlyDigits::getCalibrationValue(std::string const & line){
    int retValue = -1;

    // Look for the first integer
    for(char const & c : line){
        int firstInt = charToInt(c);
        if(firstInt != -1){
            retValue = firstInt * 10;
            break;
        }
    }

    // Look for the last integer
    for(auto rIt = line.rbegin(); rIt != line.rend(); rIt++){
        int lastInt = charToInt(*rIt);
        if(lastInt != -1){
            retValue += lastInt;
            break;
        }
    }

    return retValue;
}

int LineCalibrationParserOnlyDigits::charToInt(const char & c) {
    int retValue = -1;

    static const int asciiZero = 48;
    int cNormalized = static_cast<int>(c) - asciiZero;
    
    if(cNormalized >= 0 && cNormalized <= 9){
        retValue = cNormalized;
    }

    return retValue;
}