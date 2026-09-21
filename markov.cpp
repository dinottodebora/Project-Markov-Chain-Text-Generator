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

int buildMarkovChain(const std::string words[], int numWords, int order,
    std::string prefixes[], std::string suffixes[], int maxChainSize) {

    if (order < 1 || order > 3){
        return 0;
    }
    if (numWords <= order){
        return 0;
    }
    if (maxChainSize <= 0){
        return 0;
    }
    
    int count = 0;
    int i = 0;
    
    while(i < numWords - order && count < maxChainSize){

        std::string prefix = joinWords(words, i, order);//prexif is a string with my text
        std::string suffix = words[i + order];
        prefixes[count] = prefix;
        suffixes[count] = suffix;
        count++;
        i++;
    }


    return count;
}

std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[],
    int chainSize, std::string currentPrefix){
//If prefixes = ["the", "cat", "the", "the"] and suffixes = ["cat", "sat", "dog", "bird"]
//And we call getRandomSuffix with currentPrefix = "the":
//- We find "the" at positions 0, 2, 3 → matchCount = 3
//- pick = rand() % 3 might give us 0, 1, or 2
//- We return suffixes[0], suffixes[2], or suffixes[3] → "cat", "dog", or "bird"

    int matchCount = 0;    

    for(int i = 0; i <= chainSize - 1; i++){
        if (prefixes[i] == currentPrefix){
            matchCount++;
        }
    }
    if (matchCount == 0){
        return "";
   }
   int pick = rand() % matchCount;
   int seenMatches = 0;

   for (int i = 0; i<= chainSize - 1; i++){
        if (prefixes[i] == currentPrefix){
            if (pick == seenMatches) {
                return suffixes[i];
            }

            seenMatches++;
        }
        }
        return "";
    }

std::string getRandomPrefix(const std::string prefixes[], int chainSize){
    if(chainSize <= 0){
        return "";
    }
    int index = rand() % chainSize;
    
    return prefixes[index];
}

std::string generateText(const std::string prefixes[], const std::string suffixes[],
    int chainSize, int order, int numWords){

    
    if (chainSize <= 0){
        return "";
    }
    if (order < 1 || order > 3){
        return "";
    }
    if (numWords < order){
        return "";
    }

    std::string currentPrefix = getRandomPrefix(prefixes,chainSize);

    std::string currentWords[3] = {"","",""};
    int wordIndex = 0;
    std::string temp = "";
    std::string result = currentPrefix;

    for (int i = 0; i < currentPrefix.length(); i++){
        if (currentPrefix[i] == ' '){ 
            if (wordIndex < order){                                                                                                                                           
            currentWords[wordIndex] = temp; }                                                                                                                                           
            wordIndex++;                                                                                                                                                               
            temp = "";                 
            } else {                                                                                                                                                                       
                temp += currentPrefix[i];  
            }
        }
        if (wordIndex < order) {
            currentWords[wordIndex] = temp;}
    

    for (int i=0; i < numWords - order;i++){
        std::string newWord = getRandomSuffix(prefixes,suffixes,chainSize,currentPrefix);
        if(newWord == ""){
            break;
        }else{
            result = result + " " + newWord;   
            for (int j = 0; j < order - 1; j++){
                currentWords[j] = currentWords[j + 1];
        }
        currentWords[order - 1] = newWord;
        currentPrefix = joinWords(currentWords, 0, order);

        }
    
}
    return result;     
}

    
