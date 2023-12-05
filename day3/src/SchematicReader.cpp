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
        if (dummyString.length() != schematicDimensions.first) {
            throw std::length_error("Error: not all lines are the same length");
        }
        n++;
    }

    schematicDimensions.second = n;

    fileReader.goToLine(0);
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

    std::size_t readingColumns;
    std::size_t paddingColumns;

    getReadingAndPaddingColumns(topLeftCoordinate, blockSize, readingColumns,
                                paddingColumns);

    std::size_t readingRows;
    std::size_t paddingRows;

    getReadingAndPaddingRows(topLeftCoordinate, blockSize, readingRows,
                             paddingRows);
}

bool
SchematicReader::getReadingAndPaddingColumns(
    const MatrixCoordinate &topLeftCoordinate,
    std::pair<std::size_t, std::size_t> blockSize, std::size_t &readingColumns,
    std::size_t &paddingColumns) {

    if (topLeftCoordinate.x >= schematicDimensions.first) {
        return false;
    }

    std::size_t columnsToTheRightOfStartingPositionIncludingStart =
        schematicDimensions.first - topLeftCoordinate.x;

    if ((topLeftCoordinate.x + blockSize.first) >
        columnsToTheRightOfStartingPositionIncludingStart) {
        readingColumns = columnsToTheRightOfStartingPositionIncludingStart;
    } else {
        readingColumns = blockSize.first;
    }

    paddingColumns = blockSize.first - readingColumns;

    return true;
}

bool
SchematicReader::getReadingAndPaddingRows(
    const MatrixCoordinate &topLeftCoordinate,
    std::pair<std::size_t, std::size_t> blockSize, std::size_t &readingRows,
    std::size_t &paddingRows) {

    if (topLeftCoordinate.y >= schematicDimensions.second) {
        return false;
    }

    std::size_t rowsToTheBottomOfStartingPositionIncludingStart =
        schematicDimensions.second - topLeftCoordinate.y;

    if ((topLeftCoordinate.y + blockSize.second) >
        rowsToTheBottomOfStartingPositionIncludingStart) {
        readingRows = rowsToTheBottomOfStartingPositionIncludingStart;
    } else {
        readingRows = blockSize.second;
    }

    paddingRows = blockSize.second - readingRows;

    return true;
}