#include "./testGame_part1.hpp"
#include "./testGame_part2.hpp"
#include "./testScratchCard_getPoints.hpp"
#include "./testScratchCard_parseCardString.hpp"

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}