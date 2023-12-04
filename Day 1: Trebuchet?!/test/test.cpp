#include "gtest/gtest.h"
#include "testCharToInt.hpp"
#include "testGetCalibrationValue.hpp"

int main(int argc, char** argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}