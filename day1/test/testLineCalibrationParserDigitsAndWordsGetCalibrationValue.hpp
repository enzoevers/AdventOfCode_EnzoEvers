#include "../include/LineCalibrationParserDigitsAndWords.hpp"
#include "gtest/gtest.h"

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     noIntegersReturnsMinus1) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str = "jvkldnsjkhtkjfldsgnjf";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     emptyStringReturnsMinus1) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str;
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     singleIntegerReturnsThisTwice) {
    LineCalibrationParserDigitsAndWords parser;

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

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     singleWordIntegerReturnsThisTwice) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str = "qweroNesdf";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 11);

    str = "threeqwersadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 33);

    str = "qwersadfFive";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 55);
}

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     twoIntegersReturnsTheseTwo) {
    LineCalibrationParserDigitsAndWords parser;

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

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     twoWordIntegersReturnsTheseTwo) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str = "oneqwersadfFIVE";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qwTwOerThreesadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "oneFourqwersadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 14);

    str = "qwersadffOURrthree";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 43);
}

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     multipleIntegersOnlyReturnFirstAndLast) {
    LineCalibrationParserDigitsAndWords parser;

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

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     multipleWordIntegersOnlyReturnFirstAndLast) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str = "oneqwerTWOsaFOURdfFIVE";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qwTWOeSEVENrTHREEsadf";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "SEVENthreeTwoFivesixninethrEe";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 73);
}

TEST(LineCalibrationParserDigitsAndWords_getCalibrationValue,
     mixedWordAndIntegers) {
    LineCalibrationParserDigitsAndWords parser;

    std::string str = "fjdsakl3fdsONE";
    int value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 31);

    str = "fjdsaklTHREEfds1";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 31);

    str = "fjds2klTHREEfds1";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 21);

    str = "fjdsTWOkl3fdsONE";
    value = parser.getCalibrationValue(str);
    ASSERT_EQ(value, 21);
}