#pragma once

#include <functional>
#include <string>

class ILineCalibrationParser {
public:
    virtual int getCalibrationValue(std::string const & line) =0;
};