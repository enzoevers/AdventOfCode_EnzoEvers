#pragma once

#include "./I2DFileReader.hpp"

class SchematicProcessing {
  private:
    const char ignoreCharacter = '.';
    std::pair<std::size_t, std::size_t> blockSize = std::make_pair(12, 12);

  public:
    int processSchematic(I2DFileReader &fileReader2d);
};