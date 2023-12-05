#pragma once

#include "./MatrixCoordinate.hpp"
#include <string>
#include <vector>

class I2DFileReader {
  public:
    virtual ~I2DFileReader(){};

    virtual bool getBlock(const MatrixCoordinate &topLeftCoordinate,
                          std::vector<char> &block,
                          std::pair<std::size_t, std::size_t> blockSize) = 0;

    virtual std::pair<std::size_t, std::size_t>
    getFileDimensionsNoNewlines() = 0;
};