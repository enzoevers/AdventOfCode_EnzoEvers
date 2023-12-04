#pragma once

#include <string>

class TextToInt {
  public:
    static int charToInt(const char c);
    static int stringToInt(const std::string &str);
};