#include "../include/SchematicProcessing.hpp"
#include "../include/TextToInt.hpp"
#include <map>
#include <stdexcept>

SchematicProcessing::SchematicProcessing(
    std::shared_ptr<IFileReader> fileReader, const char ignoreCharacter)
    : fileReader(fileReader), ignoreCharacter(ignoreCharacter) {
    runningSum = 0;
    assignSchematicDimensions();
}

void
SchematicProcessing::assignSchematicDimensions() {
    auto lockedFileReader = fileReader.lock();
    if (!lockedFileReader) {
        throw std::runtime_error("Error: weak pointer was deleted");
    }

    std::string dummyString;
    if (lockedFileReader->getLine(dummyString)) {
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
    while (lockedFileReader->getLine(dummyString)) {
        if (dummyString.length() != schematicDimensions.first) {
            throw std::length_error("Error: not all lines are the same length");
        }
        n++;
    }

    schematicDimensions.second = n;

    lockedFileReader->goToLine(0);
}

std::size_t
SchematicProcessing::indexBelowCurrent(std::size_t currentIndex) {
    std::size_t index;

    if (currentIndex == 2) {
        index = 0;
    } else {
        index = currentIndex + 1;
    }

    return index;
}
std::size_t
SchematicProcessing::indexAboveCurrent(std::size_t currentIndex) {
    std::size_t index;

    if (currentIndex == 0) {
        index = 2;
    } else {
        index = currentIndex - 1;
    }

    return index;
}

void
SchematicProcessing::setVectorToAllFalse(std::vector<bool> &vec) {
    for (std::size_t i; i < vec.size(); i++) {
        vec.at(i) = false;
    }
}

int
SchematicProcessing::processSchematic() {
    runningSum = 0;

    auto lockedFileReader = fileReader.lock();
    if (!lockedFileReader) {
        throw std::runtime_error("Error: weak pointer was deleted");
    }

    const std::size_t paddedRowSize = schematicDimensions.first + 2;
    std::string paddingRow(paddedRowSize, ignoreCharacter);

    std::array<std::string, 3> buffer;
    std::array<std::vector<bool>, 3> blacklistBuffer;

    for (auto &b : blacklistBuffer) {
        for (std::size_t i = 0; i < paddedRowSize; i++) {
            b.push_back(false);
        }
    }

    // Fill initial buffer
    lockedFileReader->goToLine(0);

    buffer.at(0) = paddingRow;

    lockedFileReader->getLine(buffer.at(1));
    buffer.at(1) = ignoreCharacter + buffer.at(1) + ignoreCharacter;

    lockedFileReader->getLine(buffer.at(2));
    buffer.at(2) = ignoreCharacter + buffer.at(2) + ignoreCharacter;

    std::size_t currentLineOfInterest = 1;

    for (std::size_t r = 0; r < schematicDimensions.second; r++) {
        for (std::size_t c = 0; c < schematicDimensions.first; c++) {
            char curChar = buffer.at(currentLineOfInterest).at(1 + c);

            if (curChar != ignoreCharacter &&
                TextToInt::charToInt(curChar) == -1) {
                processNumbersAroundSymbol(buffer, blacklistBuffer,
                                           currentLineOfInterest, c);
            }
        }

        // Replace the oldest line with a new one
        std::size_t lineIndexAbove = indexAboveCurrent(currentLineOfInterest);
        lockedFileReader->getLine(buffer.at(lineIndexAbove));
        buffer.at(lineIndexAbove) =
            ignoreCharacter + buffer.at(lineIndexAbove) + ignoreCharacter;

        setVectorToAllFalse(blacklistBuffer.at(lineIndexAbove));

        currentLineOfInterest = indexBelowCurrent(currentLineOfInterest);
    }

    return runningSum;
}

void
SchematicProcessing::processNumbersAroundSymbol(
    const std::array<std::string, 3> &buffer,
    std::array<std::vector<bool>, 3> &blacklistBuffer,
    std::size_t currentLineIndex, std::size_t symbolIndex) {
    // Process current line
    if (!blacklistBuffer.at(currentLineIndex).at(symbolIndex - 1) &&
        TextToInt::charToInt(buffer.at(currentLineIndex).at(symbolIndex - 1)) !=
            -1) {
        int num = findCompleteNumber(buffer.at(currentLineIndex),
                                     blacklistBuffer.at(currentLineIndex),
                                     symbolIndex + 1);
        runningSum += num;
    }
    if (!blacklistBuffer.at(currentLineIndex).at(symbolIndex + 1) &&
        TextToInt::charToInt(buffer.at(currentLineIndex).at(symbolIndex + 1)) !=
            -1) {
        int num = findCompleteNumber(buffer.at(currentLineIndex),
                                     blacklistBuffer.at(currentLineIndex),
                                     symbolIndex + 1);
        runningSum += num;
    }

    // Process line above
    std::size_t curLine = indexAboveCurrent(currentLineIndex);
    for (std::size_t i = 0; i < 3; i++) {
        std::size_t curColumn = symbolIndex + i - 1;
        if (!blacklistBuffer.at(curLine).at(curColumn) &&
            TextToInt::charToInt(buffer.at(curLine).at(curColumn)) != -1) {
            int num = findCompleteNumber(
                buffer.at(curLine), blacklistBuffer.at(curLine), curColumn);
            runningSum += num;
        }
    }

    // Process line below
    curLine = indexBelowCurrent(currentLineIndex);
    for (std::size_t i = 0; i < 3; i++) {
        std::size_t curColumn = symbolIndex + i - 1;
        if (!blacklistBuffer.at(curLine).at(curColumn) &&
            TextToInt::charToInt(buffer.at(curLine).at(curColumn)) != -1) {
            int num = findCompleteNumber(
                buffer.at(curLine), blacklistBuffer.at(curLine), curColumn);
            runningSum += num;
        }
    }
}

int
SchematicProcessing::findCompleteNumber(const std::string &line,
                                        std::vector<bool> &blacklistBuffer,
                                        std::size_t column) {
    int totalNumber = 0;

    // It is already assumed that column is a number
    std::size_t curColumn = column;
    while (TextToInt::charToInt(line.at(curColumn + 1)) != -1) {
        // If the next column it a number, increase the current column
        curColumn++;
    }

    int scalingFactor = 1;
    int readNumber = TextToInt::charToInt(line.at(curColumn));

    while (readNumber != -1) {
        totalNumber += readNumber * scalingFactor;
        scalingFactor *= 10;

        blacklistBuffer.at(curColumn) = true;
        curColumn++;
        readNumber = TextToInt::charToInt(line.at(curColumn));
    }

    return totalNumber;
}