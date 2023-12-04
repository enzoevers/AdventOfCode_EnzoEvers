#pragma once

#include <array>
#include <fstream>
#include <string>
#include <utility>

template <std::size_t blockWidth, std::size_t blockHeight>
class SchematicReader : public ICoordinateHelper {
  private:
    std::ifstream stream;
    std::pair<std::size_t, std::size_t> schematicDimensions;

    void assignSchematicDimensions();

  public:
    SchematicReader(const std::string &filePath);
    ~SchematicReader();

    /*
     * If the the block would go out of range of the schematic,
     * this space is filles with '.'
     */
    std::array<char, (blockWidth * blockHeight)>
    getBlock(std::pair<std::size_t, std::size_t> topLeftCoordinate);

    std::size_t getBlockLengthAndWidth() { return blockLengthAndWidth; }

    //--------------------
    // ICoordinateHelper
    //--------------------
    std::size_t coordiate2dToLinear(
        std::pair<std::size_t, std::size_t> coordinate) override;
};