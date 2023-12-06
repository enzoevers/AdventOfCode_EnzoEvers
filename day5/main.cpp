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

    const std::vector<int> &seedIds = almanac.getSeedIds();

    int minLocation = std::numeric_limits<int>::max();
    for (int s : seedIds) {
        int location = almanac.getLocationFromSeed(s);

        if (location < minLocation) {
            minLocation = location;
        }
    }

    std::cout << "minLocation: " << minLocation << std::endl;

    return 0;
}