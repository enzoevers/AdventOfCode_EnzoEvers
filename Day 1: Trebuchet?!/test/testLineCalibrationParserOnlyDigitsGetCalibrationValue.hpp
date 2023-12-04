#include "../include/LineCalibrationParserOnlyDigits.hpp"
#include "gtest/gtest.h"

TEST(getCalibrationValue, noIntegersReturnsMinus1) {
    LineCalibrationParserOnlyDigits parser;

    std::string str = "jvkldnsjkhtkjfldsgnjf";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(getCalibrationValue, emptyStringReturnsMinus1) {
    LineCalibrationParserOnlyDigits parser;

    std::string str;
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(getCalibrationValue, singleIntegersReturnsThisTwice) {
    LineCalibrationParserOnlyDigits parser;

    std::string str = "qwer1sdf";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 11);

    str = "3qwersadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 33);

    str = "qwersadf5";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 55);
}

TEST(getCalibrationValue, twoIntegersReturnsTheseTwo) {
    LineCalibrationParserOnlyDigits parser;

    std::string str = "1qwersadf5";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qw2er3sadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "14qwersadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 14);

    str = "qwersadf43";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 43);
}

TEST(getCalibrationValue, multipleIntegersOnlyReturnFirstAndLast) {
    LineCalibrationParserOnlyDigits parser;

    std::string str = "1qwer2sa4df5";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qw2e7r3sadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "7854397983243";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 73);
}