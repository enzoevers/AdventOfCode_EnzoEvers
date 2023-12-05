#include "../include/FileReader.hpp"

FileReader::FileReader(const std::string &newfilePath) : filePath(newfilePath) {
    stream.open(filePath, std::ifstream::in);

    if (!stream.is_open()) {
        throw std::runtime_error("Error: failed to open ifstream");
    }
}
FileReader::~FileReader() { stream.close(); }

bool
FileReader::getNextLine(std::string &dst) {
    return static_cast<bool>(std::getline(stream, dst));
}

void
FileReader::goToLine(std::size_t lineNumber) {}

void
FileReader::readPartOfFile(std::size_t startIndex, std::size_t count,
                           std::string &dst) {}
void
FileReader::readPartOfFile(std::size_t column, std::size_t row,
                           std::size_t count, std::string &dst) {}