#include "../include/IFileReader.hpp"
#include <gmock/gmock.h>

class FileReaderMock : public IFileReader {
  public:
    MOCK_METHOD(bool, getNextLine, (std::string & dst), (override));

    MOCK_METHOD(void, goToLine, (std::size_t lineNumber), (override));

    MOCK_METHOD(void, readPartOfFile,
                (std::size_t startIndex, std::size_t count, std::string &dst),
                (override));
    MOCK_METHOD(void, readPartOfFile,
                (std::size_t column, std::size_t row, std::size_t count,
                 std::string &dst),
                (override));
};