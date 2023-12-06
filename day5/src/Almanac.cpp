#include "../include/Almanac.hpp"
#include <iostream>

void
Almanac::parseAlmanac(std::stringstream &almanacString) {
    almanacString.seekg(0, almanacString.beg);

    std::string line;
    while (std::getline(almanacString, line)) {
        if (line.find("seeds") != std::string::npos) {
            parseSeedsFromAlmanac(line);
        } else if (line.find("seed-to-soil") != std::string::npos) {
            parseMultiMap(almanacString, seedToSoil);
        }
    }
}

void
Almanac::parseSeedsFromAlmanac(const std::string &line) {
    seedIds.clear();
    seedIds.shrink_to_fit();

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

void
Almanac::parseMultiMap(std::stringstream &almanacString, MultiMap &multiMap) {
    std::string line;
    std::getline(almanacString, line);

    while (!line.empty()) {

        std::getline(almanacString, line);
    }
}

Mapping
Almanac::parseMapping(const std::string &line) {

    std::size_t firstSpaceIndex = line.find(' ');
    std::size_t secondSpaceIndex = line.find(' ', firstSpaceIndex + 1);

    std::string dstStartIdString = line.substr(0, firstSpaceIndex);
    std::string srcStartIdString =
        line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex);
    std::string rangeString = line.substr(secondSpaceIndex + 1);

    return Mapping(std::stoull(srcStartIdString), std::stoull(dstStartIdString),
                   std::stoull(rangeString));
}

uint64_t
Almanac::getLocationFromSeed(uint64_t seedId) {}