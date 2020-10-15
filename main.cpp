#include <string>
#include <iostream>
#include <stdlib.h>
#include "headers/ioutility.h"
#include "headers/utility.h"
#include "headers/hash.h"

int main(int argc, char **argv)
{
    std::string input;

    if (argc < 2)
        input = manualInput();
    else if (argc == 2)
        input = readInput(argv[1]);
    else
    {
        std::cerr << "|ERROR| Bad Formatting \nExiting..." << std::endl;
        return -1;
    }
    std::cout << hash(input) << std::endl;

    return 0;
}