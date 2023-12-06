#include "../include/Almanac.hpp"
#include <iostream>

void
Almanac::parseSeedsFromAlmanac(std::stringstream &almanacString) {
    almanacString.clear();
    almanacString.seekg(0, almanacString.beg);

    std::string line;
    while (std::getline(almanacString, line)) {
        if (line.find("seeds") != std::string::npos) {
            parseSeedsFromLine(line);
            break;
        }
    }
}

void
Almanac::parseMapsFromAlmanac(std::stringstream &almanacString) {
    almanacString.clear();
    almanacString.seekg(0, almanacString.beg);

    std::string line;
    while (std::getline(almanacString, line)) {
        if (line.find("seed-to-soil") != std::string::npos) {
            parseMultiMap(almanacString, seedToSoil);
        } else if (line.find("soil-to-fertilizer") != std::string::npos) {
            parseMultiMap(almanacString, soilToFertilizer);
        } else if (line.find("fertilizer-to-water") != std::string::npos) {
            parseMultiMap(almanacString, fertilizerToWater);
        } else if (line.find("water-to-light") != std::string::npos) {
            parseMultiMap(almanacString, waterToLight);
        } else if (line.find("light-to-temperature") != std::string::npos) {
            parseMultiMap(almanacString, lightToTemperature);
        } else if (line.find("temperature-to-humidity") != std::string::npos) {
            parseMultiMap(almanacString, temperatureToHumidity);
        } else if (line.find("humidity-to-location") != std::string::npos) {
            parseMultiMap(almanacString, humidityToLocation);
        }
    }
}

void
Almanac::parseSeedsFromLine(const std::string &line) {
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
    multiMap.clearMappings();

    std::string line;
    std::getline(almanacString, line);

    while (!almanacString.eof() && !line.empty()) {
        Mapping mapping = parseMapping(line);
        multiMap.mappings.push_back(mapping);
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
Almanac::getLocationFromSeed(uint64_t seedId) {
    uint64_t soilId = seedToSoil.map(seedId);
    uint64_t fertilizerId = soilToFertilizer.map(soilId);
    uint64_t waterId = fertilizerToWater.map(fertilizerId);
    uint64_t lightId = waterToLight.map(waterId);
    uint64_t temperatureId = lightToTemperature.map(lightId);
    uint64_t humidityId = temperatureToHumidity.map(temperatureId);
    uint64_t locationId = humidityToLocation.map(humidityId);

    return locationId;
}

uint64_t
Almanac::getSeedFromLocation(uint64_t locationId) {
    uint64_t humidityId = humidityToLocation.rmap(locationId);
    uint64_t temperatureId = temperatureToHumidity.rmap(humidityId);
    uint64_t lightId = lightToTemperature.rmap(temperatureId);
    uint64_t waterId = waterToLight.rmap(lightId);
    uint64_t fertilizerId = fertilizerToWater.rmap(waterId);
    uint64_t soilId = soilToFertilizer.rmap(fertilizerId);
    uint64_t seedId = seedToSoil.rmap(soilId);

    return seedId;
}