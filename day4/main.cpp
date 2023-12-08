#include "./include/Game.hpp"
#include <iostream>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    playPart1(argv[1]);
    playPart2(argv[1]);

    return 0;
}