#pragma once

#include "../include/FileReader.hpp"
#include "../include/SchematicReader.hpp"
#include "gtest/gtest.h"
#include <filesystem>

TEST(SchematicReader_constructor, sizeIsSetCorrectlyForTestSchematic0) {
    std::string absolutePath = (std::filesystem::current_path() /
                                "./test/testSchematics/schematic0.txt")
                                   .string();

    FileReader fileReader(absolutePath);
    SchematicReader reader(fileReader);

    auto schematicDimensions = reader.getSchematicDimensions();
    ASSERT_EQ(schematicDimensions.first, 8);
    ASSERT_EQ(schematicDimensions.second, 3);
}