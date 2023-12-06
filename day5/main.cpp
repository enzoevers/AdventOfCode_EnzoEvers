#include <iostream>

int
main(int argc, char **argv) {
    if (argc == 1) {
        std::cout << "Requires input file name" << std::endl;
        return 1;
    }

    return 0;
}