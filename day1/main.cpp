#include "include/CalibrationDataReader.hpp"
#include "include/LineCalibrationParserDigitsAndWords.hpp"
#include "include/LineCalibrationParserOnlyDigits.hpp"
#include <iostream>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    CalibrationDataReader reader;
    LineCalibrationParserOnlyDigits parserOnlyDigits;
    LineCalibrationParserDigitsAndWords parserDigitsAndWords;

    reader.getSumOfCalibrationValues(file, parserOnlyDigits);
    reader.getSumOfCalibrationValues(file, parserDigitsAndWords);

    file.close();

    return 0;
}