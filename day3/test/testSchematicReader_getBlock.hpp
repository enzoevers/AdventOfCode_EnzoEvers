#pragma once

#include "../include/SchematicReader.hpp"
#include "./mocks/FileReaderMock.hpp"
#include "gtest/gtest.h"
#include <filesystem>

using ::testing::_;

TEST(SchematicReader_getBlock, getSquareBlockStartingAtZeroZero) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);

    std::pair<std::size_t, std::size_t> blockSize(3, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string row0 = "...#.123";
    std::string row1 = "..2.....";
    std::string row2 = ".....$1.";
    std::string row3 = ".2...3..";
    std::string row4 = "..%..2..";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row0),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row1),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row2),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row3),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row4),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    EXPECT_CALL(fileReaderMock, readPartOfFile(0, 3, _))
        .WillOnce(testing::SetArgReferee<2>("..."));
    EXPECT_CALL(fileReaderMock, readPartOfFile(9, 3, _))
        .WillOnce(testing::SetArgReferee<2>("..2"));
    EXPECT_CALL(fileReaderMock, readPartOfFile(18, 3, _))
        .WillOnce(testing::SetArgReferee<2>("..."));

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '.', '.', '.', '2', '.',
                                            '.', '.'));
}

TEST(SchematicReader_getBlock, getNoneSquareBlockStartingAtZeroZero) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(0, 0);

    std::pair<std::size_t, std::size_t> blockSize(4, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string row0 = "...#.123";
    std::string row1 = "..2.....";
    std::string row2 = ".....$1.";
    std::string row3 = ".2...3..";
    std::string row4 = "..%..2..";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row0),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row1),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row2),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row3),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row4),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    EXPECT_CALL(fileReaderMock, readPartOfFile(0, 4, _))
        .WillOnce(testing::SetArgReferee<2>("...#"));
    EXPECT_CALL(fileReaderMock, readPartOfFile(9, 4, _))
        .WillOnce(testing::SetArgReferee<2>("..2."));
    EXPECT_CALL(fileReaderMock, readPartOfFile(18, 4, _))
        .WillOnce(testing::SetArgReferee<2>("...."));

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '.', '#', '.', '.', '2',
                                            '.', '.', '.', '.', '.'));
}

TEST(SchematicReader_getBlock, getSquareBlockStartingAtNonZeroZeroInsideFile) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(3, 2);

    std::pair<std::size_t, std::size_t> blockSize(3, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string row0 = "...#.123";
    std::string row1 = "..2.....";
    std::string row2 = ".....$1.";
    std::string row3 = ".2...3..";
    std::string row4 = "..%..2..";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row0),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row1),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row2),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row3),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row4),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    // Note that the width of the row in the file is 9 rather than 8 due to the
    // \n character
    std::pair<std::size_t, std::size_t> schematicSize(9, 5);

    EXPECT_CALL(fileReaderMock,
                readPartOfFile(topLeftCoordinate.toLinear(schematicSize), 3, _))
        .WillOnce(testing::SetArgReferee<2>("..$"));

    EXPECT_CALL(fileReaderMock,
                readPartOfFile(MatrixCoordinate(topLeftCoordinate.x,
                                                topLeftCoordinate.y + 1)
                                   .toLinear(schematicSize),
                               3, _))
        .WillOnce(testing::SetArgReferee<2>("..3"));

    EXPECT_CALL(fileReaderMock,
                readPartOfFile(MatrixCoordinate(topLeftCoordinate.x,
                                                topLeftCoordinate.y + 2)
                                   .toLinear(schematicSize),
                               3, _))
        .WillOnce(testing::SetArgReferee<2>("..2"));

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '$', '.', '.', '3', '.',
                                            '.', '2'));
}

TEST(SchematicReader_getBlock,
     getSquareBlockStartingAtNonZeroZeroPartlyOutsideFile) {

    FileReaderMock fileReaderMock("tmp");

    MatrixCoordinate topLeftCoordinate(5, 3);

    std::pair<std::size_t, std::size_t> blockSize(4, 4);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string row0 = "...#.123";
    std::string row1 = "..2.....";
    std::string row2 = ".....$1.";
    std::string row3 = ".2...3..";
    std::string row4 = "..%..2..";

    // Mock a schematic of 1 line.
    EXPECT_CALL(fileReaderMock, getLine(_))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row0),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row1),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row2),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row3),
                                 testing::Return(true)))
        .WillOnce(testing::DoAll(testing::SetArgReferee<0>(row4),
                                 testing::Return(true)))
        .WillRepeatedly(testing::Return(false));

    EXPECT_CALL(fileReaderMock, goToLine(0));

    SchematicReader reader(fileReaderMock);

    // Note that the width of the row in the file is 9 rather than 8 due to the
    // \n character
    std::pair<std::size_t, std::size_t> schematicSize(9, 5);

    // Arg two of the calls is 3 and not 4 because only three columns are read.
    // The rest is padding
    EXPECT_CALL(fileReaderMock,
                readPartOfFile(topLeftCoordinate.toLinear(schematicSize), 3, _))
        .WillOnce(testing::SetArgReferee<2>("3.."));

    EXPECT_CALL(fileReaderMock,
                readPartOfFile(MatrixCoordinate(topLeftCoordinate.x,
                                                topLeftCoordinate.y + 1)
                                   .toLinear(schematicSize),
                               3, _))
        .WillOnce(testing::SetArgReferee<2>("2.."));

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block,
                testing::ElementsAre('3', '.', '.', '.', '2', '.', '.', '.',
                                     '.', '.', '.', '.', '.', '.', '.', '.'));
}