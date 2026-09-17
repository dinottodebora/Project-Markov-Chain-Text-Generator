#include "markov.h"
#include <fstream>
#include <cstdlib>

std::string joinWords(const std::string words[], int startIndex, int count){

    std:: string result_joint_words = "";
    
    for(int i = 0; i <= count-1; i++){
        result_joint_words = result_joint_words + words[startIndex + i];
        if (i != count - 1){
            result_joint_words = result_joint_words + " ";   
        }
    }
    return result_joint_words;
}

int readWordsFromFile(std::string filename, std::string words[], int maxWords){
    
    std::ifstream input_File(filename);

    if(input_File.is_open() == false){
        return -1;
    }
    int counter = 0;

    while(counter < maxWords && input_File >> words[counter]){
        counter = counter + 1;
    }

    input_File.close();

    return counter;
}

std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[],
int chainSize, std::string currentPrefix){

    return "";
}

std::string getRandomPrefix(const std::string prefixes[], int chainSize){
    return "";
}

std::string generateText(const std::string prefixes[], const std::string suffixes[],
int chainSize, int order, int numWords){
    return "";
}
