#pragma once

#include <bitset>

inline std::bitset<32> lrot(std::bitset<32> word, unsigned bit)
{
    return (word << bit) | (word >> (32 - bit));
}

inline std::bitset<32> transform(std::bitset<32> *words)
{
    std::bitset<32> xorTransed = words[0] ^ words[1] ^ words[2] ^ words[3];
    return lrot(xorTransed, 1); //Left rotation by 1 bit
}

void trans1(std::bitset<32> &f, std::bitset<32> &k, std::bitset<32> *vars)
{
    f = ((vars[1] & vars[2]) | (~vars[1] & vars[3]));
    k = std::bitset<32>(std::string("01011010100000100111100110011001"));
}

void trans2(std::bitset<32> &f, std::bitset<32> &k, std::bitset<32> *vars)
{
    f = vars[1] ^ vars[2] ^ vars[3];
    k = std::bitset<32>(std::string("01101110110110011110101110100001"));
}

void trans3(std::bitset<32> &f, std::bitset<32> &k, std::bitset<32> *vars)
{
    f = (vars[1] & vars[2]) | (vars[1] & vars[3]) | (vars[2] & vars[3]);
    k = std::bitset<32>(std::string("10001111000110111011110011011100"));
}

void trans4(std::bitset<32> &f, std::bitset<32> &k, std::bitset<32> *vars)
{
    f = vars[1] ^ vars[2] ^ vars[3];
    k = std::bitset<32>(std::string("11001010011000101100000111010110"));
}

