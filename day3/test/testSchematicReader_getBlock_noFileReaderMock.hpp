#pragma once

#include "../include/FileReader.hpp"
#include "../include/SchematicReader.hpp"
#include "gtest/gtest.h"
#include <filesystem>

using ::testing::_;

TEST(SchematicReader_getBlock_noFileReaderMock,
     getSquareBlockStartingAtZeroZero) {
    MatrixCoordinate topLeftCoordinate(0, 0);

    std::pair<std::size_t, std::size_t> blockSize(3, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic1.txt")
                                   .string();

    FileReader fileReader(absolutePath);
    SchematicReader reader(fileReader);

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '.', '.', '.', '2', '.',
                                            '.', '.'));
}

TEST(SchematicReader_getBlock_noFileReaderMock,
     getNoneSquareBlockStartingAtZeroZero) {
    MatrixCoordinate topLeftCoordinate(0, 0);

    std::pair<std::size_t, std::size_t> blockSize(4, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic1.txt")
                                   .string();

    FileReader fileReader(absolutePath);
    SchematicReader reader(fileReader);

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '.', '#', '.', '.', '2',
                                            '.', '.', '.', '.', '.'));
}

TEST(SchematicReader_getBlock_noFileReaderMock,
     getSquareBlockStartingAtNonZeroZeroInsideFile) {
    MatrixCoordinate topLeftCoordinate(3, 2);

    std::pair<std::size_t, std::size_t> blockSize(3, 3);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic1.txt")
                                   .string();

    FileReader fileReader(absolutePath);
    SchematicReader reader(fileReader);

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block, testing::ElementsAre('.', '.', '$', '.', '.', '3', '.',
                                            '.', '2'));
}

TEST(SchematicReader_getBlock_noFileReaderMock,
     getSquareBlockStartingAtNonZeroZeroPartlyOutsideFile) {

    MatrixCoordinate topLeftCoordinate(5, 3);

    std::pair<std::size_t, std::size_t> blockSize(4, 4);
    std::vector<char> block;
    block.reserve(blockSize.first * blockSize.second);

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic1.txt")
                                   .string();

    FileReader fileReader(absolutePath);
    SchematicReader reader(fileReader);

    bool ret = reader.getBlock(topLeftCoordinate, block, blockSize);

    ASSERT_TRUE(ret);
    ASSERT_EQ(block.size(), blockSize.first * blockSize.second);
    ASSERT_THAT(block,
                testing::ElementsAre('3', '.', '.', '.', '2', '.', '.', '.',
                                     '.', '.', '.', '.', '.', '.', '.', '.'));
}