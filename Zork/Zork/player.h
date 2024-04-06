#pragma once

#ifndef __Player__
#define __Player__

#include <string>
#include <list>
#include <vector>

#include "entity.h"
#include "room.h"

using namespace std;

class Player : public Entity
{
public:
	Player(const char* name, const char* description, Room* roomToSet);
	void Look() const;
	void Examine() const;
	void Oxygen();
	bool IsDead();
	void Go(string direction_name);
	void Directions() const;
	void Take(string object_name);
	void Open(string object_name);
	void Drop();
	void Inventory();
	void Take(string object_name, string from_object_name);
	void Push(string object_name);
	void Read(string object_name);
	void Activate(string object_name);
	void Unlock(string object_name);
	void Use(string object_name);
	void SetRemainingOxygen(int new_oxygen);
	void SetOxygenLoosedPerMovement(int new_oxygen);

public:
	Room* room;
	Entity* item_in_hands;
	int oxygen_remaining;
	int oxygen_loosed_per_movement;
	bool dead;
};

#endif