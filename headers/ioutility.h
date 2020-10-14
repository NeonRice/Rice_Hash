#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <bitset>

std::string manualInput()
{
    std::string input;

    std::cout << "Enter what you want to hashify: ";
    std::getline(std::cin, input);

    return input;
}
std::string digestToString(std::bitset<32> *digest)
{
    std::stringstream ss;
    ss << std::hex << digest[0].to_ullong() << digest[1].to_ullong() << digest[2].to_ullong()
              << digest[3].to_ullong() << digest[4].to_ullong() << digest[5].to_ullong()
              << digest[6].to_ullong() << digest[7].to_ullong() << std::endl;
    return ss.str();
}