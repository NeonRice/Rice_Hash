#pragma once

#include <string>
#include <iostream>
#include <bitset>
#include <vector>
#include "ioutility.h"
#include "utility.h"

template <class T, size_t BITSIZE>
std::vector<T> getChunks(const std::string &input)
{
    std::vector<T> chunks;
    for (size_t i = 0; i < input.length(); i += BITSIZE)
        chunks.push_back(T(std::bitset<BITSIZE>(input.substr(i, BITSIZE))));

    return chunks;
}

template <size_t BITSIZE>
struct BitsetObject
{
    std::bitset<BITSIZE> value;

    BitsetObject(std::bitset<BITSIZE> val) : value(val){};
};

template <size_t BITSIZE>
struct Chunk : public BitsetObject<BITSIZE>
{
    Chunk()
    {
        words = getChunks<BitsetObject<BITSIZE / 16>, BITSIZE / 16>(this->value.to_string()); 
    }
    Chunk(std::bitset<BITSIZE> bitSet) : BitsetObject<BITSIZE>(bitSet)
    {
        words = getChunks<BitsetObject<BITSIZE / 16>, BITSIZE / 16>(this->value.to_string());
    }

    std::vector<BitsetObject<BITSIZE / 16>> words;
};

inline std::string padToCongruent(std::string input)
{
    while (input.size() % 512 != 448)
        input += "0";

    return input;
}

template <class T>
void transformWords(T &chunk, std::bitset<32> *digest)
{
    std::bitset<32> vars[] = {digest[0], digest[1], digest[2],
                              digest[3], digest[4], digest[5], digest[6], digest[7]};

    for (size_t i = 0; i <= 79; ++i) //Looping through words
    {
        std::bitset<32> f, k;

        if (i <= 19)
            trans1(f, k, vars);
        else if (i <= 39)
            trans2(f, k, vars);
        else if (i <= 59)
            trans3(f, k, vars);
        else if (i <= 79)
            trans4(f, k, vars);

        std::bitset<32> temp = (lrot(vars[0], 5).to_ullong() + f.to_ullong() + vars[4].to_ullong() + k.to_ullong() + chunk.words[i].value.to_ullong());

        vars[5] = lrot(vars[4], 10) ^ vars[3];
        vars[6] = lrot(vars[5] | vars[2] | vars[1], 4);
        vars[7] = vars[4].to_ullong() + vars[6].to_ullong() + lrot(f.to_ullong() + k.to_ullong(), 10).to_ullong();
        vars[4] = vars[3];
        vars[3] = vars[2];
        vars[2] = lrot(vars[1], 30);
        vars[1] = vars[0];
        vars[0] = temp;
    }

    digest[0] = std::bitset<32>(digest[0].to_ullong() + vars[0].to_ullong());
    digest[1] = std::bitset<32>(digest[1].to_ullong() + vars[1].to_ullong());
    digest[2] = std::bitset<32>(digest[2].to_ullong() + vars[2].to_ullong());
    digest[3] = std::bitset<32>(digest[3].to_ullong() + vars[3].to_ullong());
    digest[4] = std::bitset<32>(digest[4].to_ullong() + vars[4].to_ullong());
    digest[5] = std::bitset<32>(digest[5].to_ullong() + vars[5].to_ullong());
    digest[6] = std::bitset<32>(digest[6].to_ullong() + vars[6].to_ullong());
    digest[7] = std::bitset<32>(digest[7].to_ullong() + vars[7].to_ullong());
}

template <class T>
void extendWords(T &words)
{
    int i = 16;
    for (size_t i = 16; i <= 79; i++)
    {
        std::bitset<32> wordArr[4] = {words[i - 3].value, words[i - 8].value,
                                      words[i - 14].value, words[i - 16].value};
        words.push_back(transform(wordArr));
    }
}

std::string hash(const std::string &input)
{
    std::string binarifiedString = "";

    for (auto it = input.begin(); it != input.end(); ++it)
    {
        //Converting char to ASCII and then converting it to binary
        int charCode = *it;
        std::bitset<8> binaryNum(charCode);
        binarifiedString += binaryNum.to_string(); //Concat to a big chunk of a string
    }
    binarifiedString += "1";

    std::string paddedString = padToCongruent(binarifiedString);

    paddedString += std::bitset<64>(binarifiedString.size() - 1).to_string();

    std::vector<Chunk<512>> chunks = getChunks<Chunk<512>, 512>(paddedString); //Processes words aswell as chunks?

    std::bitset<32> h0 = std::bitset<32>(std::string("01100111010001010010001100000001"));
    std::bitset<32> h1 = std::bitset<32>(std::string("11101111110011011010101110001001"));
    std::bitset<32> h2 = std::bitset<32>(std::string("10011000101110101101110011111110"));
    std::bitset<32> h3 = std::bitset<32>(std::string("00010000001100100101010001110110"));
    std::bitset<32> h4 = std::bitset<32>(std::string("11000011110100101110000111110000"));
    std::bitset<32> h5 = std::bitset<32>(std::string("00101110100101011010111010001001"));
    std::bitset<32> h6 = std::bitset<32>(std::string("11111000001000000101100010001010"));
    std::bitset<32> h7 = std::bitset<32>(std::string("00000010001000100101010000110010"));

    std::bitset<32> digest[8] = {h0, h1, h2, h3, h4, h5, h6, h7};

    // Proccess each chunk seperately
    for (auto &&chunk : chunks)
    {
        extendWords(chunk.words);
        transformWords(chunk, digest);
    }

    return digestToString(digest);    
}