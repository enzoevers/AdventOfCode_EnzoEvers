#include "../include/LineCalibrationParserOnlyDigits.hpp"
#include "../include/TextToInt.hpp"

int LineCalibrationParserOnlyDigits::getCalibrationValue(std::string const & line){
    int retValue = -1;

    // Look for the first integer
    for(char const & c : line){
        int firstInt = TextToInt::charToInt(c);
        if(firstInt != -1){
            retValue = firstInt * 10;
            break;
        }
    }

    // Look for the last integer
    for(auto rIt = line.rbegin(); rIt != line.rend(); rIt++){
        int lastInt = TextToInt::charToInt(*rIt);
        if(lastInt != -1){
            retValue += lastInt;
            break;
        }
    }

    return retValue;
}