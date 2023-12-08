#include "./include/ScratchCard.hpp"
#include <fstream>
#include <iostream>
#include <iterator>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    ScratchCard scratchCard;

    std::ifstream file(argv[1]);
    std::string card;
    uint32_t totalPoints = 0;
    while (std::getline(file, card)) {
        scratchCard.parseCardString(card);
        totalPoints += scratchCard.getPoints();
    }

    std::cout << "totalPoints: " << totalPoints << std::endl;

    return 0;
}