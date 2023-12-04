#pragma once

#include "ILineCalibrationParser.hpp"

class LineCalibrationParserOnlyDigits : public ILineCalibrationParser {
  public:
    int getCalibrationValue(const std::string &line) override;
};