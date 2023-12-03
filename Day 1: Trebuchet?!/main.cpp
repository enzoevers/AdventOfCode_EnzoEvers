#include <iostream>
#include <fstream>

void readFile(std::ifstream& file) {
    for(std::string line; std::getline(file, line);){
        std::cout << line << std::endl;
    }
}

int main(int argc, char** argv) {
    if(argc == 1){
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    readFile(file);

    return 0;
}