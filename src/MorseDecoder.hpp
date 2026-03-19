#pragma once

#include <string>
#include <unordered_map>

class MorseDecoder {
public:
    MorseDecoder();

    // Input methods
    void addDot();
    void addDash();

    // Validation
    bool validateLetter();

    // Getters
    std::string getCurrentSequence() const { return currentSequence; }
    std::string getCurrentWord() const { return currentWord; }
    std::string getLastError() const { return lastError; }

    // Utility
    void reset();
    void clearWord();

private:
    std::string currentSequence;
    std::string currentWord;
    std::string lastError;

    // Morse code dictionary
    std::unordered_map<std::string, char> morseToChar;

    // Initialize the Morse dictionary
    void initializeMorseDictionary();
};
