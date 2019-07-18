// bot.h
// Created by Carter on 7/2/2019.
//

#ifndef HANGMANBOT_BOT_H
#define HANGMANBOT_BOT_H

#include <list>
#include <string>
#include <map>

namespace hbot {
    // Solves a game of Hangman after retrieving the word to guess.
    // Example:
    //  bot my_bot();
    //  my_bot.Run();
    class bot {
    public:
        // Starts a game of Hangman and solves for the word the user inputs.
        void Run();

        void PrintCandidates();

    //private:
        // The dictionary of words to chose from
        std::string dictionary = "words.txt";

        // The shrinking list of words to choose from. If the size of this
        // reaches 1 before the bot runs out of lives, the bot has won.
        std::list<std::string> candidates;

        // Letter frequency table used generate the best letter to guess.
        std::map<char, int> letter_freq;

        int num_lives = 7;

        // Populates candidates with the words in a .txt file.
        // Params:
        //  filename: The name of the file to read
        void InitializeCandidates(std::string& filename);

        // Returns the target word from the user.
        std::string GetTarget();

        // Removes the words from candidates that do not match the length of
        // the word that the user entered.
        // Params:
        //  length: The length of the words to be removed
        void RemoveIncorrectLength(int length);

        // Returns the letter that appears most frequently in the current
        // candidates.
        char GetBestGuess();

        // Updates a character array to match the target string based on the
        // guess char passed.
        // Params:
        //  guess: The letter to identify in target, and place in word[]
        //  word[]: The array to update
        //  target: The string to analyze
        void UpdateWord(char guess, char word[], std::string target);

        // Eliminates words from candidates that contain the char passed.
        // Params:
        //  guess: The letter identified in removed words
        void EliminateContaining(char guess);

        // Eliminates words form candidates that do not match the letters'
        // in word[] so far.
        // Params:
        //  word[]: The array to compare against the words in candidates
        void EliminateWithout(char word[]);

        // Ends the game.
        // Params:
        //  win: Indicator that the bot has either won, or lost the game
        void GameOver(bool win);
    };
}

#endif //HANGMANBOT_BOT_H
