#pragma once

#include "../include/Game.hpp"
#include <filesystem>
#include <gmock/gmock.h>

TEST(testGame_part2, fromExample) {
    std::string absolutePath =
        (std::filesystem::current_path() / "./test/testInput/examplePart2.txt")
            .string();

    uint32_t totalCards = playPart2(absolutePath);

    ASSERT_EQ(totalCards, 30);
}