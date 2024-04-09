#include "globals.h"
#include <algorithm>
#include <cctype>

// Return true if the two strings provided are the same (for capital letters comparaisons)
bool Same(const string& a, const string& b)
{
	return _stricmp(a.c_str(), b.c_str()) == 0;
}

bool Same(const char* a, const string& b)
{
	return _stricmp(a, b.c_str()) == 0;
}

bool Same(const string& a, const char* b)
{
	return _stricmp(a.c_str(), b) == 0;
}

// Parse the direction to a string
string directionToString(Direction dir) {
	switch (dir) {
	case SOUTH:
		return "South";
	case EAST:
		return "East";
	case NORTH:
		return "North";
	case WEST:
		return "West";
	default:
		return "Error";
	}
}

// Parse the string to a direction
Direction stringToDirection(const string& str) {
	string lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return tolower(c); });

	if (lowerStr == "south") {
		return SOUTH;
	}
	else if (lowerStr == "east") {
		return EAST;
	}
	else if (lowerStr == "north") {
		return NORTH;
	}
	else if (lowerStr == "west") {
		return WEST;
	}
	else {
		return ERROR_DIRECTION;
	}
}

// Splits the provided string and returned in "arguments"
void Tokenize(const string& line, vector<string>& arguments)
{
	const char* str = line.c_str();

	do
	{
		const char* begin = str;

		while (*str != ' ' && *str)
			str++;

		arguments.push_back(string(begin, str));
	} while (0 != *str++);
}

// Concatenate arguments of a vector from X value of the vector to X value of the vector
// Example: args="take Orange Key from Corpse" -> combineValues(args, "take", "Corpse") returns "Orange Key"
string combineValues(const vector<string>& args, const string& startString, const string& endString) {
	size_t startIndex = 0;
	size_t endIndex = args.size();

	// Start index
	if (!startString.empty()) {
		vector<string>::const_iterator startIt = find_if(args.begin(), args.end(), [&](const string& s) {
			return Same(s, startString);
			});
		if (startIt != args.end()) startIndex = distance(args.begin(), startIt) + 1;
		else return "";
	}

	// Finish index
	if (!endString.empty()) {
		vector<string>::const_iterator endIt = find_if(args.begin() + startIndex, args.end(), [&](const string& s) {
			return Same(s, endString);
			});
		if (endIt != args.end()) endIndex = distance(args.begin(), endIt);
		else return "";
	}

	// Combine values between
	string combinedValue;
	for (size_t i = startIndex; i < endIndex; ++i) {
		combinedValue += args[i];
		if (i != endIndex - 1) combinedValue += " ";
	}
	return combinedValue;
}