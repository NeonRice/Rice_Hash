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

std::string getBinaryStrFromHexStr(std::string hexStr)
{
    std::string convertedString = "";
    for (int i = 0; i < hexStr.length(); ++i)
    {
        switch (hexStr[i])
        {
        case '0':
            convertedString.append("0000");
            break;
        case '1':
            convertedString.append("0001");
            break;
        case '2':
            convertedString.append("0010");
            break;
        case '3':
            convertedString.append("0011");
            break;
        case '4':
            convertedString.append("0100");
            break;
        case '5':
            convertedString.append("0101");
            break;
        case '6':
            convertedString.append("0110");
            break;
        case '7':
            convertedString.append("0111");
            break;
        case '8':
            convertedString.append("1000");
            break;
        case '9':
            convertedString.append("1001");
            break;
        case 'a':
            convertedString.append("1010");
            break;
        case 'b':
            convertedString.append("1011");
            break;
        case 'c':
            convertedString.append("1100");
            break;
        case 'd':
            convertedString.append("1101");
            break;
        case 'e':
            convertedString.append("1110");
            break;
        case 'f':
            convertedString.append("1111");
            break;
        }
    }
    return convertedString;
}