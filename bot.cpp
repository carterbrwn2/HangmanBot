// bot.cpp
// Created by Carter on 7/2/2019.
//

#include "bot.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace hbot;
using namespace std;

void bot::Run() {
    InitializeCandidates(dictionary);
    string target = GetTarget();
    int word_length = target.length();
    // An array to model the work towards the target word
    char word[word_length];
    // Initialize word array - no guesses made yet so all underscores
    for (int i = 0; i < word_length; ++i) {
        word[i] = '_';
    }
    RemoveIncorrectLength(word_length);
    // Make guesses until game ends
    char guess;
    while (num_lives >= 0 && candidates.size() > 1) {
        guess = GetBestGuess();
        if (target.find(guess) != string::npos) {
            UpdateWord(guess, word, target);
            EliminateWithout(word);
        } else {
            EliminateContaining(guess);
            num_lives--;
        }
    }
    GameOver(num_lives>=0);
}

// Text file format is assumed to be one word per line,
// with no newline at the end of the document.
// The filename is assumed to be in the format
// "filename.txt"
void bot::InitializeCandidates(string& filename) {
    string word;
    ifstream words_file(filename);
    if (words_file.is_open()) {
        while (getline(words_file, word)) {
            candidates.push_back(word);
        }
        words_file.close();
    } else {
        cout << "Unable to open " << filename << "\n";
    }
}
