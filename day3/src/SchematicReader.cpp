#include "../include/SchematicReader.hpp"
#include <limits>
#include <stdexcept>

SchematicReader::SchematicReader(IFileReader &fileReader)
    : fileReader(fileReader) {
    assignSchematicDimensions();
}

void
SchematicReader::assignSchematicDimensions() {
    std::string dummyString;
    if (fileReader.getNextLine(dummyString)) {
        if (dummyString.empty()) {
            throw std::length_error(
                "Error: Schematic needs to have at least one non-empty line");
        }
        schematicDimensions.first = dummyString.length();
    } else {
        throw std::runtime_error("Error: expected at least one line");
    }

    // One line was already read
    size_t n = 1;
    while (fileReader.getNextLine(dummyString)) {
        n++;
    }

    schematicDimensions.second = n;
}

void
SchematicReader::getBlock(const MatrixCoordinate &topLeftCoordinate,
                          std::vector<char> &block,
                          std::pair<std::size_t, std::size_t> blockSize) {
    if (!(std::numeric_limits<std::size_t>::max() / blockSize.first >=
          blockSize.second)) {
        throw std::out_of_range("Error: the total block size is out of range");
    }

    std::size_t totalSize = blockSize.first * blockSize.second;

    if (block.capacity() < totalSize) {
        throw std::out_of_range("Error: block does not have enough capacity");
    }

    block.clear();

    for (std::size_t i = 0; i < blockSize.second; i++) {

        std::size_t linearStartIndex =
            topLeftCoordinate.toLinear(schematicDimensions);

        std::size_t readingColumns;
        std::size_t paddingColumns;

        getReadingAndPaddingColumns(topLeftCoordinate, blockSize,
                                    readingColumns, paddingColumns);

        // stream.seekg(linearStartIndex);
    }
}

void
SchematicReader::getReadingAndPaddingColumns(
    const MatrixCoordinate &topLeftCoordinate,
    std::pair<std::size_t, std::size_t> blockSize, std::size_t &readingColumns,
    std::size_t &paddingColumns) {

    std::size_t columnsToTheRightIfStartingPositionIncludingStart =
        schematicDimensions.first - topLeftCoordinate.x;

    if ((topLeftCoordinate.x + blockSize.first) >
        columnsToTheRightIfStartingPositionIncludingStart) {
        readingColumns = columnsToTheRightIfStartingPositionIncludingStart;
    }

    paddingColumns = blockSize.first - readingColumns;
}