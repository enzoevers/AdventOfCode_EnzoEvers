#include "../include/SchematicReader.hpp"

#include <stdexcept>

template <std::size_t blockWidth, std::size_t blockHeight>
SchematicReader<blockWidth, blockHeight>::SchematicReader(
    const std::string &filePath) {
    stream = new std::ifstream(filePath, std::ifstream::in);

    if (!stream.is_open()) {
        throw std::runtime_error(
            std::format("Error: failed to open filestream for {}", filePath));
    }

    assignSchematicDimensions();
}

template <std::size_t blockWidth, std::size_t blockHeight>
void
SchematicReader<blockWidth, blockHeight>::assignSchematicDimensions() {
    size_t n = 0;
    while (std::getline(stream, string)) {
        n++;
    }
}

template <std::size_t blockWidth, std::size_t blockHeight>
SchematicReader<blockWidth, blockHeight>::~SchematicReader() {
    stream.close();
}

template <std::size_t blockWidth, std::size_t blockHeight>
std::array<char, (blockWidth * blockHeight)>
SchematicReader<blockWidth, blockHeight>::getBlock(
    std::pair<std::size_t, std::size_t> topLeftCoordinate) {}

template <std::size_t blockWidth, std::size_t blockHeight>
std::size_t
SchematicReader<blockWidth, blockHeight>::coordiate2dToLinear(
    std::pair<std::size_t, std::size_t> coordinate) {
    return
}
