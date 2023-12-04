#pragma once

#include <array>
#include <fstream>
#include <string>
#include <utility>

template <std::size_t blockLengthAndWith> class SchematicReader {
  private:
    std::ifstream stream;

  public:
    SchematicReader(const std::string &filePath, );
    ~SchematicReader();

    std::array<char, blockLengthAndWith>
    getBlock(std::pair<std::size_t, std::size_t> topLeftCoordinate);
};