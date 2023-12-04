#pragma once

#include "ILineCalibrationParser.hpp"
#include <fstream>

class CalibrationDataReader {
  public:
    int
    getSumOfCalibrationValues(std::ifstream &file,
                              ILineCalibrationParser &lineCalibrationParser);
};