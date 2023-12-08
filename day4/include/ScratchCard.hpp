#pragma once

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

class ScratchCard {
  private:
    uint32_t cardId;
    std::vector<uint32_t> winningNumbers;
    std::vector<uint32_t> myNumbers;

    static uint32_t stringToCardId(const std::string &cardIdString);
    static std::vector<uint32_t>
    stringToSortedVector(const std::string &numberString, char deliminator);

    static std::size_t getNextNumberIndex(const std::string &str,
                                          std::size_t startIndex);

  public:
    void parseCardString(const std::string &card);

    uint32_t getCardId() { return cardId; }
    const std::vector<uint32_t> &getWinningNumbers() const {
        return winningNumbers;
    }
    const std::vector<uint32_t> &getMyNumbers() const { return myNumbers; }

    std::pair<uint32_t, uint32_t> getPoints();
};