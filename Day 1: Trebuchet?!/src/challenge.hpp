#pragma once

#include <fstream>

int charToInt(const char & c);

// It is assumes that the intiger to look for is >=0
// Returning -1 means that no integer is found.
int getFirstInteger(std::string const & line);
int getSumOfCalibrationValues(std::ifstream& file);