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

std::size_t
getLineCount(std::ifstream &file) {
    size_t n = 0;
    std::string dummyString;
    while (std::getline(file, dummyString)) {
        n++;
    }

    // Go Back to the beginning
    file.clear();
    file.seekg(0, file.beg);

    return n;
}

void
printCardCount(const std::vector<uint32_t> &cardCount) {
    std::cout << "cardCount: " << std::endl;
    for (auto c : cardCount) {
        std::cout << c << std::endl;
    }
}

uint32_t
playPart2(const std::string &filePath) {
    ScratchCard scratchCard;

    std::ifstream file(filePath);
    std::string card;

    const std::size_t lineCount = getLineCount(file);

    std::vector<uint32_t> cardCount;
    cardCount.reserve(lineCount);

    for (std::size_t i = 0; i < lineCount; ++i) {
        cardCount.push_back(0);
    }

    std::size_t curIndex = 0;
    while (std::getline(file, card)) {
        scratchCard.parseCardString(card);
        uint32_t matchCount = scratchCard.getPoints().first;

        ++cardCount.at(curIndex);
        uint32_t curCardCount = cardCount.at(curIndex);
        for (std::size_t i = curIndex + 1;
             i <= (curIndex + matchCount) && i < lineCount; ++i) {
            cardCount.at(i) += curCardCount;
        }

        ++curIndex;
    }

    uint32_t totalCards = 0;
    for (auto c : cardCount) {
        totalCards += c;
    }

    std::cout << "totalCards: " << totalCards << std::endl;

    return totalCards;
}
