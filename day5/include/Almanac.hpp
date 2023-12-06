#pragma once

#include "./MultiMap.hpp"
#include <sstream>

class Almanac {
  private:
    std::vector<int> seedIds;
    MultiMap seedToSoil;
    MultiMap soilToFertilizer;
    MultiMap fertilizerToWater;
    MultiMap waterToLight;
    MultiMap lightToTemperature;
    MultiMap temperatureToHumidity;
    MultiMap humidityToLocation;

  public:
    const std::vector<int> &getSeedIds() const { return seedIds; }

    void parseAlmanac(std::stringstream &almanacString);
    int getLocationFromSeed(int seedId);
};