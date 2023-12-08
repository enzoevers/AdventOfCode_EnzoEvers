#pragma once

#include "../include/ScratchCard.hpp"
#include <gmock/gmock.h>

TEST(testScratchCard_parseCardString,
     correctIfNoPointsLessWinningNumberThanMyNumbers) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 1 10 | 2 30 4  432 3");
    auto countAndPoints = scratchCard.getPoints();

    ASSERT_EQ(countAndPoints.first, 0);
    ASSERT_EQ(countAndPoints.second, 0);
}

TEST(testScratchCard_parseCardString,
     correctIfNoPointsMoreWinningNumberThanMyNumbers) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 2 30 4  432 3 | 1 10");
    auto countAndPoints = scratchCard.getPoints();

    ASSERT_EQ(countAndPoints.first, 0);
    ASSERT_EQ(countAndPoints.second, 0);
}

TEST(testScratchCard_parseCardString, correctIfMoreWinningNumberThanMyNumbers) {
    ScratchCard scratchCard;

    scratchCard.parseCardString(
        "card 1: 1 30 3 100 5 432 5 2  90   6 99 | 2 30 4 ");
    auto countAndPoints = scratchCard.getPoints();

    ASSERT_EQ(countAndPoints.first, 2);
    ASSERT_EQ(countAndPoints.second, 2);   // 2^(2-1) = 2
}

TEST(testScratchCard_parseCardString, correctIfLessWinningNumberThanMyNumbers) {
    ScratchCard scratchCard;

    scratchCard.parseCardString(
        "card 1: 1 30 3 100 5 | 2 30 4  432 5 3 1 32 100");
    auto countAndPoints = scratchCard.getPoints();

    ASSERT_EQ(countAndPoints.first, 5);
    ASSERT_EQ(countAndPoints.second, 16);   // 2^(5-1) = 16
}