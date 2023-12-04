#include "../include/StringManipulation.hpp"
#include "gtest/gtest.h"

TEST(StringManipulation, onlyLowerCaseNotAffected) {
    std::string str = "jdkslankjdahf";

    ASSERT_EQ(StringManipulation::toLowerString(str), str);
}

TEST(StringManipulation, onlyUpperCaseLowAllLowerCase) {
    std::string str = "ABCDEFGHI";
    std::string expectedStr = "abcdefghi";

    ASSERT_EQ(StringManipulation::toLowerString(str), expectedStr);
}

TEST(StringManipulation, someUpperCaseLowAllLowerCase) {
    std::string expectedStr = "abcdefghi";

    std::string str = "ABcdefghi";
    ASSERT_EQ(StringManipulation::toLowerString(str), expectedStr);

    str = "abcdefgHI";
    ASSERT_EQ(StringManipulation::toLowerString(str), expectedStr);

    str = "abcDefghi";
    ASSERT_EQ(StringManipulation::toLowerString(str), expectedStr);

    str = "abCDefGhi";
    ASSERT_EQ(StringManipulation::toLowerString(str), expectedStr);
}