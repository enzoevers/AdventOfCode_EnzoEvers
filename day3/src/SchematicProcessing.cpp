#pragma once

#include "../include/SchematicProcessing.hpp"
#include <map>

int
SchematicProcessing::processSchematic(I2DFileReader &fileReader2d) {
    std::map<MatrixCoordinate, bool> blacklistedCoordinated;

    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::pair<std::size_t, std::size_t> schematicSize =
        fileReader2d.getFileDimensionsNoNewlines();

    std::size_t horizontalBlockCount = (schematicSize.first / blockSize.first);
    if (horizontalBlockCount * blockSize.first != schematicSize.first) {
        horizontalBlockCount++;
    }

    std::size_t verticalBlockCount = (schematicSize.second / blockSize.second);
    if (verticalBlockCount * blockSize.second != schematicSize.second) {
        verticalBlockCount++;
    }

    for (std::size_t h = 0; h < horizontalBlockCount; h++) {
        for (std::size_t v = 0; v < verticalBlockCount; v++) {
        }
    }
}
