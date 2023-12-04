#include "gtest/gtest.h"
#include "../src/challenge.hpp"

TEST(charToInt, belowAscii0){
    int value = charToInt('(');
    ASSERT_EQ(value, -1);
}

TEST(charToInt, inRange){
    ASSERT_EQ(charToInt('0'), 0);
    ASSERT_EQ(charToInt('1'), 1);
    ASSERT_EQ(charToInt('2'), 2);
    ASSERT_EQ(charToInt('3'), 3);
    ASSERT_EQ(charToInt('4'), 4);
    ASSERT_EQ(charToInt('5'), 5);
    ASSERT_EQ(charToInt('6'), 6);
    ASSERT_EQ(charToInt('7'), 7);
    ASSERT_EQ(charToInt('8'), 8);
    ASSERT_EQ(charToInt('9'), 9);
}

TEST(charToInt, aboveAscii9){
    int value = charToInt('a');
    ASSERT_EQ(value, -1);
}

TEST(charToInt, minusSignNotCounted){
    int value = charToInt('-');
    ASSERT_EQ(value, -1);
}