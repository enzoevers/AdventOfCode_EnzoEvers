#pragma once

#include <fstream>
#include "ILineCalibrationParser.hpp"


class CalibrationDataReader {
public:
    int getSumOfCalibrationValues(std::ifstream& file, ILineCalibrationParser& lineCalibrationParser);
};