#pragma once

#include "../include/SchematicReader.hpp"
#include "./mocks/FileReaderMock.hpp"
#include "gtest/gtest.h"
#include <filesystem>

using ::testing::_;

TEST(SchematicReader_getReadingAndPaddingRows,
     keepsPaddingRowsToZeroIfBlockHeightFitsOneColumnSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "1";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    std::size_t readingRows;
    std::size_t paddingRows;

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingRows, paddingRows);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingRows, blockSize.second);
    ASSERT_EQ(paddingRows, 0);
}

TEST(SchematicReader_getReadingAndPaddingRows,
     keepsPaddingRowsToZeroIfBlockHeightFitsMultipleColumnsSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    std::size_t readingRows;
    std::size_t paddingRows;

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingRows, paddingRows);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingRows, blockSize.first);
    ASSERT_EQ(paddingRows, 0);
}

TEST(SchematicReader_getReadingAndPaddingRows,
     setsPaddingIfBlockHeightDoesNotFitOneColumnSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 6);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "1";

    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    std::size_t readingRows;
    std::size_t paddingRows;

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingRows, paddingRows);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingRows, 3);
    ASSERT_EQ(paddingRows, 2);
}

TEST(SchematicReader_getReadingAndPaddingRows,
     setsPaddingIfBlockHeightDoesNotFitMultipleColumnsSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 6);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    std::size_t readingRows;
    std::size_t paddingRows;

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingRows, paddingRows);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingRows, 3);
    ASSERT_EQ(paddingRows, 2);
}

TEST(SchematicReader_getReadingAndPaddingRows,
     returnsTrueIfStartingCoordinateOnLastRow) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 8);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingColumns, paddingColumns);

    ASSERT_TRUE(ret);
    ASSERT_EQ(readingColumns, 1);
    ASSERT_EQ(paddingColumns, 4);
}

TEST(SchematicReader_getReadingAndPaddingRows,
     returnsFalseIfStartingCoordinateOutsideOfSchematic) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 32);
    std::pair<std::size_t, std::size_t> blockSize(5, 5);
    std::string rowString = "123456789";

    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(rowString),
                                 testing::Return(true)))
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

    bool ret = reader.getReadingAndPaddingRows(topLeftCoordinate, blockSize,
                                               readingColumns, paddingColumns);

    ASSERT_FALSE(ret);
}