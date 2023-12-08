#include "../include/Game.hpp"

#include <fstream>
#include <iostream>
#include <iterator>

uint32_t
playPart1(const std::string &filePath) {
    std::ifstream file(filePath);
    uint32_t totalWinnings = 0;

    std::cout << "totalWinnings: " << totalWinnings << std::endl;

    return totalWinnings;
}

uint32_t
playPart2(const std::string &filePath) {
    std::ifstream file(filePath);
    uint32_t total = 0;

    std::cout << "total...: " << total << std::endl;

    return total;
}
