#include "markov.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <ctime>
#include <string>

bool isPositiveNumber(std::string input)
{

    if (input == "")
    {
        return false;
    }
    for (int i = 0; i < input.length(); i++)
    {
        if ('0' > input[i] || input[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int countWords(std::string text)
{
    int result = 1;
    for (int i = 0; i < text.length(); i++)
    {
        if (text[i] == ' ')
        {
            result = result + 1;
        }
    }
    return result;
}

int main()
{

    int MAX_WORDS = 5000;
    std::string words[MAX_WORDS];
    std::string prefixes[MAX_WORDS];
    std::string suffixes[MAX_WORDS];

    srand(time(0));

    std::string fileName;

    std::cout << "Filename: ";
    std::cin >> fileName;

    std::string strOrder;
    int order;

    while (true)
    {
        std::cout << "Order: ";
        std::cin >> strOrder;

        if (strOrder == "1" or strOrder == "2" or strOrder == "3")
        {
            order = stoi(strOrder);
            break;
        }
        else
        {
            std::cout << "Invalid input. Enter a number from 1 to 3." << std::endl;
        }
    }

    int numWord;

    while (true)
    {
        std::string strnumWord;
        std::cout << "Number of words: ";
        std::cin >> strnumWord;

        if (!isPositiveNumber(strnumWord))
        {
            std::cout << "Invalid input. Enter a positive integer number." << std::endl;
            continue;
        }
        numWord = stoi(strnumWord);
        if (numWord > MAX_WORDS)
        {
            std::cout << "Max allowed number of words is 5000. Try again." << std::endl;
            continue;
        }
        break;
    }

    int resultFileWordCount = readWordsFromFile(fileName, words, MAX_WORDS);
    if (resultFileWordCount == -1)
    {
        std::cout << "We couldn't open your file." << std::endl;
        return 0;
    }
    if (resultFileWordCount <= order)
    {
        std::cout << "At least order + 1 training words are needed." << std::endl;
        std::cout << "Your file might be empty or contain less words than order!" <<std::endl;
        return 0;
    }

    int resultMarkovChainSize = buildMarkovChain(words, resultFileWordCount, order, prefixes, suffixes, MAX_WORDS);
    if (resultMarkovChainSize == 0)
    {
        std::cout << "Something went wrong. Markov Chain is 0." << std::endl;
        return 0;
    }
    if (resultMarkovChainSize == MAX_WORDS)
    {
        std::cout << "5000 words were used and additional words, if any, were ignored." << std::endl;
    }

    std::string myGeneratedText = generateText(prefixes, suffixes, resultMarkovChainSize, order, numWord);
    
    std::cout << std::endl;
    std::cout << "Here is your generated text!" << std::endl;
    std::cout << std::endl;
    std::cout << myGeneratedText;
    std::cout << std::endl;
    std::cout << "Word count: " << countWords(myGeneratedText) << std::endl;
    if (numWord != countWords(myGeneratedText))
    {
        std::cout << "If the numbers of words is less than you expected is because the generator stopped at a dead end.";
    }

}
    //You can ignore everything under here! These are just notes and tests!!!!
    /*Step 8: Complete main()
    Now put it all together! Your main() should:
    1. Add srand(time(0)); at the very beginning (for randomness).
    2. Ask for the filename, order, and maximum number of words. Reject nonnumeric input, order outside 1–3, or a requested count smaller than order; explain the problem and let the user try again.
    3. Use a named capacity, for example const int MAX_WORDS = 5000; declare words, prefixes, and suffixes with that capacity. Pass the actual capacity to the functions. This project may train on only the first 5000 words of a larger file.
    4. Read the file. Explain a -1 result as a file-open failure. If the count is <= order, explain that at least order + 1 training words are needed. Do not try to generate from those inputs.
    5. Build the chain and confirm chainSize > 0 before random selection. If the input array filled to capacity, tell the user that at most MAX_WORDS input words were used and additional words, if any, were ignored.
    6. Generate up to the requested number of words, stopping if a prefix has no successor.
    7. Print the generated text and its actual word count. If it is shorter than requested, explain that generation stopped at a dead end. Count the words in the returned text; do not change the required function signature.
    ✓ Git commit: "Completed main program"
    */

    // With order 1, each prefix is a single word.

    // int textLength = 1000;
    /*All tests are below this line
    std::cout << "Hello!";
    int textLength = 1000;
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
    }*/
