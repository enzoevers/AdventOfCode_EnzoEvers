#pragma once

#include "./MatrixCoordinate.hpp"
#include <array>
#include <fstream>
#include <string>
#include <utility>

template <std::size_t blockWidth, std::size_t blockHeight>
class SchematicReader {
  private:
    const std::string filePath;
    std::ifstream stream;

    /*
     * first: width
     * second: height
     */
    std::pair<std::size_t, std::size_t> schematicDimensions;

    /*
     * It is assumed that the schematic is a rectangle. Meaning that
     * it is assumed that all lines have the same width.
     */
    void assignSchematicDimensions();

  public:
    SchematicReader(const std::string &filePath);
    ~SchematicReader();

    /*
     * If the the block would go out of range of the schematic,
     * this space is filles with '.'
     */
    std::array<char, (blockWidth * blockHeight)>
    getBlock(MatrixCoordinate &topLeftCoordinate);

    std::pair<std::size_t, std::size_t> getSchematicDimensions() {
        return schematicDimensions;
    }
};