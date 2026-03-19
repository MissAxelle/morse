#include "MorseDecoder.hpp"

MorseDecoder::MorseDecoder() : currentSequence(""), currentWord(""), lastError("") {
    initializeMorseDictionary();
}

void MorseDecoder::initializeMorseDictionary() {
    // Letters A-Z
    morseToChar[".-"] = 'A';
    morseToChar["-..."] = 'B';
    morseToChar["-.-."] = 'C';
    morseToChar["-.."] = 'D';
    morseToChar["."] = 'E';
    morseToChar["..-."] = 'F';
    morseToChar["--."] = 'G';
    morseToChar["...."] = 'H';
    morseToChar[".."] = 'I';
    morseToChar[".---"] = 'J';
    morseToChar["-.-"] = 'K';
    morseToChar[".-.."] = 'L';
    morseToChar["--"] = 'M';
    morseToChar["-."] = 'N';
    morseToChar["---"] = 'O';
    morseToChar[".--."] = 'P';
    morseToChar["--.-"] = 'Q';
    morseToChar[".-."] = 'R';
    morseToChar["..."] = 'S';
    morseToChar["-"] = 'T';
    morseToChar["..-"] = 'U';
    morseToChar["...-"] = 'V';
    morseToChar[".--"] = 'W';
    morseToChar["-..-"] = 'X';
    morseToChar["-.--"] = 'Y';
    morseToChar["--.."] = 'Z';

    // Digits 0-9
    morseToChar["-----"] = '0';
    morseToChar[".----"] = '1';
    morseToChar["..---"] = '2';
    morseToChar["...--"] = '3';
    morseToChar["....-"] = '4';
    morseToChar["....."] = '5';
    morseToChar["-...."] = '6';
    morseToChar["--..."] = '7';
    morseToChar["---.."] = '8';
    morseToChar["----."] = '9';
}

void MorseDecoder::addDot() {
    currentSequence += ".";
    lastError = "";
}

void MorseDecoder::addDash() {
    currentSequence += "-";
    lastError = "";
}

bool MorseDecoder::validateLetter() {
    // Check if sequence is empty
    if (currentSequence.empty()) {
        lastError = "Invalid sequence";
        return false;
    }

    // Look up in dictionary
    auto it = morseToChar.find(currentSequence);
    if (it != morseToChar.end()) {
        // Valid - add character to word
        currentWord += it->second;
        currentSequence = "";
        lastError = "";
        return true;
    } else {
        // Invalid
        lastError = "Invalid sequence: " + currentSequence;
        currentSequence = "";
        return false;
    }
}

void MorseDecoder::reset() {
    currentSequence = "";
    currentWord = "";
    lastError = "";
}

void MorseDecoder::clearWord() {
    // Clear the composed word and any pending sequence so user can start fresh
    currentWord.clear();
    currentSequence.clear();
    lastError.clear();
}
