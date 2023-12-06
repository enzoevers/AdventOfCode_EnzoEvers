#include "../include/Almanac.hpp"
#include <iostream>

void
Almanac::parseAlmanac(std::stringstream &almanacString) {
    almanacString.seekg(0, almanacString.beg);

    std::string line;
    while (std::getline(almanacString, line)) {
        if (line.find("seeds") != std::string::npos) {
            parseSeedsFromAlmanac(line);
        }
    }
}

void
Almanac::parseSeedsFromAlmanac(const std::string &line) {
    std::size_t startIndex = line.find(' ');
    std::size_t endIndex = line.find(' ', startIndex + 1);
    while (startIndex != std::string::npos) {
        startIndex++;

        std::string seedIdString;
        if (endIndex != std::string::npos) {
            seedIdString = line.substr(startIndex, endIndex - startIndex);
        } else {
            seedIdString = line.substr(startIndex);
        }

        uint64_t seedId = std::stoull(seedIdString);

        seedIds.push_back(seedId);

        startIndex = endIndex;
        if (startIndex != std::string::npos) {
            endIndex = line.find(' ', startIndex + 1);
        }
    }
}

uint64_t
Almanac::getLocationFromSeed(uint64_t seedId) {}