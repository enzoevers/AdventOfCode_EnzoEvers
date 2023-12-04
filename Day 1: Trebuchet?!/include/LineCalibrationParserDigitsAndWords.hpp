#pragma once

#include "ILineCalibrationParser.hpp"

class LineCalibrationParserDigitsAndWords : public ILineCalibrationParser {
public:
    int getCalibrationValue(std::string const & line) override;
};