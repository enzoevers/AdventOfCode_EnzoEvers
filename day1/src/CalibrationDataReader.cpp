#include "../include/CalibrationDataReader.hpp"

#include <iostream>

int
CalibrationDataReader::getSumOfCalibrationValues(
    std::ifstream &file, ILineCalibrationParser &lineCalibrationParser) {
    int sum = 0;

    file.clear();
    file.seekg(0, file.beg);

    for (std::string line; std::getline(file, line);) {
        int calibrationValue = lineCalibrationParser.getCalibrationValue(line);
        sum += calibrationValue;
    }

    std::cout << "sum: " << sum << std::endl;

    return sum;
}