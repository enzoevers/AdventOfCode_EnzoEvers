#pragma once

#include "../../include/IFileReader.hpp"
#include "gmock/gmock.h"

class FileReaderMock : public IFileReader {
  public:
    FileReaderMock(const std::string &newfilePath) {}

    MOCK_METHOD(std::size_t, getLineCount, (), (override));

    MOCK_METHOD(bool, getLine, (std::string & dst), (override));

    MOCK_METHOD(void, goToLine, (std::size_t lineNumber), (override));

    MOCK_METHOD(void, readPartOfFile,
                (std::size_t startIndex, std::size_t count, std::string &dst),
                (override));
    MOCK_METHOD(void, readPartOfFile,
                (std::size_t column, std::size_t row, std::size_t count,
                 std::string &dst),
                (override));
};