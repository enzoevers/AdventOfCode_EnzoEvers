#pragma once

#include <string>

class IFileReader {
  public:
    virtual ~IFileReader(){};

    virtual bool getNextLine(std::string &dst) = 0;

    virtual void goToLine(std::size_t lineNumber) = 0;

    virtual void readPartOfFile(std::size_t startIndex, std::size_t count,
                                std::string &dst) = 0;
    virtual void readPartOfFile(std::size_t column, std::size_t row,
                                std::size_t count, std::string &dst) = 0;
};