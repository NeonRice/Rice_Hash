#include <string>
#include <iostream>
#include <bitset>
#include <vector>


std::string padToCongruent(std::string input)
{
    while (input.size() % 512 != 448)
    {
        input += "0";
    }
    
    return input;
}

std::vector<std::string> getChunks(const std::string &input, const unsigned &modifier)
{
    std::vector<std::string> chunks;
    for (size_t i = 0; i < input.length(); i += modifier)
    {
        chunks.push_back(input.substr(i, modifier));
    }
    
    return chunks;
}


std::string hash(const std::string &input)
{
    int h0, h1, h2, h3, h4;
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

    std::vector<std::string> chunks = getChunks(paddedString, 512);
    
    std::vector<std::vector<std::string>> words;
    
    for (std::string chunk : chunks)
    {
        words.push_back(getChunks(chunk, 32));
    } 

    for (auto it = words.begin(); it != words.end(); ++it)
    {
        for (auto it2 = it->begin(); it2 != it->end(); ++it2)
        {
            std::cout << *it2 << std::endl;
        }
    }

}

std::string manualInput()
{
    std::string input;

    std::cout << "Enter what you want to hashify: ";
    std::getline(std::cin, input);

    return input;
}


int main(int argc, char** argv)
{
    std::string input;
    //Hash here HAHA
    if (argc < 2)
    {
        // Input by hand
        input = manualInput();
        hash(input);
    }
    else if (argc == 2)
    {
        std::string fileName = argv[1];
        //Do file reading here
    }
    
    return 0;
}