#include "../include/ScratchCard.hpp"
#include "../include/TextToInt.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>

//====================
// Public
//====================

void
ScratchCard::parseCardString(const std::string &card) {
    if (card.empty()) {
        throw std::length_error("Error: card cannot be empty");
    }

    //--------------------
    // Clear data from vectors
    //--------------------
    winningNumbers.clear();
    winningNumbers.shrink_to_fit();

    myNumbers.clear();
    myNumbers.shrink_to_fit();

    //--------------------
    // Identify indexes of interest
    //--------------------
    std::size_t startIndexWinningNumbers = card.find(':') + 1;
    if (startIndexWinningNumbers == std::string::npos) {
        // TODO: throw;
    }

    std::size_t endIndexWinningNumbers =
        card.find('|', startIndexWinningNumbers) - 1;
    if (startIndexWinningNumbers == std::string::npos) {
        // TODO: throw;
    }

    std::size_t startIndexMyNumbers = endIndexWinningNumbers + 2;
    std::size_t endIndexMyNumbers = card.length() - 1;

    //--------------------
    // Set the card vectors
    //--------------------
    std::string substr =
        card.substr(startIndexWinningNumbers,
                    endIndexWinningNumbers - startIndexWinningNumbers + 1);
    winningNumbers = stringToSortedVector(substr, ' ');

    substr = card.substr(startIndexMyNumbers,
                         endIndexMyNumbers - startIndexMyNumbers + 1);
    myNumbers = stringToSortedVector(substr, ' ');
}

uint32_t
ScratchCard::getPoints() {
    uint32_t points = 0;
    uint32_t matchCount = 0;

    auto curWinningNumber = winningNumbers.begin();
    for (auto n : myNumbers) {
        while (curWinningNumber != winningNumbers.end() &&
               *curWinningNumber < n) {
            // The arrays are sorted. Meaning that if
            // curWinningNumber < n, curWinningNumber
            // curWinningNumber will never be matched.
            ++curWinningNumber;
        }

        if (curWinningNumber == winningNumbers.end()) {
            break;
        }

        if (n == *curWinningNumber) {
            ++matchCount;
            ++curWinningNumber;
        }
    }

    points = pow(2, matchCount - 1);

    return points;
}

//====================
// Private
//====================

std::vector<uint32_t>
ScratchCard::stringToSortedVector(const std::string &numbersString,
                                  char deliminator) {
    std::vector<uint32_t> vec;

    if (numbersString.empty()) {
        return vec;
    }

    std::size_t startIndex = getNextNumberIndex(numbersString, 0);
    if (startIndex == std::string::npos) {
        return vec;
    }

    std::size_t endIndex = numbersString.find(deliminator, startIndex);
    while (startIndex != std::string::npos) {

        if (endIndex == std::string::npos) {
            endIndex = numbersString.length();
        }
        std::string numberStr =
            numbersString.substr(startIndex, endIndex - startIndex);
        uint32_t number;
        try {
            number = std::stoul(numberStr);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            throw;
        }

        vec.push_back(number);

        startIndex = getNextNumberIndex(numbersString, endIndex);
        endIndex = numbersString.find(deliminator, startIndex);
    }

    std::sort(vec.begin(), vec.end());

    return vec;
}

std::size_t
ScratchCard::getNextNumberIndex(const std::string &str,
                                std::size_t startIndex) {

    std::size_t curIndex = startIndex;
    std::size_t strLength = str.length();
    while (curIndex < strLength &&
           TextToInt::charToInt(str.at(curIndex)) == -1) {
        ++curIndex;
    }

    return curIndex == strLength ? std::string::npos : curIndex;
}