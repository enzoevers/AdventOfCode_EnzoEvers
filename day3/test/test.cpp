#include "testFileReader_readPartOfFile.hpp"
#include "testMatrixCoordinate_ToLinear.hpp"
#include "testSchematicReader_constructor.hpp"
#include "testSchematicReader_getBlock.hpp"
#include "testSchematicReader_getBlock_noFileReaderMock.hpp"
#include "testSchematicReader_getReadingAndPaddingColumns.hpp"
#include "testSchematicReader_getReadingAndPaddingRows.hpp"
#include "gtest/gtest.h"

int
main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}