#pragma once

#include "./MultiMap.hpp"

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
    void parseAlmanac(const std::string &almanacString);
    int getLocationFromSeed(int seedId);
};