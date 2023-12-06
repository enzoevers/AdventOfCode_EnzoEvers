#pragma once

#include "./IFileReader.hpp"
#include <memory>
#include <vector>

class SchematicProcessing {
  private:
    std::weak_ptr<IFileReader> fileReader;
    const char ignoreCharacter;

    int runningSum;

    /*
     * first: width
     * second: height
     */
    std::pair<std::size_t, std::size_t> schematicDimensions;

    /*
     * It is assumed that the schematic is a rectangle. Meaning that
     * it is assumed that all lines have the same width.
     */
    void assignSchematicDimensions();

    std::size_t indexBelowCurrent(std::size_t currentIndex);
    std::size_t indexAboveCurrent(std::size_t currentIndex);
    void setVectorToAllFalse(std::vector<bool> &vec);

  public:
    SchematicProcessing(std::shared_ptr<IFileReader> fileReader,
                        const char ignoreCharacter);

    int processSchematic();

    void processNumbersAroundSymbol(
        const std::array<std::string, 3> &buffer,
        std::array<std::vector<bool>, 3> &blacklistBuffer,
        std::size_t currentLineIndex, std::size_t symbolIndex);

    int findCompleteNumber(const std::string &buffer,
                           std::vector<bool> &blacklistBuffer,
                           std::size_t column);
};