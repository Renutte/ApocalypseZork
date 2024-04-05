#pragma once

#ifndef __Room__
#define __Room__

#include <string>
#include <list>
#include <vector>
#include <time.h>

#include "entity.h"
#include "exit.h"
#include "globals.h"

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	void SetExit(Direction direction, Entity* obstruction_object, Room* destination, const char* name, const char* description);
	void Look() const;
	Exit* GetExit(Direction direction);
	//Exit GetExitInfo(Direction direction);
	void RemoveObstruction(Direction direction);
	void Directions() const;

public:
	Exit* north_exit;
	Exit* south_exit;
	Exit* east_exit;
	Exit* west_exit;
};

#endif