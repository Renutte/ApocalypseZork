#pragma once

#ifndef __Player__
#define __Player__

#include <string>
#include <list>
#include <vector>
#include <time.h>

#include "entity.h"
#include "room.h"

using namespace std;

class Player : public Entity
{
public:
	Player(const char* name, const char* description, Room* roomToSet);
	void Look() const;
	void Examine() const;
	void Go(string direction_name);
	void Directions() const;
	void Take(string object_name);
	void Open(string object_name);
	void Drop();
	void Inventory();
	void Take(string object_name, string from_object_name);

public:
	Room* room;
	Entity* item_in_hands;
};

#endif