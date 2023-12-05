#pragma once

#include "./I2DFileReader.hpp"
#include "./IFileReader.hpp"

#include <string>
#include <utility>

class SchematicReader : public I2DFileReader {
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

    bool
    getReadingAndPaddingColumns(const MatrixCoordinate &topLeftCoordinate,
                                std::pair<std::size_t, std::size_t> blockSize,
                                std::size_t &readingColumns,
                                std::size_t &paddingColumns);

    bool getReadingAndPaddingRows(const MatrixCoordinate &topLeftCoordinate,
                                  std::pair<std::size_t, std::size_t> blockSize,
                                  std::size_t &readingRows,
                                  std::size_t &paddingRows);

    //====================
    // I2DFileReader
    //====================

    /*
     * If the the block would go out of range of the schematic,
     * this space is filles with '.'
     */
    bool getBlock(const MatrixCoordinate &topLeftCoordinate,
                  std::vector<char> &block,
                  std::pair<std::size_t, std::size_t> blockSize) override;

    std::pair<std::size_t, std::size_t> getFileDimensionsNoNewlines() override {
        return schematicDimensions;
    }
};