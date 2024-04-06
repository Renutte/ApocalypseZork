#pragma once

#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <vector>
#include <time.h>

#include "player.h"

using namespace std;

class World
{
public:
	World();
	bool Tick(vector<string>& args);
	bool ParseCommand(vector<string>& args);
	Player* GetMainPlayer();

private:
	Player* player;

};

#endif