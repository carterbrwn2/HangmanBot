// main.cpp
// Created by Carter on 7/2/2019.
//

#include <iostream>
#include "bot.h"
using namespace hbot;
using namespace std;

int main() {
    bot my_bot;
    string filename = "words.txt";
    my_bot.InitializeCandidates(filename);
    my_bot.RemoveIncorrectLength(4);
    my_bot.PrintCandidates();
    return 0;
}
