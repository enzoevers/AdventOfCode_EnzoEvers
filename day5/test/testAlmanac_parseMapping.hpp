#include "../include/Almanac.hpp"
#include "gtest/gtest.h"

TEST(Almanac_parseMapping, placeholder) {
    Almanac almanac;

    Mapping mapping = almanac.parseMapping("123 234 2");

    ASSERT_EQ(mapping.srcStartId, 234);
    ASSERT_EQ(mapping.dstStartId, 123);
    ASSERT_EQ(mapping.range, 2);
}

TEST(Almanac_parseMapping, placeholderOneValue0) {
    Almanac almanac;

    Mapping mapping = almanac.parseMapping("123 0 2");

    ASSERT_EQ(mapping.srcStartId, 0);
    ASSERT_EQ(mapping.dstStartId, 123);
    ASSERT_EQ(mapping.range, 2);
}
