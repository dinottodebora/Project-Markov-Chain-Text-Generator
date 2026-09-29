#include "markov.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <ctime>

int main()
{
    int textLength = 1000;

    srand(time(0));
    std::cout << "Hello!";
    std::string testWords[] = {"the", "cat", "sat", "down"};
    std::cout << joinWords(testWords, 0, 2) << std::endl;
    std::cout << joinWords(testWords, 1, 3) << std::endl;

    std::string words[textLength];
    int count = readWordsFromFile("Alice.txt", words, textLength);
    std::cout << "Read " << count << " words" << std::endl;
    for (int i = 0; i < 10 && i < count; i++)
    {
        std::cout << words[i] << std::endl;
    }
    std::string prefixes[textLength], suffixes[textLength];
    int chainSize = buildMarkovChain(words, count, 2, prefixes, suffixes, textLength);
    for (int i = 0; i < 20 && i < chainSize; i++)
    {
        std::cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << std::endl;
    }
    // for (int i = 0; i < 10; i++) {
    // std::cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << std::endl;
    //}
    for (int i = 0; i < 10; i++)
    {
        std::cout << getRandomSuffix(prefixes, suffixes, chainSize, "dogs. I") << std::endl;
    }

    for (int i = 0; i < 5; i++)
    {
        std::cout << getRandomPrefix(prefixes, chainSize) << std::endl;
    }
    std::string output = generateText(prefixes, suffixes, chainSize, 2, 20);
    std::cout << output << std::endl;

    for (int i = 4; i < 11; i++)
    {   std::cout << " i = " << i << std::endl;
        std::string output = generateText(prefixes, suffixes, chainSize, 2, i);
        std::cout << output << std::endl;
    }
}