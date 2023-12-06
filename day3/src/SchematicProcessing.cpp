#include "../include/SchematicProcessing.hpp"
#include "../include/TextToInt.hpp"
#include <iostream>
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
    for (std::size_t i = 0; i < vec.size(); i++) {
        vec.at(i) = false;
    }
}

void
printBuffer(std::array<std::string, 3> &buffer) {
    std::cout << "printBuffer" << std::endl;
    for (auto s : buffer) {
        std::cout << s << std::endl;
    }
}

void
printBlacklist(std::array<std::vector<bool>, 3> &blacklistBuffer) {
    std::cout << "printBlacklist" << std::endl;
    for (auto v : blacklistBuffer) {
        for (auto b : v) {
            std::cout << b;
        }
        std::cout << std::endl;
    }
}

int
SchematicProcessing::processSchematic(
    std::function<int(const std::array<std::string, 3> &buffer,
                      std::array<std::vector<bool>, 3> &blacklistBuffer,
                      std::size_t currentLineIndex, std::size_t symbolIndex)>
        symbolBlockProcessor) {

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

            std::size_t curCharIndex = c + 1;
            char curChar = buffer.at(currentLineOfInterest).at(curCharIndex);

            if (curChar != ignoreCharacter &&
                TextToInt::charToInt(curChar) == -1) {
                runningSum +=
                    symbolBlockProcessor(buffer, blacklistBuffer,
                                         currentLineOfInterest, curCharIndex);
            }
        }

        // Replace the oldest line with a new one
        std::size_t lineIndexAbove = indexAboveCurrent(currentLineOfInterest);

        if (r < schematicDimensions.second - 2) {
            lockedFileReader->getLine(buffer.at(lineIndexAbove));
            buffer.at(lineIndexAbove) =
                ignoreCharacter + buffer.at(lineIndexAbove) + ignoreCharacter;
        } else {
            buffer.at(lineIndexAbove) = paddingRow;
        }

        setVectorToAllFalse(blacklistBuffer.at(lineIndexAbove));

        currentLineOfInterest = indexBelowCurrent(currentLineOfInterest);
    }

    return runningSum;
}

int
SchematicProcessing::processNumbersAroundSymbol(
    const std::array<std::string, 3> &buffer,
    std::array<std::vector<bool>, 3> &blacklistBuffer,
    std::size_t currentLineIndex, std::size_t symbolIndex) {

    int localSum = 0;

    // Note that this isn't the most optimal with regard to caching
    // since the last read line is always the currentLineIndex while
    // this loop simply starts at line 0.
    //
    // Also, the symbol character is checked twice over the whole process.
    // Once in this loop and once before this function
    // (processNumbersAroundSymbol) is called.
    const std::size_t windowWidth = 3;
    const std::size_t windowHeight = 3;
    for (std::size_t i = 0; i < windowWidth * windowHeight; i++) {
        std::size_t r = i / windowWidth;
        std::size_t c = i % windowWidth;

        std::size_t curColumn = symbolIndex + c - 1;

        if (!blacklistBuffer.at(r).at(curColumn) &&
            TextToInt::charToInt(buffer.at(r).at(curColumn)) != -1) {

            int num = findCompleteNumber(buffer.at(r), blacklistBuffer.at(r),
                                         curColumn);
            localSum += num;
        }
    }

    return localSum;
}

int
SchematicProcessing::processPotentialGearRatio(
    const std::array<std::string, 3> &buffer,
    std::array<std::vector<bool>, 3> &blacklistBuffer,
    std::size_t currentLineIndex, std::size_t symbolIndex) {
    int gearRatio = 0;

    if (buffer.at(currentLineIndex).at(symbolIndex) != '*') {
        return 0;
    }

    std::array<int, 2> gearRatioMembers;
    std::size_t ratioMemberCount = 0;

    const std::size_t windowWidth = 3;
    const std::size_t windowHeight = 3;
    for (std::size_t i = 0; i < windowWidth * windowHeight; i++) {
        std::size_t r = i / windowWidth;
        std::size_t c = i % windowWidth;

        std::size_t curColumn = symbolIndex + c - 1;

        if (!blacklistBuffer.at(r).at(curColumn) &&
            TextToInt::charToInt(buffer.at(r).at(curColumn)) != -1) {

            if (ratioMemberCount == 2) {
                // Found a third value. This is not a gear of interest
                // Increment ratioMemberCount to indicate that more than
                // two numbers are found.
                ratioMemberCount++;
                break;
            }

            int num = findCompleteNumber(buffer.at(r), blacklistBuffer.at(r),
                                         curColumn);

            gearRatioMembers.at(ratioMemberCount++) = num;
        }
    }

    if (ratioMemberCount == 2) {
        gearRatio = gearRatioMembers.at(0) * gearRatioMembers.at(1);
    }

    return gearRatio;
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
        curColumn--;
        readNumber = TextToInt::charToInt(line.at(curColumn));
    }

    return totalNumber;
}