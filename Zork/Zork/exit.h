#pragma once

#ifndef __Exit__
#define __Exit__

#include <string>
#include <list>
#include <vector>
#include <time.h>

#include "entity.h"
#include "globals.h"

class Room;

using namespace std;

class Exit : public Entity
{
public:
	Exit(Direction direction, Entity* obstruction_object, Room* destination, const char* title, const char* description, Room* room);
	void RemoveObstruction();

public:
	Direction direction;
	Entity* obstruction_object;
	Room* destination;
};

#endif