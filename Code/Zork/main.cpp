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

    // == Title
    cout << B_RED_;
    cout << endl;
    cout << " _____                 _                    _____         _   " << endl;
    cout << "|  _  |___ ___ ___ ___| |_ _ ___ ___ ___   |__   |___ ___| |_ " << endl;
    cout << "|     | . | . |  _| .'| | | | . |_ -| -_|  |   __| . |  _| '_|" << endl;
    cout << "|__|__|  _|___|___|__,|_|_  |  _|___|___|  |_____|___|_| |_,_|" << endl;
    cout << "      |_|               |___|_|                               " << endl;
    cout << RESET_;
    cout << B_WHITE_;
    cout << endl;
    cout << "By: Daniel Z." << endl;
    cout << endl << "______________________________________________________________" << endl;
    cout << endl;
    cout << RESET_;

    // == Lore
    cout << B_BLACK_ "INTRODUCTION: " RESET_ << endl << endl;
    cout << "It is the year 2023. After a nuclear and biological war, the air has become unbreathable." << endl;
    cout << "You find yourself wandering through a desolate wasteland, thirsty and with your oxygen tank running low." << endl;
    cout << "Your objective is to find a source of water." << endl;
    cout << "In the distance, you spot a cave and decide to venture inside." << endl;
    cout << "As you explore, you discover an abandoned settlement and decide to check it out, hoping to find water." << endl;
    cout << endl;
    cout << B_YELLOW_ "WARNING: " B_BLACK_;
    cout << "Movement consumes oxygen, don't waste it by exploring unnecessarily." << endl;
    cout << RESET_;

    // == Runtime
    string player_input;
    vector<string> args;
    args.reserve(10);
    vector<string> all_inputs;
    World world;

    // Initial information Look() and Oxygen()
    world.player->PrintOxygenAndRoomInfo();
    
    // Read inputs
    while (true) {
        // If player finished and win
        if (world.PlayerWin()) {
            cout << EMOJI_TROPHY << " YOU WON " << EMOJI_TROPHY << endl;
            cout << endl;
            break;
        }
        // If player dead
        if (world.GetMainPlayer()->IsDead()) {
            cout << EMOJI_SKULL << " YOU DIED " << EMOJI_SKULL << endl;
            break;
        }
        // If player still alive and dont win
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
        cout << endl << " ==>> All inputs:" << endl;
        cout << endl;
        for (const string& input : all_inputs) {
            cout << input << endl;
        }
        cout << endl << " ==>> Commands amount used: " << all_inputs.size() << endl;
    }

    // == Final text
    cout << endl << "Thanks for playing :)" << endl;
    return 0;
}
