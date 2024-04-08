#pragma once

#ifndef __Room__
#define __Room__

#include <string>
#include <list>
#include <vector>

#include "entity.h"
#include "exit.h"
#include "globals.h"

using namespace std;

class Room : public Entity
{
public:
	Room(const char* name, const char* description);
	void SetExit(Direction direction, Entity* obstruction_object, Room* destination, const char* name, const char* description);
	void Look();
	Exit* GetExit(Direction direction);
	//Exit GetExitInfo(Direction direction);
	void RemoveObstruction(Direction direction);
	void Directions();
	void UnlockExit(Entity* obstruction_object);

public:
	Exit* north_exit;
	Exit* south_exit;
	Exit* east_exit;
	Exit* west_exit;
	bool visited;
};

#endif