#include <iostream>
#include "src/challenge.hpp"

int main(int argc, char** argv) {
    if(argc == 1){
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    int sum = getSumOfCalibrationValues(file);

    return 0;
}