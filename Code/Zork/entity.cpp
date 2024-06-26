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
	can_store = false;
}

Entity::~Entity()
{
	
}

// Change storable permission (player can place items inside)
void Entity::SetStorable(bool storable) {
	can_store = storable;
}

// Change the name of this entity by the provided
void Entity::ChangeNameTo(string new_name) {
	name = new_name;
}

// Change the description of this entity by the provided
void Entity::ChangeDescriptionTo(string new_description) {
	description = new_description;
}

// Return the item that can open this entity
Item* Entity::GetItemProperties() const{
	return opens;
}

// Change locked state
void Entity::SetLockedTo(bool new_state) {
	locked = new_state;
}

// Change unlockable permission
void Entity::SetUnlockable(bool unlockable, bool is_locked, string password_to_set) {
	locked = is_locked;
	can_unlock = unlockable;
	password = password_to_set;
}

// Change pushable permission
// (Pushable entities disappear when pushed)
void Entity::SetPushable(bool pushable, string pushed_description) {
	can_push = pushable;
	text_when_pushed = pushed_description;
}

// Change readable permission
void Entity::SetReadable(bool readable, string read_text) {
	read_description = read_text;
	can_read = readable;
}

// Change activation permission
void Entity::SetActivateable(bool activetable, bool default_state) {
	can_activate = activetable;
	activated = default_state;
}

// Change activated state
void Entity::SetActiveTo(bool activation) {
	activated = activation;
}

// Change the parent of the specified object by other
void Entity::ChangeParentTo(Entity* new_parent)
{
	if (parent != NULL) parent->container.remove(this);
	parent = new_parent;
	if (parent != NULL) parent->container.push_back(this);
}

// Prints the description of the specified child by his name
void Entity::Look(string entity_name) const
{
	cout << endl;
	Entity* entity_to_look = FindChild(entity_name);
	if (entity_to_look != NULL) entity_to_look->Look();
	else cout << "You cant look this object." << endl;
	cout << endl;
}

// Prints the description of this entity
void Entity::Look() const
{
	cout << description << endl;
}

// Returns a specified child by his name
Entity* Entity::FindChild(string entity_name) const {
	for (const auto& entity : container) {
		if ((Same(entity->name, entity_name))) return entity;
	}
	return NULL;
}

// Prints what contains the specified child by his name
void Entity::Examine(string entity_name) const {
	cout << endl;
	if (entity_name == "") cout << "What do you want to examine?" << endl;
	else {
		Entity* entity_to_examine = FindChild(entity_name);
		if (entity_to_examine == NULL) cout << "You dont see any " << B_RED_ << entity_name << RESET_ << " near you." << endl;
		else if (entity_to_examine->can_unlock && entity_to_examine->locked) cout << B_RED_ << entity_to_examine->name << RESET_ << " is locked, you can't examine this." << endl;
		else entity_to_examine->Examine();
	}
	cout << endl;
}

// Prints what contains this entity
void Entity::Examine() const {
	list<string> visibleItems;
	for (auto& entity : container) {
		if (entity->visible) visibleItems.push_back(entity->name); 
	}
	
	if (visibleItems.empty()) {
		if (parent == NULL) cout << "Nothing interesting in " << B_BLUE_ << name << RESET_ << "." << endl;
		else cout << "Nothing interesting in " << B_RED_ << name << RESET_ << "." << endl;
	}
	else {
		cout << "This " << B_BLUE_ << name << RESET_ << " contains a ";
		auto it = visibleItems.begin();
		while (true) {
			cout << B_RED_ << *it << RESET_;
			if (++it == visibleItems.end()) {
				break;
			}
			else if (next(it) == visibleItems.end()) {
				cout << " and a ";
			}
			else {
				cout << ", ";
			}
		}
		cout << "." << endl;
	}
}