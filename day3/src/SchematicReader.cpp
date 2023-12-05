#include "../include/SchematicReader.hpp"

#include <stdexcept>

template <std::size_t BW, std::size_t BH>
SchematicReader<BW, BH>::SchematicReader(const std::string &filePath)
    : filePath(filePath) {
    stream = new std::ifstream(filePath, std::ifstream::in);

    if (!stream.is_open()) {
        throw std::runtime_error("Error: failed to open ifstream");
    }

    assignSchematicDimensions();
}

template <std::size_t BW, std::size_t BH>
void
SchematicReader<BW, BH>::assignSchematicDimensions() {
    std::string dummyString;
    if (std::getline(stream, dummyString)) {
        schematicDimensions.first = dummyString.length;
    } else {
        throw std::runtime_error("Error: expected at least one line");
    }

    // One line was already read
    size_t n = 1;
    while (std::getline(stream, dummyString)) {
        n++;
    }

    schematicDimensions.second = n;
}

template <std::size_t BW, std::size_t BH>
SchematicReader<BW, BH>::~SchematicReader() {
    stream.close();
}

template <std::size_t BW, std::size_t BH>
std::array<char, (BW * BH)>
SchematicReader<BW, BH>::getBlock(MatrixCoordinate &topLeftCoordinate) {}
