#include <iostream>
#include "globals.h"
#include "Entity.h"
#include <list>

Entity::Entity(const char* name, const char* description, Entity* parent, bool visible) :
	name(name), description(description), parent(parent), visible(visible)
{
	if (parent != NULL) parent->container.push_back(this);
	can_push = false;
	can_activate = false;
	activated = false;
	can_unlock = false;
	password = "";
}

Entity::Entity(const char* name, const char* description, Entity* parent, bool visible, Item* opens) :
	name(name), description(description), parent(parent), visible(visible), opens(opens)
{
	if (parent != NULL) parent->container.push_back(this); 
	can_push = false;
	can_activate = false;
	activated = false;
	can_unlock = false;
	password = "";
}

Entity::~Entity()
{
	
}

void Entity::ChangeNameTo(string new_name) {
	name = new_name;
}

void Entity::ChangeDescriptionTo(string new_description) {
	description = new_description;
}

Item* Entity::GetItemProperties() {
	return opens;
}

void Entity::SetLockedTo(bool new_state) {
	locked = new_state;
}
void Entity::SetUnlockable(bool unlockable, bool is_locked, string password_to_set) {
	locked = is_locked;
	can_unlock = unlockable;
	password = password_to_set;
}

// Pushable entities disappear when pushed
void Entity::SetPushable(bool pushable) {
	can_push = pushable;
}

void Entity::SetReadable(bool readable, string read_text) {
	read_description = read_text;
	can_read = readable;
}


void Entity::SetActivateable(bool activetable, bool default_state) {
	can_activate = activetable;
	activated = default_state;
}

void Entity::SetActiveTo(bool activation) {
	activated = activation;
}

void Entity::ChangeParentTo(Entity* new_parent)
{
	if (parent != NULL) parent->container.remove(this);
	parent = new_parent;
	if (parent != NULL) parent->container.push_back(this);
}

void Entity::Look(string entity_name) const
{
	cout << endl;
	Entity* entity_to_look = FindChild(entity_name);
	if (entity_to_look != NULL) entity_to_look->Look();
	else cout << "I cant look this object." << endl;
	cout << endl;
}

void Entity::Look() const
{
	cout << B_RED_ << name << RESET_ << endl;
	cout << description << endl;
}

Entity* Entity::FindChild(string entity_name) const {
	for (const auto& entity : container) {
		if ((Same(entity->name, entity_name))) return entity;
	}
	return NULL;
}

void Entity::Examine(string entity_name) const {
	if (entity_name == "") cout << "What you want to examine?" << endl;
	else {
		Entity* entity_to_examine = FindChild(entity_name);
		if (entity_to_examine == NULL) cout << endl << "I dont see any " << B_RED_ << entity_name << RESET_ << " near me" << endl << endl;
		else if (entity_to_examine->can_unlock && entity_to_examine->locked) cout << endl << B_RED_ << entity_to_examine->name << RESET_ << " is locked, you cant examine this." << endl << endl;
		else entity_to_examine->Examine();
	}
}

void Entity::Examine() const {
	cout << endl;

	list<string> visibleItems;
	for (auto& entity : container) {
		if (entity->visible) visibleItems.push_back(entity->name); 
	}
	
	if (visibleItems.empty()) cout << "Nothing interesting in " << B_RED_ << name << RESET_ << endl; 
	else {
		cout << "This " << B_BLUE_ << name << RESET_ << " contains: ";
		auto it = visibleItems.begin();
		while (true) {
			cout << B_RED_ << *it << RESET_;
			if (++it == visibleItems.end()) {
				break;
			}
			else if (next(it) == visibleItems.end()) {
				cout << " and ";
			}
			else {
				cout << ", ";
			}
		}
		cout << "." << endl;
	}
	cout << endl;
}