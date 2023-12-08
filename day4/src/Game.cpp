#include "../include/Game.hpp"
#include "../include/ScratchCard.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

uint32_t
playPart1(const std::string &filePath) {
    ScratchCard scratchCard;

    std::ifstream file(filePath);
    std::string card;
    uint32_t totalPoints = 0;
    while (std::getline(file, card)) {
        scratchCard.parseCardString(card);
        totalPoints += scratchCard.getPoints().second;
    }

    std::cout << "totalPoints: " << totalPoints << std::endl;

    return totalPoints;
}

uint32_t
playPart2(const std::string &filePath) {
    ScratchCard scratchCard;

    std::ifstream file(filePath);

    uint32_t totalCards = 0;
    std::vector<uint32_t> cardCount;

    std::cout << "totalCards: " << totalCards << std::endl;

    return 0;
}
