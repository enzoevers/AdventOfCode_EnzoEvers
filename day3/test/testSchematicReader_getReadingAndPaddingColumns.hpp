#include "../include/SchematicReader.hpp"
#include "./mocks/FileReaderMock.hpp"
#include "gtest/gtest.h"
#include <filesystem>

TEST(SchematicReader_getReadingAndPaddingColumns,
     keepsPaddingColumnsToZeroIfBlockWidthFits) {

    FileReaderMock fileReaderMock("tmp");
    SchematicReader reader(fileReaderMock);

    MatrixCoordinate topLeftCoordinate(0, 0) std::pair<std::size_t, std::size_t>
        blockSize(12, 12)

            std::size_t readingColumns;
    std::size_t paddingColumns;

    reader.getReadingAndPaddingColumns(topLeftCoordinate, blockSize,
                                       readingColumns, paddingColumns);
}
