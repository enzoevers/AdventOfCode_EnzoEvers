#pragma once

#include "../include/StringManipulation.hpp"
#include <algorithm>
#include <cctype>

std::string
StringManipulation::toLowerString(const std::string &str) {
    size_t strLength = str.length();
    std::string lowerString(strLength, ' ');

    for (int i = 0; i < strLength; i++) {
        lowerString[i] = std::tolower(str.at(i));
    }
}