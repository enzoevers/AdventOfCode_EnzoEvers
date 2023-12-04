#pragma once

#include "ILineCalibrationParser.hpp"

class LineCalibrationParserDigitsAndWords : public ILineCalibrationParser {
  public:
    int getCalibrationValue(const std::string &line) override;

  private:
    int findFirstNumberInWordOrDigit(const std::string &line);
    int findLastNumberInWordOrDigit(const std::string &line);
};