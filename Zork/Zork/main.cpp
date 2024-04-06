#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <conio.h>

#include "globals.h"
#include "world.h"

using namespace std;

int main()
{
    // == For emojis
    SetConsoleOutputCP(CP_UTF8);

    // == Text colors
    cout << RED_ << "Red" << RESET_ << " || ";
    cout << GREEN_ << "Green" << RESET_ << " || ";
    cout << YELLOW_ << "Yellow" << RESET_ << " || ";
    cout << BLUE_ << "Blue" << RESET_ << " || ";
    cout << MAGENTA_ << "Magenta" << RESET_ << " || ";
    cout << CYAN_ << "Cyan" << RESET_ << " || ";
    cout << WHITE_ << "White" << RESET_ << " || ";
    cout << B_BLACK_ << "Bright Black" << RESET_ << " || ";
    cout << B_RED_ << "Bright Red" << RESET_ << " || ";
    cout << B_GREEN_ << "Bright Green" << RESET_ << " || ";
    cout << B_YELLOW_ << "Bright Yellow" << RESET_ << " || ";
    cout << B_BLUE_ << "Bright Blue" << RESET_ << " || ";
    cout << B_MAGENTA_ << "Bright Magenta" << RESET_ << " || ";
    cout << B_CYAN_ << "Bright Cyan" << RESET_ << " || ";
    cout << B_WHITE_ << "Bright White" << RESET_ << endl;

    // == Title
    cout << endl;
    cout << " _____                 _                    _____         _   " << endl;
    cout << "|  _  |___ ___ ___ ___| |_ _ ___ ___ ___   |__   |___ ___| |_ " << endl;
    cout << "|     | . | . |  _| .'| | | | . |_ -| -_|  |   __| . |  _| '_|" << endl;
    cout << "|__|__|  _|___|___|__,|_|_  |  _|___|___|  |_____|___|_| |_,_|" << endl;
    cout << "      |_|               |___|_|                               " << endl;
    cout << endl;
    cout << "By: Daniel Z." << endl;
    cout << endl;

    // == Runtime
    string player_input;
    vector<string> args;
    args.reserve(10);
    vector<string> all_inputs;
    
    World world;

    while (true) {
        if (world.PlayerWin()) {
            cout << EMOJI_TROPHY << " YOU WON " << EMOJI_TROPHY << endl;
            cout << endl;
            break;
        }
        if (world.GetMainPlayer()->IsDead()) {
            cout << EMOJI_SKULL << " YOU DIED " << EMOJI_SKULL << endl;
            break;
        }
        cout << "> ";
        getline(cin, player_input);
        all_inputs.push_back(player_input);
        Tokenize(player_input, args);
        if (args.size() > 0 && Same(args[0], "quit")) break;
        if (world.Tick(args) == false) cout << endl << "I donk understand you, what you want i do?" << endl << endl;
        args.clear();
    }

    cout << "You want to know your stats? (Y/N)" << endl;
    cout << endl;
    cout << "> ";
    getline(cin, player_input);
    if (Same(player_input, "Y") || Same(player_input, "Yes")) {
        cout << endl << "Comands ammount used: " << all_inputs.size() << endl;
        cout << endl << "All inputs:" << endl;
        for (const string& input : all_inputs) {
            cout << input << endl;
        }
    }

    cout << endl << "Thanks for playing :)" << endl;
    return 0;
}
