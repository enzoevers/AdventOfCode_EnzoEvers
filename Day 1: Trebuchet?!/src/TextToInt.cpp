#include "../include/TextToInt.hpp"

int
TextToInt::charToInt(const char c) {
    int retValue = -1;

    static const int asciiZero = 48;
    int cNormalized = static_cast<int>(c) - asciiZero;

    if (cNormalized >= 0 && cNormalized <= 9) {
        retValue = cNormalized;
    }

    return retValue;
}

int
TextToInt::stringToInt(const std::string &str) {}
