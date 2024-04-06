#pragma once

#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <vector>

#include "player.h"

using namespace std;

class World
{
public:
	World();
	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	Player* GetMainPlayer();
	bool PlayerWin();

private:
	Player* player;
	Room* finishRoom;
	Entity* powerSource;
};

#endif