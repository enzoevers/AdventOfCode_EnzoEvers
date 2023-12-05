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

bool
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
    bool success = getReadingAndPaddingColumns(topLeftCoordinate, blockSize,
                                               readingColumns, paddingColumns);

    if (!success) {
        return false;
    }

    std::size_t readingRows;
    std::size_t paddingRows;
    success = getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                       readingRows, paddingRows);

    if (!success) {
        return false;
    }

    std::string rowEndPadding(paddingColumns, '.');

    auto tmpSchematicDimensions = schematicDimensions;
    // The +1 is to take into account the new line character
    tmpSchematicDimensions.first++;

    auto tmpCoordinate = topLeftCoordinate;

    std::size_t r = 0;
    for (; r < readingRows; r++) {

        std::size_t startIndex = tmpCoordinate.toLinear(tmpSchematicDimensions);
        tmpCoordinate.y++;

        std::string dstString;

        fileReader.readPartOfFile(startIndex, readingColumns, dstString);

        std::copy(dstString.begin(), dstString.end(),
                  std::back_inserter(block));

        std::copy(rowEndPadding.begin(), rowEndPadding.end(),
                  std::back_inserter(block));
    }

    if (paddingRows > 0) {
        std::string completeRowPadding(paddingRows * blockSize.first, '.');

        std::copy(completeRowPadding.begin(), completeRowPadding.end(),
                  std::back_inserter(block));
    }

    return true;
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

    // A -1 because the starting point also counts
    if ((topLeftCoordinate.x + blockSize.first - 1) >
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

    // A -1 because the starting point also counts
    if ((topLeftCoordinate.y + blockSize.second - 1) >
        rowsToTheBottomOfStartingPositionIncludingStart) {
        readingRows = rowsToTheBottomOfStartingPositionIncludingStart;
    } else {
        readingRows = blockSize.second;
    }

    paddingRows = blockSize.second - readingRows;

    return true;
}