#include "../include/MatrixCoordinate.hpp"
#include "gtest/gtest.h"

TEST(MatrixCoordinate_toLinear,
     returnsCorrectLinearIndexForZeroZeroCoordinate) {

    MatrixCoordinate coordinate(0, 0);

    std::pair<std::size_t, std::size_t> srcDimensions(3, 5);
    ASSERT_EQ(coordinate.toLinear(srcDimensions), 0);

    srcDimensions =
        std::make_pair<std::size_t, std::size_t>(3428549378392, 432787584);
    ASSERT_EQ(coordinate.toLinear(srcDimensions), 0);
}

TEST(MatrixCoordinate_toLinear,
     returnsCorrectLinearIndexForCoordinateOnFirstRow) {

    MatrixCoordinate coordinate(4, 0);
    std::pair<std::size_t, std::size_t> srcDimensions(6, 5);
    ASSERT_EQ(coordinate.toLinear(srcDimensions), 4);

    coordinate = MatrixCoordinate(432432432, 0);
    srcDimensions =
        std::make_pair<std::size_t, std::size_t>(3428549378392, 432787584);

    ASSERT_EQ(coordinate.toLinear(srcDimensions), 432432432);
}

TEST(MatrixCoordinate_toLinear, returnsCorrectLinearIndexForCoordinateAnyRow) {

    MatrixCoordinate coordinate(4, 1);
    std::pair<std::size_t, std::size_t> srcDimensions(6, 5);
    ASSERT_EQ(coordinate.toLinear(srcDimensions), 4 + (6 * 1));

    coordinate = MatrixCoordinate(432432432, 5);
    srcDimensions =
        std::make_pair<std::size_t, std::size_t>(3428549378392, 432787584);

    ASSERT_EQ(coordinate.toLinear(srcDimensions),
              432432432 + (5 * 3428549378392));
}

TEST(MatrixCoordinate_toLinear, throwsIfSrcDimensionsIsZeroZero) {
    std::pair<std::size_t, std::size_t> srcDimensions(0, 0);

    MatrixCoordinate coordinate(0, 0);
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);

    coordinate.x = 3;
    coordinate.y = 4;
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);
}

TEST(MatrixCoordinate_toLinear, throwsIfXGteWidth) {
    std::pair<std::size_t, std::size_t> srcDimensions(10, 100);

    MatrixCoordinate coordinate(10, 42);
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);

    coordinate.x = 54;
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);
}

TEST(MatrixCoordinate_toLinear, throwsIfYGteWidth) {
    std::pair<std::size_t, std::size_t> srcDimensions(100, 10);

    MatrixCoordinate coordinate(42, 10);
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);

    coordinate.y = 54;
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);
}

TEST(MatrixCoordinate_toLinear, throwsIfXAndYGteWidth) {
    std::pair<std::size_t, std::size_t> srcDimensions(10, 100);

    MatrixCoordinate coordinate(10, 100);
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);

    coordinate.x = 11;
    coordinate.y = 101;
    EXPECT_THROW(
        {
            try {

                coordinate.toLinear(srcDimensions);
            } catch (const std::out_of_range &e) {
                // and this tests that it has the correct message
                EXPECT_STREQ("Coordinates out of range for size", e.what());
                throw;
            }
        },
        std::out_of_range);
}