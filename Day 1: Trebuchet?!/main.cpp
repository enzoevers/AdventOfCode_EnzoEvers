#include <iostream>
#include "include/CalibrationDataReader.hpp"
#include "include/LineCalibrationParserOnlyDigits.hpp"

int main(int argc, char** argv) {
    if(argc == 1){
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    CalibrationDataReader reader;
    LineCalibrationParserOnlyDigits parserOnlyDigits;

    reader.getSumOfCalibrationValues(file, parserOnlyDigits);

    file.close();

    return 0;
}