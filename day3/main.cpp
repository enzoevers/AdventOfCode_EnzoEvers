#include "./include/FileReader.hpp"
#include "./include/SchematicProcessing.hpp"
#include <iostream>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    auto fileReader = std::make_shared<FileReader>(argv[1]);
    SchematicProcessing schematicProcessing(fileReader, '.');

    std::cout << "processNumbersAroundSymbol" << std::endl;
    int sum = schematicProcessing.processSchematic(
        &SchematicProcessing::processNumbersAroundSymbol);

    std::cout << "processPotentialGearRatio" << std::endl;
    int sumGearRatio = schematicProcessing.processSchematic(
        &SchematicProcessing::processPotentialGearRatio);

    std::cout << "sum: " << sum << std::endl;
    std::cout << "sumGearRatio: " << sumGearRatio << std::endl;

    return 0;
}