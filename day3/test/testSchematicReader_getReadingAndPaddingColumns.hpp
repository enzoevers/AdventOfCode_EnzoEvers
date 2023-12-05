#include "../include/SchematicReader.hpp"
#include "./mocks/FileReaderMock.hpp"
#include "gtest/gtest.h"
#include <filesystem>

using ::testing::_;

TEST(SchematicReader_getReadingAndPaddingColumns,
     keepsPaddingColumnsToZeroIfBlockWidthFitsOneLineSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getNextLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    std::size_t readingColumns;
    std::size_t paddingColumns;

    bool ret = reader.getReadingAndPaddingColumns(
        topLeftCoordinate, blockSize, readingColumns, paddingColumns);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingColumns, blockSize.first);
    ASSERT_EQ(paddingColumns, 0);
}

TEST(SchematicReader_getReadingAndPaddingColumns,
     keepsPaddingColumnsToZeroIfBlockWidthFitsMultipleLinesSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getNextLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    std::size_t readingColumns;
    std::size_t paddingColumns;

    bool ret = reader.getReadingAndPaddingColumns(
        topLeftCoordinate, blockSize, readingColumns, paddingColumns);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingColumns, blockSize.first);
    ASSERT_EQ(paddingColumns, 0);
}

TEST(SchematicReader_getReadingAndPaddingColumns,
     setsPaddingIfBlockWidthDoesNotFitOneLineSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(6, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getNextLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    std::size_t readingColumns;
    std::size_t paddingColumns;

    bool ret = reader.getReadingAndPaddingColumns(
        topLeftCoordinate, blockSize, readingColumns, paddingColumns);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingColumns, 3);
    ASSERT_EQ(paddingColumns, 2);
}

TEST(SchematicReader_getReadingAndPaddingColumns,
     setsPaddingIfBlockWidthDoesNotFitMultipleLinesSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(6, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getNextLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    std::size_t readingColumns;
    std::size_t paddingColumns;

    bool ret = reader.getReadingAndPaddingColumns(
        topLeftCoordinate, blockSize, readingColumns, paddingColumns);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingColumns, 3);
    ASSERT_EQ(paddingColumns, 2);
}

TEST(SchematicReader_getReadingAndPaddingColumns,
     returnsFalseIfStartingCoordinateOutsideOfSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(10, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getNextLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    std::size_t readingColumns;
    std::size_t paddingColumns;

    bool ret = reader.getReadingAndPaddingColumns(
        topLeftCoordinate, blockSize, readingColumns, paddingColumns);

    ASSERT_FALSE(ret);
}