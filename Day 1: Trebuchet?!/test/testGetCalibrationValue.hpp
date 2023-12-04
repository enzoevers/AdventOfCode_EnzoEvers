#include "gtest/gtest.h"
#include "../src/challenge.hpp"

TEST(getCalibrationValue, noIntegersReturnsMinus1){
    std::string str = "jvkldnsjkhtkjfldsgnjf";
    int value = getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(getCalibrationValue, emptyStringReturnsMinus1){
    std::string str;
    int value = getCalibrationValue(str);
    ASSERT_EQ(value, -1);
}

TEST(getCalibrationValue, singleIntegersReturnsThisTwice){
    std::string str = "qwer1sdf";
    int value = getCalibrationValue(str);
    ASSERT_EQ(value, 11);

    str = "3qwersadf";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 33);

    str = "qwersadf5";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 55);
}

TEST(getCalibrationValue, twoIntegersReturnsTheseTwo){
    std::string str = "1qwersadf5";
    int value = getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qw2er3sadf";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "14qwersadf";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 14);

    str = "qwersadf43";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 43);
}

TEST(getCalibrationValue, multipleIntegersOnlyReturnFirstAndLast){
    std::string str = "1qwer2sa4df5";
    int value = getCalibrationValue(str);
    ASSERT_EQ(value, 15);

    str = "qw2e7r3sadf";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 23);

    str = "7854397983243";
    value = getCalibrationValue(str);
    ASSERT_EQ(value, 73);
}