#pragma once

#include "../include/FileReader.hpp"
#include "gtest/gtest.h"
#include <filesystem>

TEST(FileReader_readPartOfFile, readsPartOfFirstRowStartingFromTheBeginning) {

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic0.txt")
                                   .string();

    FileReader fileReader(absolutePath);

    std::string readPart;
    fileReader.readPartOfFile(0, 4, readPart);

    ASSERT_EQ(readPart, "...#");
}

TEST(FileReader_readPartOfFile, readsPartOfFirstRowStartingFromDifferentStart) {

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic0.txt")
                                   .string();

    FileReader fileReader(absolutePath);

    std::string readPart;
    fileReader.readPartOfFile(2, 4, readPart);

    ASSERT_EQ(readPart, ".#.1");
}

TEST(FileReader_readPartOfFile, readingWrapsAroundLines) {

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic0.txt")
                                   .string();

    FileReader fileReader(absolutePath);

    std::string readPart;
    fileReader.readPartOfFile(6, 7, readPart);

    ASSERT_EQ(readPart, "23\n..2.");
}

TEST(FileReader_readPartOfFile, readingFromSecondLine) {

    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic0.txt")
                                   .string();

    FileReader fileReader(absolutePath);

    std::string readPart;
    fileReader.readPartOfFile(9, 3, readPart);

    ASSERT_EQ(readPart, "..2");
}