#pragma once

#include "./IFileReader.hpp"
#include <fstream>

class FileReader : public IFileReader {
  private:
    const std::string filePath;
    std::ifstream stream;

  public:
    FileReader(const std::string &newfilePath);
    ~FileReader();

    std::size_t getLineCount() override;

    bool getNextLine(std::string &dst) override;

    void goToLine(std::size_t lineNumber) override;

    void readPartOfFile(std::size_t startIndex, std::size_t count,
                        std::string &dst) override;
    void readPartOfFile(std::size_t column, std::size_t row, std::size_t count,
                        std::string &dst) override;
};