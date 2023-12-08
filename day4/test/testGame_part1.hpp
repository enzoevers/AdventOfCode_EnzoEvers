#pragma once

#include "../include/Game.hpp"
#include <filesystem>
#include <gmock/gmock.h>

TEST(testGame_part1, fromExample) {
    std::string absolutePath =
        (std::filesystem::current_path() / "./test/testInput/examplePart1.txt")
            .string();

    uint32_t totalPoints = playPart1(absolutePath);

    ASSERT_EQ(totalPoints, 13);
}

TEST(testGame_part1, mainInput) {
    std::string absolutePath =
        (std::filesystem::current_path() / "input.txt").string();

    uint32_t totalPoints = playPart1(absolutePath);

    ASSERT_EQ(totalPoints, 22897);
}