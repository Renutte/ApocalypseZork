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
    //cout << RED_ << "Red" << RESET_ << " || ";
    //cout << GREEN_ << "Green" << RESET_ << " || ";
    //cout << YELLOW_ << "Yellow" << RESET_ << " || ";
    //cout << BLUE_ << "Blue" << RESET_ << " || ";
    //cout << MAGENTA_ << "Magenta" << RESET_ << " || ";
    //cout << CYAN_ << "Cyan" << RESET_ << " || ";
    //cout << WHITE_ << "White" << RESET_ << " || ";
    //cout << B_BLACK_ << "Bright Black" << RESET_ << " || ";
    //cout << B_RED_ << "Bright Red" << RESET_ << " || ";
    //cout << B_GREEN_ << "Bright Green" << RESET_ << " || ";
    //cout << B_YELLOW_ << "Bright Yellow" << RESET_ << " || ";
    //cout << B_BLUE_ << "Bright Blue" << RESET_ << " || ";
    //cout << B_MAGENTA_ << "Bright Magenta" << RESET_ << " || ";
    //cout << B_CYAN_ << "Bright Cyan" << RESET_ << " || ";
    //cout << B_WHITE_ << "Bright White" << RESET_ << endl;

    // == Title
    cout << B_WHITE_;
    cout << endl;
    cout << " _____                 _                    _____         _   " << endl;
    cout << "|  _  |___ ___ ___ ___| |_ _ ___ ___ ___   |__   |___ ___| |_ " << endl;
    cout << "|     | . | . |  _| .'| | | | . |_ -| -_|  |   __| . |  _| '_|" << endl;
    cout << "|__|__|  _|___|___|__,|_|_  |  _|___|___|  |_____|___|_| |_,_|" << endl;
    cout << "      |_|               |___|_|                               " << endl;
    cout << endl;
    cout << "By: Daniel Z." << endl;
    cout << endl;
    cout << RESET_;

    // == Lore
    //cout << B_WHITE_;
    cout << "You are wandering through a wasteland, thirsty and with low oxygen levels..." << endl;
    cout << "Your objective is to find a source of water." << endl;
    cout << "In the distance, you spot a cave and decide to enter." << endl;
    cout << "Inside the cave, you discover an abandoned settlement." << endl;
    cout << "You decide to explore and see if you find anything interesting." << endl;

    //cout << RESET_;

    // == Runtime
    string player_input;
    vector<string> args;
    args.reserve(10);
    vector<string> all_inputs;
    
    World world;
    bool restart_game = true;

    world.player->PrintRoomInfo();
    
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
        cout << B_BLACK_;
        cout << "> ";
        getline(cin, player_input);
        cout << RESET_;
        all_inputs.push_back(player_input);
        Tokenize(player_input, args);
        if (args.size() > 0 && Same(args[0], "quit")) break;
        world.ProcessInput(args);
        args.clear();
    }

    // == Check stats
    cout << "You want to know your stats? (Y/N)" << endl;
    cout << endl;
    cout << "> ";
    getline(cin, player_input);
    if (Same(player_input, "Y") || Same(player_input, "Yes")) {
        cout << endl << "Commands amount used: " << all_inputs.size() << endl;
        cout << endl << "All inputs:" << endl;
        for (const string& input : all_inputs) {
            cout << input << endl;
        }
    }

    //// == Restart game
    //cout << endl << "You want to restart the game? (Y/N)" << endl;
    //cout << endl;
    //cout << "> ";
    //getline(cin, player_input);
    //if (Same(player_input, "Y") || Same(player_input, "Yes")) {
    //    main();
    //    all_inputs.clear();
    //}

    // == Final text
    cout << endl << "Thanks for playing :)" << endl;
    return 0;
}
