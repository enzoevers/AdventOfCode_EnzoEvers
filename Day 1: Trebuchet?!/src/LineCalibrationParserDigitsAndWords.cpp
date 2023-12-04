#include "../include/LineCalibrationParserDigitsAndWords.hpp"
#include "../include/StringManipulation.hpp"
#include "../include/TextToInt.hpp"
#include "../include/WordMapping.hpp"

int
LineCalibrationParserDigitsAndWords::getCalibrationValue(
    const std::string &line) {
    int retvalue = -1;

    if (line.empty()) {
        return retvalue;
    }

    std::string lineLower = StringManipulation::toLowerString(line);

    int firstInt = findFirstNumberInWordOrDigit(lineLower);
    if (firstInt != -1) {
        retvalue = firstInt * 10;
    }

    if (retvalue != -1) {
        int secondInt = findLastNumberInWordOrDigit(lineLower);
        if (secondInt != -1) {
            retvalue += secondInt;
        }
    }

    return retvalue;
}

int
LineCalibrationParserDigitsAndWords::findFirstNumberInWordOrDigit(
    const std::string &line) {
    int retValue = -1;

    const std::size_t lineLength = line.length();

    //------------------------------
    // Find the earliest word integer
    //------------------------------
    std::size_t earliestWordIntegerIndex = std::string::npos;
    int wordInteger;

    for (std::size_t i = 0; i < 10; i++) {
        std::size_t startIndex = line.find(WORD_MAPPING[i]);

        if (startIndex == std::string::npos) {
            continue;
        }

        if (startIndex < earliestWordIntegerIndex ||
            earliestWordIntegerIndex == std::string::npos) {
            earliestWordIntegerIndex = startIndex;
            wordInteger = i;
        }
    }

    //------------------------------
    // Find the earliest number integer
    //------------------------------
    std::size_t earliestNumberIntegerIndex = std::string::npos;
    int numberInteger;

    // Look for the first integer
    for (std::size_t i = 0; i < lineLength; i++) {
        int firstInt = TextToInt::charToInt(line.at(i));

        if (firstInt != -1) {
            earliestNumberIntegerIndex = i;
            numberInteger = firstInt;
            break;
        }
    }

    //------------------------------
    // Check which one is earlier
    //------------------------------
    if (earliestWordIntegerIndex == earliestNumberIntegerIndex) {
        // Do nothing. Keep retValue -1
    } else if (earliestWordIntegerIndex == std::string::npos &&
               earliestNumberIntegerIndex != std::string::npos) {
        retValue = numberInteger;
    } else if (earliestWordIntegerIndex != std::string::npos &&
               earliestNumberIntegerIndex == std::string::npos) {
        retValue = wordInteger;
    } else if (earliestWordIntegerIndex < earliestNumberIntegerIndex) {
        retValue = wordInteger;
    } else {
        retValue = numberInteger;
    }

    return retValue;
}

int
LineCalibrationParserDigitsAndWords::findLastNumberInWordOrDigit(
    const std::string &line) {
    int retValue = -1;

    const std::size_t lineLength = line.length();

    //------------------------------
    // Find the latest word integer
    //------------------------------
    std::size_t latestWordIntegerIndex = std::string::npos;
    int wordInteger;

    for (std::size_t i = 0; i < 10; i++) {
        std::size_t startIndex = line.rfind(WORD_MAPPING[i]);

        if (startIndex == std::string::npos) {
            continue;
        }

        if (startIndex > latestWordIntegerIndex ||
            latestWordIntegerIndex == std::string::npos) {
            latestWordIntegerIndex = startIndex;
            wordInteger = i;
        }
    }

    //------------------------------
    // Find the earliest number integer
    //------------------------------
    std::size_t latestNumberIntegerIndex = std::string::npos;
    int numberInteger;

    // Look for the first integer
    for (std::size_t i = 0; i < lineLength; i++) {
        std::size_t tmpi = lineLength - 1 - i;

        int lastInt = TextToInt::charToInt(line.at(tmpi));

        if (lastInt != -1) {
            latestNumberIntegerIndex = tmpi;
            numberInteger = lastInt;
            break;
        }
    }

    //------------------------------
    // Check which one is earlier
    //------------------------------
    if (latestWordIntegerIndex == latestNumberIntegerIndex) {
        // Do nothing. Keep retValue -1
    } else if (latestWordIntegerIndex == std::string::npos &&
               latestNumberIntegerIndex != std::string::npos) {
        retValue = numberInteger;
    } else if (latestWordIntegerIndex != std::string::npos &&
               latestNumberIntegerIndex == std::string::npos) {
        retValue = wordInteger;
    } else if (latestWordIntegerIndex > latestNumberIntegerIndex) {
        retValue = wordInteger;
    } else {
        retValue = numberInteger;
    }

    return retValue;
}