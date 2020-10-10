#include <string>
#include <iostream>
#include <bitset>
#include <vector>


std::string padToCongruent(std::string input)
{
    while (input.size() % 512 != 448)
        input += "0";
    
    return input;
}

std::vector<std::string> getChunks(const std::string &input, const unsigned &modifier)
{
    std::vector<std::string> chunks;
    for (size_t i = 0; i < input.length(); i += modifier)
        chunks.push_back(input.substr(i, modifier));
    
    return chunks;
}

inline std::bitset<32> lrot(std::bitset<32> word, unsigned bit)
{
    return (word << bit)|(word >> (32 - bit));
}

inline std::bitset<32> transform(std::bitset<32> *words)
{
    std::bitset<32> xorTransed = words[0] ^ words[1] ^ words[2] ^ words[3];
    return lrot(xorTransed, 1);  //Left rotation by 1 bit
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

void transformWords(std::vector<std::string> words)
{
    std::bitset<32> h0 = std::bitset<32>(std::string("01100111010001010010001100000001"));
    std::bitset<32> h1 = std::bitset<32>(std::string("11101111110011011010101110001001"));
    std::bitset<32> h2 = std::bitset<32>(std::string("10011000101110101101110011111110"));
    std::bitset<32> h3 = std::bitset<32>(std::string("00010000001100100101010001110110"));
    std::bitset<32> h4 = std::bitset<32>(std::string("11000011110100101110000111110000"));
    std::bitset<32> vars[] = {h0, h1, h2, h3, h4};

    for (size_t i = 0; i <= 79; ++i) //Looping through words
    {
        auto transWord = std::bitset<32>(words[i]);
        std::bitset<32> f, k;

        if (i <= 19)
            trans1(f, k, vars);
        else if (i <= 39)
            trans2(f, k, vars);
        else if (i <= 59)
            trans3(f, k, vars);
        else if (i <= 79)
            trans4(f, k, vars);

        std::bitset<32> temp = (lrot(vars[0], 5).to_ullong() + f.to_ullong() + vars[4].to_ullong() + k.to_ullong() + transWord.to_ullong());
        vars[4] = vars[3];
        vars[3] = vars[2];
        vars[2] = lrot(vars[1], 30);
        vars[1] = vars[0];
        vars[0] = temp;
    }

    h0 = h0.to_ullong() + vars[0].to_ullong();
    h1 = h1.to_ullong() + vars[1].to_ullong();
    h2 = h2.to_ullong() + vars[2].to_ullong();
    h3 = h3.to_ullong() + vars[3].to_ullong();
    h4 = h4.to_ullong() + vars[4].to_ullong();

    std::cout << std::hex << h0.to_ullong()  << std::endl;
    
}

void extendWords(std::vector<std::string> &words)
{
    int i = 16;
    for (size_t i = 16; i <= 79; i++)
    {
        std::bitset<32> wordArr[4] = {std::bitset<32>(words[i-3]), std::bitset<32>(words[i-8]),
        std::bitset<32>(words[i-14]), std::bitset<32>(words[i-16])};

        words.push_back(transform(wordArr).to_string());
    }    
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

    // Proccess each chunk seperately
    for (auto &&chunk : words)
    {
        extendWords(chunk);
        transformWords(chunk);
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
    /* std::bitset<32> a (std::string("00000000000000000000000000000000")), b (std::string("01000001001000000101010001100101"));
    std::bitset<32> words[] = {a, a, a, b};
    std::cout << transform1(words).to_string(); */
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
    
    return -1;
}