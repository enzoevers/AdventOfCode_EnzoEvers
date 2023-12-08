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

    uint32_t cardId = scratchCard.getCardId();
    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_EQ(cardId, 1);
    ASSERT_TRUE(winningNumbers.empty());
    ASSERT_THAT(myNumbers, testing::ElementsAreArray({2}));
}

TEST(testScratchCard_parseCardString,
     nonEmptyWinningNumberAndEmptyWinningNumbersDoesNotThrow) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 2 | ");

    uint32_t cardId = scratchCard.getCardId();
    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_EQ(cardId, 1);
    ASSERT_THAT(winningNumbers, testing::ElementsAreArray({2}));
    ASSERT_TRUE(myNumbers.empty());
}

TEST(testScratchCard_parseCardString, storesWinningAndMyNumberSorted) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 1: 2 30 4  432 3 | 3 5    6 732 2 4");

    uint32_t cardId = scratchCard.getCardId();
    std::vector<uint32_t> winningNumbers = scratchCard.getWinningNumbers();
    std::vector<uint32_t> myNumbers = scratchCard.getMyNumbers();

    ASSERT_EQ(cardId, 1);
    ASSERT_THAT(winningNumbers, testing::ElementsAreArray({2, 3, 4, 30, 432}));
    ASSERT_THAT(myNumbers, testing::ElementsAreArray({2, 3, 4, 5, 6, 732}));
}

TEST(testScratchCard_parseCardString, getCardIdCorrect) {
    ScratchCard scratchCard;

    scratchCard.parseCardString("card 0: 2 | 3");
    uint32_t cardId = scratchCard.getCardId();
    ASSERT_EQ(cardId, 0);

    scratchCard.parseCardString("card 3: 2 | 3");
    cardId = scratchCard.getCardId();
    ASSERT_EQ(cardId, 3);

    scratchCard.parseCardString("card 24: 2 | 3");
    cardId = scratchCard.getCardId();
    ASSERT_EQ(cardId, 24);

    scratchCard.parseCardString("card 1000: 2 | 3");
    cardId = scratchCard.getCardId();
    ASSERT_EQ(cardId, 1000);

    scratchCard.parseCardString("card 256: 2 | 3");
    cardId = scratchCard.getCardId();
    ASSERT_EQ(cardId, 256);
}