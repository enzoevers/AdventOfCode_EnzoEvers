#include "./include/Almanac.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

uint64_t
getLowestSeedId(const std::vector<uint64_t> &seedIds) {
    uint64_t smallestSeedId = std::numeric_limits<uint64_t>::max();

    std::size_t bound = seedIds.size() / 2;

    for (std::size_t i = 0; i < bound; i++) {
        std::size_t index = i * 2;

        uint64_t startId = seedIds.at(index);
        if (startId < smallestSeedId) {
            smallestSeedId = startId;
        }
    }

    return smallestSeedId;
}

bool
doesSeedExistPart2(uint64_t seedId, const std::vector<uint64_t> &seedIds) {
    bool seedExists = false;

    std::size_t bound = seedIds.size() / 2;

    for (std::size_t i = 0; i < bound; i++) {
        std::size_t index = i * 2;

        uint64_t startId = seedIds.at(index);
        uint64_t count = seedIds.at(index + 1);

        if (seedId < startId) {
            continue;
        }

        if (seedId >= (startId + count)) {
            // seedId is larger than the range
            continue;
        }

        // The seedId is in the range
        seedExists = true;
        break;
    }

    return seedExists;
}

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    Almanac almanac;

    std::stringstream buffer;
    {
        std::ifstream file(argv[1]);
        buffer << file.rdbuf();
    }

    almanac.parseSeedsFromAlmanac(buffer);
    almanac.parseMapsFromAlmanac(buffer);

    const std::vector<uint64_t> &seedIds = almanac.getSeedIds();

    // Part 1
    {
        uint64_t minLocation = std::numeric_limits<uint64_t>::max();
        for (uint64_t s : seedIds) {
            uint64_t location = almanac.getLocationFromSeed(s);

            if (location < minLocation) {
                minLocation = location;
            }
        }

        std::cout << "minLocation part 1: " << minLocation << std::endl;
    }

    // Part 2
    {
        uint64_t minLocation = 0;

        uint64_t seedId = almanac.getSeedFromLocation(minLocation);
        bool foundSeed = doesSeedExistPart2(seedId, seedIds);
        while (!foundSeed) {
            uint64_t seedId = almanac.getSeedFromLocation(++minLocation);
            foundSeed = doesSeedExistPart2(seedId, seedIds);
        }

        std::cout << "minLocation part 2: " << minLocation << std::endl;
    }

    return 0;
}