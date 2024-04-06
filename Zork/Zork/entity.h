#pragma once

#ifndef __Entity__
#define __Entity__

#include <string>
#include <list>
#include <vector>

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
	void ChangeNameTo(string new_name);
	void Look() const;
	void Examine(string entity_name) const;
	void Examine() const;
	Entity* FindChild(string entity_name) const;
	void Look(string entity_name) const;
	void SetPushable(bool pushable);
	void SetReadable(bool readable, string read_text);
	void SetActiveTo(bool activation);
	void SetActivateable(bool activetable, bool default_state);
	void SetLockedTo(bool new_state);
	void SetUnlockable(bool unlockable, bool is_locked, string password_to_set);
	Item* GetItemProperties();
	void ChangeDescriptionTo(string new_description);

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
	// Is a readable object (Note)
	bool can_read;
	string read_description;
	// Is a activable object (Switch)
	bool can_activate;
	bool activated;
	// Is a unlockable object (Safe box)
	bool can_unlock;
	bool locked;
	string password;
};

#endif