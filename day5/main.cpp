#include "./include/Almanac.hpp"
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    Almanac almanac;

    {
        std::stringstream buffer;
        {
            std::ifstream file(argv[1]);
            buffer << file.rdbuf();
        }

        almanac.parseAlmanac(buffer);
    }

    const std::vector<uint64_t> &seedIds = almanac.getSeedIds();

    uint64_t minLocation = std::numeric_limits<uint64_t>::max();
    for (uint64_t s : seedIds) {
        uint64_t location = almanac.getLocationFromSeed(s);

        if (location < minLocation) {
            minLocation = location;
        }
    }

    std::cout << "minLocation: " << minLocation << std::endl;

    return 0;
}