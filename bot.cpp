// bot.cpp
// Created by Carter on 7/2/2019.
//

#include "bot.h"

using namespace hbot;
using namespace std;

void bot::Run() {
    InitializeCandidates("words.txt");
    string target = GetTarget();
    int word_length = target.length();
    // An array to model the work towards the target word
    char word[word_length];
    // Initialize word array - no guesses made yet so all underscores
    for(int i=0; i<word_length; i++) {
        word[i] = '_';
    }
    RemoveIncorrectLength(word_length);
    // Make guesses until game ends
    char guess;
    while(num_lives>=0 && candidates.size()>1) {
        guess = GetBestGuess();
        if(target.find(guess)!=string::npos) {
            UpdateWord(guess, word, target);
            EliminateWithout(word);
        } else {
            EliminateContaining(guess);
            num_lives--;
        }
    }
    GameOver(num_lives>=0);
}



