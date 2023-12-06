#pragma once

#include "./MultiMap.hpp"
#include <sstream>

class Almanac {
  private:
    std::vector<uint64_t> seedIds;
    MultiMap seedToSoil;
    MultiMap soilToFertilizer;
    MultiMap fertilizerToWater;
    MultiMap waterToLight;
    MultiMap lightToTemperature;
    MultiMap temperatureToHumidity;
    MultiMap humidityToLocation;

  public:
    const std::vector<uint64_t> &getSeedIds() const { return seedIds; }

    void parseAlmanac(std::stringstream &almanacString);
    uint64_t getLocationFromSeed(uint64_t seedId);

    void parseSeedsFromAlmanac(const std::string &line);
};