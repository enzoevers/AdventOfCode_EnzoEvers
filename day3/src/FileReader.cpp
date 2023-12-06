#include "../include/FileReader.hpp"
#include <iostream>
#include <vector>

FileReader::FileReader(const std::string &newfilePath) : filePath(newfilePath) {
    stream.open(filePath, std::ifstream::in);

    if (!stream.is_open()) {
        throw std::runtime_error("Error: failed to open ifstream");
    }
}
FileReader::~FileReader() { stream.close(); }

std::size_t
FileReader::getLineCount() {
    size_t n = 0;
    std::string dummyString;
    while (std::getline(stream, dummyString)) {
        n++;
    }

    // Go Back to the beginning
    stream.clear();
    stream.seekg(0, stream.beg);

    return n;
}

bool
FileReader::getLine(std::string &dst) {
    if (stream.eof()) {
        return false;
    }

    std::getline(stream, dst);
    return true;
}

void
FileReader::goToLine(std::size_t lineNumber) {
    stream.clear();
    stream.seekg(0, stream.beg);

    std::string dummyString;
    for (std::size_t i; i < lineNumber && getLine(dummyString); i++) {
    }
}

void
FileReader::readPartOfFile(std::size_t startIndex, std::size_t count,
                           std::string &dst) {

    // TODO: Some more constraint checks

    stream.clear();
    stream.seekg(startIndex, stream.beg);

    std::vector<char> tmpArray(count);

    stream.read(tmpArray.data(), count);

    dst = std::string(tmpArray.begin(), tmpArray.end());
}
void
FileReader::readPartOfFile(std::size_t column, std::size_t row,
                           std::size_t count, std::string &dst) {}