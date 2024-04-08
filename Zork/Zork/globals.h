#pragma once

#ifndef __Globals__
#define __Globals__

#define BLACK_ "\033[0;30m"
#define RED_ "\033[0;31m"
#define GREEN_ "\033[0;32m"
#define YELLOW_ "\033[0;33m"
#define BLUE_ "\033[0;34m"
#define MAGENTA_ "\033[0;35m"
#define CYAN_ "\033[0;36m"
#define WHITE_ "\033[0;37m"

#define B_BLACK_ "\033[1;30m"
#define B_RED_ "\033[1;31m"
#define B_GREEN_ "\033[1;32m"
#define B_YELLOW_ "\033[1;33m"
#define B_BLUE_ "\033[1;34m"
#define B_MAGENTA_ "\033[1;35m"
#define B_CYAN_ "\033[1;36m"
#define B_WHITE_ "\033[1;37m"

#define RESET_ "\033[0m"

#define EMOJI_SKULL "\xF0\x9F\x92\x80"
#define EMOJI_TROPHY "\xF0\x9F\x8F\x86"

#include <string>
#include <list>
#include <vector>
#include <Windows.h>

using namespace std;

enum Direction
{
	SOUTH,
	EAST,
	NORTH,
	WEST,
	ERROR_DIRECTION
};

string directionToString(Direction dir);
bool Same(const string& a, const string& b);
bool Same(const char* a, const string& b);
bool Same(const string& a, const char* b);
int Roll(int min, int max);
void Tokenize(const string& line, vector<string>& arguments);
string ConcatenateArgs(const vector<string>& args, size_t startIdx);
Direction stringToDirection(const string& str);
string combineValues(const vector<string>& args, const string& startString, const string& endString);

#endif