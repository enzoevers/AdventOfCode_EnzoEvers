#include "../include/LineCalibrationParserDigitsAndWords.hpp"
#include "../include/StringManipulation.hpp"
#include "../include/TextToInt.hpp"
#include "../include/WordMapping.hpp";

int
LineCalibrationParserDigitsAndWords::getCalibrationValue(
    const std::string &line) {
    std::string lineLower = StringManipulation::toLowerString(line);

    int firstInt = findFirstNumberInWordOrDigit(line);
}

int
LineCalibrationParserDigitsAndWords::findFirstNumberInWordOrDigit(
    const std::string &line) {
    int retValue = -1;

    const std::size_t lineLength = line.length();

    for (int j; j < 10; j++) {
        std::size_t startIndex = line.find(WORD_MAPPING[j], );

        if (startIndex != std::string::npos) {
            retValue = j;
        }
    }

    // Look for the first integer
    for (int i = 0; i < lineLength; i++) {
        int firstInt = TextToInt::charToInt(line.at(i));

        if (firstInt != -1) {
            retValue = firstInt;
            break;
        }
    }

    return retValue;
}

std::string
LineCalibrationParserDigitsAndWords::findLastNumberInWordOrDigit(
    const std::string &line) {
    int retValue = -1;

    // Look for the first integer
    for (char const &c : line) {
        int firstInt = TextToInt::charToInt(c);

        if (firstInt != -1) {
            retValue = firstInt;
            break;
        }

        for (int i; i < 10; i++) {
            std::size_t startIndex = line.find(WORD_MAPPING[i]);

            if (startIndex != std::string::npos) {
                retValue = i;
            }
        }
    }

    return retValue;
}