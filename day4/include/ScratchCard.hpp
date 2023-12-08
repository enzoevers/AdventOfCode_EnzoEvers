#pragma once

#include <stdint.h>
#include <string>
#include <vector>

class ScratchCard {
  private:
    std::vector<uint32_t> winningNumbers;
    std::vector<uint32_t> myNumbers;

    static std::vector<uint32_t>
    stringToSortedVector(const std::string &numberString, char deliminator);
    static std::size_t getNextNumberIndex(const std::string &str,
                                          std::size_t startIndex);

  public:
    void parseCardString(const std::string &card);

    const std::vector<uint32_t> &getWinningNumbers() const {
        return winningNumbers;
    }
    const std::vector<uint32_t> &getMyNumbers() const { return myNumbers; }

    uint32_t getPoints();
};