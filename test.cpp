#include <chrono>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include "headers/ioutility.h"
#include "headers/hash.h"

const std::string pathToTests = "tests";

inline std::string fancyLabel(const std::string &input)
{
    std::string label = "\u25A0\u25A0\u25A0\u25A0\u25A0\u25A0\u25A0\u25A0";
    return "\u2588" + label + "\u2588 " + input + " \u2588" + label + "\u2588";
}

void speedTest(const std::string &fileName)
{
    std::string line;
    std::ifstream file(fileName);

    if (file.fail())
    {
        std::cerr << "|ERROR| Unable to open input file " << fileName << "\nExiting..." << std::endl;
        std::exit(0);
    }

    auto start = std::chrono::system_clock::now();
    std::cout << fancyLabel("Speed Test") << std::endl;
    while (std::getline(file, line))
        hash(line);
    auto end = std::chrono::system_clock::now();

    std::cout << "Test took " << std::chrono::duration<double>(end - start).count() << " seconds" << std::endl;
}

void collisionTest(std::string filename)
{
    std::string data = readInput(filename);
    std::unordered_set<std::string> seen_before;
    int collisions = 0, count = 0;
    std::string digestedHash;
    
    std::stringstream ss(data);
    std::string line = " ";

    std::cout << fancyLabel("Collision Test") << std::endl;
    while (std::getline(ss, line)) 
    {
        ++count;
        digestedHash = hash(line);
        auto i = seen_before.find(digestedHash);
        if (i == seen_before.end()) 
        {
            seen_before.emplace_hint(i, digestedHash);
        }
        else 
        {
            ++collisions;
        }
    }
    std::cout << "Total Input is " << count << " lines" << std::endl;
    std::cout << "Collision # is " << collisions << std::endl;
}

int main(int argc, char **argv)
{
    for (const auto & entry : std::filesystem::directory_iterator(pathToTests))
    {
        std::string path = entry.path();
        std::cout << fancyLabel(path) << std::endl;
        speedTest(path);
        collisionTest(path);
    }
}