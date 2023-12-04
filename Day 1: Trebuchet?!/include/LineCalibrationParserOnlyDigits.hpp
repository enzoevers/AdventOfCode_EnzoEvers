#pragma once

#include "ILineCalibrationParser.hpp"

class LineCalibrationParserOnlyDigits : public ILineCalibrationParser {
public:
    int getCalibrationValue(std::string const & line) override;
    int charToInt(const char & c);
};