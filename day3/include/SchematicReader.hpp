#pragma once

#include "./IFileReader.hpp"
#include "./MatrixCoordinate.hpp"

#include <string>
#include <utility>
#include <vector>

class SchematicReader {
  private:
    IFileReader &fileReader;

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
    SchematicReader(IFileReader &fileReader);

    /*
     * If the the block would go out of range of the schematic,
     * this space is filles with '.'
     */
    void getBlock(const MatrixCoordinate &topLeftCoordinate,
                  std::vector<char> &block,
                  std::pair<std::size_t, std::size_t> blockSize);

    bool
    getReadingAndPaddingColumns(const MatrixCoordinate &topLeftCoordinate,
                                std::pair<std::size_t, std::size_t> blockSize,
                                std::size_t &readingColumns,
                                std::size_t &paddingColumns);

    std::pair<std::size_t, std::size_t> getSchematicDimensions() {
        return schematicDimensions;
    }
};