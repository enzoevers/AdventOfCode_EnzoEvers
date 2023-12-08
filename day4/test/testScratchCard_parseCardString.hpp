#pragma once

#include "../include/ScratchCard.hpp"
#include <gmock/gmock.h>

TEST(testScratchCard_parseCardString, throwsOnEmptyString) {
    ScratchCard scratchCard;

    EXPECT_THROW(
        {
            try {
                scratchCard.parseCardString("");
            } catch (const std::length_error &e) {
                EXPECT_STREQ("Error: card cannot be empty", e.what());
                throw;
            }
        },
        std::length_error);
}

TEST(testScratchCard_parseCardString,
     emptyWinningNumberAndNonEmptyWinningNumbersDoesNotThrow) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: | 2");

    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_TRUE(winningNumbers.empty());
    ASSERT_THAT(myNumbers, testing::ElementsAreArray({2}));
}

TEST(testScratchCard_parseCardString,
     nonEmptyWinningNumberAndEmptyWinningNumbersDoesNotThrow) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 2 | ");

    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_THAT(winningNumbers, testing::ElementsAreArray({2}));
    ASSERT_TRUE(myNumbers.empty());
}

TEST(testScratchCard_parseCardString, storesWinningAndMyNumberSorted) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 2 30 4  432 3 | 3 5    6 732 2 4");

    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_THAT(winningNumbers, testing::ElementsAreArray({2, 3, 4, 30, 432}));
    ASSERT_THAT(myNumbers, testing::ElementsAreArray({2, 3, 4, 5, 6, 732}));
}