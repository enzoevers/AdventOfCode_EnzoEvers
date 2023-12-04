#pragma once

#include <fstream>

int charToInt(const char & c);

// It is assumed that the integer to look for is >=0
// Returning -1 means that no integer is found.
//
// It is that is there is only 1 digit, this digit is
// used twice due to the need to a 2-digit calibration value.
int getCalibrationValue(std::string const & line);
int getSumOfCalibrationValues(std::ifstream& file);