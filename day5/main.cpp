#include "./include/Almanac.hpp"
#include <fstream>
#include <iostream>
#include <iterator>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    std::ifstream istream(argv[1]);

    Almanac almanac;
    almanac.parseAlmanac(std::string(std::istreambuf_iterator<char>(istream),
                                     std::istreambuf_iterator<char>()));

    return 0;
}