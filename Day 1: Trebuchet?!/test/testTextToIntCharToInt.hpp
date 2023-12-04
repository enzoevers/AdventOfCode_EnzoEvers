#include "gtest/gtest.h"
#include "../include/TextToInt.hpp"

TEST(charToInt, belowAscii0){
    int value = TextToInt::charToInt('(');
    ASSERT_EQ(value, -1);
}

TEST(charToInt, inRange){
    ASSERT_EQ(TextToInt::charToInt('0'), 0);
    ASSERT_EQ(TextToInt::charToInt('1'), 1);
    ASSERT_EQ(TextToInt::charToInt('2'), 2);
    ASSERT_EQ(TextToInt::charToInt('3'), 3);
    ASSERT_EQ(TextToInt::charToInt('4'), 4);
    ASSERT_EQ(TextToInt::charToInt('5'), 5);
    ASSERT_EQ(TextToInt::charToInt('6'), 6);
    ASSERT_EQ(TextToInt::charToInt('7'), 7);
    ASSERT_EQ(TextToInt::charToInt('8'), 8);
    ASSERT_EQ(TextToInt::charToInt('9'), 9);
}

TEST(charToInt, aboveAscii9){
    int value = TextToInt::charToInt('a');
    ASSERT_EQ(value, -1);
}

TEST(charToInt, minusSignNotCounted){
    int value = TextToInt::charToInt('-');
    ASSERT_EQ(value, -1);
}