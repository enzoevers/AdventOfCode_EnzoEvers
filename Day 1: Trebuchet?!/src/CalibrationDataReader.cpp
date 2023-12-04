#include "../include/CalibrationDataReader.hpp"

#include <iostream>

int CalibrationDataReader::getSumOfCalibrationValues(std::ifstream& file, ILineCalibrationParser& lineCalibrationParser){
    int sum = 0;

    for(std::string line; std::getline(file, line);){
        int calibrationValue = lineCalibrationParser.getCalibrationValue(line);
        sum += calibrationValue;
        std::cout << calibrationValue << ": " << line << std::endl;
        std::cout << "sum: " << sum << std::endl;
    }

    return sum;
}