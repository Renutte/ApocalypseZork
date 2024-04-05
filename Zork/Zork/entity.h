#pragma once

#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>
#include <vector>
#include <time.h>

//#include "item.h"

using namespace std;

class Item;

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent, bool visible);
	Entity(const char* name, const char* description, Entity* parent, bool visible, Item* opens);
	~Entity();
	void ChangeParentTo(Entity* new_parent);
	void Look() const;
	void Examine(string entity_name) const;
	void Examine() const;
	Entity* FindChild(string entity_name) const;
	void Look(string entity_name) const;
	void SetPushable(bool pushable);
	//void Push();

public:
	string name;
	string description;
	Entity* parent;
	list<Entity*> container;
	bool visible;
	Item* opens;

// Entity properties
public:
	// Is a movable object (Rock)
	bool can_push;
	// Is a activable object (Switch)
	bool can_activate;
	bool activated;
	// Is a unlockable object (Safe box)
	bool can_unlock;
	string password;
};

#endif