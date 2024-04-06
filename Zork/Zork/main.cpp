#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "globals.h"
#include "world.h"

using namespace std;

#define BACKSPACE "\033[D\033[K"

// -------------------------------------------------
int main()
{
    char key;
    string player_input;
    vector<string> args;
    args.reserve(10);

    cout << RED_ << "Red" << RESET_ << endl;
    cout << GREEN_ << "Green" << RESET_ << endl;
    cout << YELLOW_ << "Yellow" << RESET_ << endl;
    cout << BLUE_ << "Blue" << RESET_ << endl;
    cout << MAGENTA_ << "Magenta" << RESET_ << endl;
    cout << CYAN_ << "Cyan" << RESET_ << endl;
    cout << WHITE_ << "White" << RESET_ << endl;
    cout << B_BLACK_ << "Bright Black" << RESET_ << endl;
    cout << B_RED_ << "Bright Red" << RESET_ << endl;
    cout << B_GREEN_ << "Bright Green" << RESET_ << endl;
    cout << B_YELLOW_ << "Bright Yellow" << RESET_ << endl;
    cout << B_BLUE_ << "Bright Blue" << RESET_ << endl;
    cout << B_MAGENTA_ << "Bright Magenta" << RESET_ << endl;
    cout << B_CYAN_ << "Bright Cyan" << RESET_ << endl;
    cout << B_WHITE_ << "Bright White" << RESET_ << endl;

    cout << endl;
    cout << " _____                 _                    _____         _   " << endl;
    cout << "|  _  |___ ___ ___ ___| |_ _ ___ ___ ___   |__   |___ ___| |_ " << endl;
    cout << "|     | . | . |  _| .'| | | | . |_ -| -_|  |   __| . |  _| '_|" << endl;
    cout << "|__|__|  _|___|___|__,|_|_  |  _|___|___|  |_____|___|_| |_,_|" << endl;
    cout << "      |_|               |___|_|                               " << endl;
    cout << endl;
    cout << "By: Daniel Z." << endl;
    cout << endl;

    World world;

    while (true) {
        cout << "> ";
        getline(cin, player_input);
        Tokenize(player_input, args);
        if (args.size() > 0 && Same(args[0], "quit")) break;
        if (world.Tick(args) == false) cout << endl << "I donk understand you, what you want i do?" << endl << endl;
        args.clear();
    }

    cout << endl << "Thanks for playing :)" << endl;
    return 0;
}
