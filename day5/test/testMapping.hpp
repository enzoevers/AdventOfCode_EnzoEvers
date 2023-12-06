#include "../include/Mapping.hpp"
#include "gtest/gtest.h"

TEST(Mapping, srcEndCorrect) {
    Mapping mapping(10, 15, 8);
    ASSERT_EQ(mapping.getSrcEndId(), 17);
}

TEST(Mapping, dstEndCorrect) {
    Mapping mapping(10, 15, 8);
    ASSERT_EQ(mapping.getDstEndId(), 22);
}

TEST(Mapping, offsetCorrectIfSrcStartLtDstStart) {
    Mapping mapping(10, 15, 8);
    ASSERT_EQ(mapping.getSrcToDstOffset(), 5);
}

TEST(Mapping, offsetCorrectIfSrcStartGtDstStart) {
    Mapping mapping(15, 10, 8);
    ASSERT_EQ(mapping.getSrcToDstOffset(), -5);
}

TEST(Mapping, srcStartLtDstStartDoesNotMapIfInputLtSrcStart) {
    Mapping mapping(10, 15, 8);

    ASSERT_EQ(mapping.map(5), 5);
    ASSERT_EQ(mapping.rmap(5), 5);
    ASSERT_EQ(mapping.map(9), 9);
    ASSERT_EQ(mapping.rmap(9), 9);
}

TEST(Mapping, srcStartLtDstStartDoesNotMapIfInputGtSrcStart) {
    Mapping mapping(10, 15, 8);

    ASSERT_EQ(mapping.map(18), 18);
    ASSERT_EQ(mapping.rmap(18), 13);
    ASSERT_EQ(mapping.map(100), 100);
    ASSERT_EQ(mapping.rmap(100), 100);
}

TEST(Mapping, srcStartLtDstStartDoesMapIfInputEqSrcStart) {
    Mapping mapping(10, 15, 8);

    ASSERT_EQ(mapping.map(10), 15);
    ASSERT_EQ(mapping.rmap(15), 10);
}

TEST(Mapping, srcStartLtDstStartDoesMapIfInputEqSrcEnd) {
    Mapping mapping(10, 15, 8);

    ASSERT_EQ(mapping.map(17), 22);
    ASSERT_EQ(mapping.rmap(22), 17);
}