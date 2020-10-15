#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <bitset>
#include <fstream>

std::string manualInput()
{
    std::string input;

    std::cout << "Enter what you want to hashify: ";
    std::getline(std::cin, input);

    return input;
}

std::string readInput(std::string fileName)
{
    std::ifstream data(fileName);
    if(data.fail()) 
    {
        std::cerr << "|ERROR| Unable to open input file " << fileName << "\nExiting..." << std::endl;
        std::exit(0);
    }
    std::string input;

    std::stringstream strStream;
    strStream << data.rdbuf();         //read the file
    std::string str = strStream.str(); //str holds the content of the file

    data.close();

    return str;
}

std::string digestToString(std::bitset<32> *digest)
{
    std::stringstream ss;
    ss << std::hex << digest[0].to_ullong() << digest[1].to_ullong() << digest[2].to_ullong()
              << digest[3].to_ullong() << digest[4].to_ullong() << digest[5].to_ullong()
              << digest[6].to_ullong() << digest[7].to_ullong();
    return ss.str();
}