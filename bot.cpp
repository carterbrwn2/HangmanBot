// bot.cpp
// Created by Carter on 7/2/2019.
//

#include "bot.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace hbot;
using namespace std;

void bot::Run() {
    bool play = true;
    while(play) {
        InitializeCandidates(dictionary);
        string target = GetTarget();
        int word_length = target.length();
        // An array to model the work towards the target word
        vector<char> word;
        word.reserve(word_length);
        // Initialize word array - no guesses made yet so all underscores
        for (int i = 0; i < word_length; ++i) {
            word.push_back('_');
        }
        RemoveIncorrectLength(word_length);
        // Make guesses until game ends
        char guess;
        while (num_lives >= 0 && candidates.size() > 1) {
            guess = GetBestGuess();
            cout << "The letter guessed was: " << guess << "\n";
            if (target.find(guess) != string::npos) {
                UpdateWord(guess, word, target);
                // Show the update
                for (auto ch : word) {
                    cout << ch << " ";
                }
                cout << "\n";
                EliminateWithout(word);
            } else {
                EliminateContaining(guess);
                num_lives--;
            }
        }
        GameOver(num_lives>=0);

        // Ask user if they'd like to play again
        cout << "Play again? (y/n): ";
        char ans;
        cin >> ans;
        if (ans == 'n') {
            play = false;
        } else {
            candidates.clear();
            guesses.clear();
            num_lives = 7;
            cout << "\n";
        }
    }

}

// Text file format is assumed to be one word per line,
// with no newline at the end of the document.
// The filename is assumed to be in the format
// "filename.txt"
void bot::InitializeCandidates(string& filename) {
    string word;
    ifstream words_file;
    words_file.open(filename);
    if (words_file.is_open()) {
        while (getline(words_file, word)) {
            candidates.push_back(word);
        }
        words_file.close();
    } else {
        cout << "Unable to open " << filename << "\n";
    }
}

// Helper Function: Prints candidates
void bot::PrintCandidates() {
    for (auto const& i : candidates) {
        cout << i + "\n";
    }
}

// Current implementation:
// Get target string from user via command line
string bot::GetTarget() {
    string target;
    cout << "Choose your word:\n";
    cin >> target;
    return target;
}

// Iterates over candidates and erases the members
// that do not match the passed length
void bot::RemoveIncorrectLength(int length) {
    auto i = candidates.begin();
    // Compare each word to target length,
    // remove if necessary
    while (i != candidates.end()) {
        string curr_word = *i;
        int curr_word_length = curr_word.length();
        bool is_correct_length = curr_word_length == length;
        if (!is_correct_length) {
            candidates.erase(i++);
        }
        else {
            ++i;
        }
    }
}

// Populates the letter_freq map with each char frequency
// from all the strings remaining in candidates
char bot::GetBestGuess() {
    // Fill letter_freq map
    string temp;
    for (auto const& i : candidates) {
        temp = i;
        for (char& ch : temp) {
            letter_freq[ch]++;
        }
    }
    // Get the char that appeared most often
    char guess = ' ';
    int max_val = -1;
    for (auto const& x : letter_freq) {
        // The second condition checks if the char has been guessed
        if (x.second > max_val && guesses.find(x.first) == guesses.end()) {
            guess = x.first;
            max_val = x.second;
        }
    }
    letter_freq.clear();
    guesses.insert(guess);
    return guess;
}

// Iterates over the target word and updates the word vector,
// replacing chars as they are found in the target
void bot::UpdateWord(char guess, vector<char>& word, string& target) {
    for (int i = 0; i < target.length(); ++i) {
        if (target[i] == guess) {
            word[i] = guess;
        }
    }
}

// Iterates over candidates and removes strings
// that contain char guess
void bot::EliminateContaining(char guess) {
    auto i = candidates.begin();
    // See if each string contains the char,
    // remove if it does
    while (i != candidates.end()) {
        string curr_word = *i;
        if (curr_word.find(guess) != string::npos) {
            candidates.erase(i++);
        }
        else {
            ++i;
        }
    }
}

// Iterates over candidates and removes strings
// that do not match the current word vector
void bot::EliminateWithout(vector<char>& word) {
    auto i = candidates.begin();
    // See if each string matches the vector,
    // remove if it doesn't
    while (i != candidates.end()) {
        string curr_word = *i;
        bool matches = true;
        int j = 0;
        while (matches && j < word.size()) {
            if ((word[j] != '_') && (word[j] != curr_word[j])) {
                matches = false;
            } else {
                ++j;
            }
        }
        if (!matches) {
            candidates.erase(i++);
        }
        else {
            ++i;
        }
    }
}

// Prints a message to the screen ending the game
void bot::GameOver(bool win) {
    if (win) {
        cout << "\nThe bot has won\n";
        cout << "The word was: " << candidates.front() << "\n" << endl;
    } else {
        cout << "\nYou have won\n";
        cout << "The bot narrowed it down to, "
                "or was going to next guess: \n";
        PrintCandidates();
        cout << endl;
    }
}
