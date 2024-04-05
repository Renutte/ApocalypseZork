#include <iostream>
#include "globals.h"
#include "Entity.h"
#include <list>

Entity::Entity(const char* name, const char* description, Entity* parent, bool visible) :
	name(name), description(description), parent(parent), visible(visible)
{
	if (parent != NULL) {
		parent->container.push_back(this);
		//cout << "--- Entity::Entity with name: " << name << " and parent: " << parent->name << ", now parent contains " << parent->container.size() << " objects " << endl;
		//Examine();
	}
}

Entity::Entity(const char* name, const char* description, Entity* parent, bool visible, Item* opens) :
	name(name), description(description), parent(parent), visible(visible), opens(opens)
{
	if (parent != NULL) {
		parent->container.push_back(this);
		//cout << "--- Entity::Entity with name: " << name << " and parent: " << parent->name << ", now parent contains " << parent->container.size() << " objects " << endl;
		//Examine();
	}
}



Entity::~Entity()
{
	
}

void Entity::ChangeParentTo(Entity* new_parent)
{
	if (parent != NULL) parent->container.remove(this);
	parent = new_parent;
	if (parent != NULL) parent->container.push_back(this);
}

void Entity::Look(string entity_name) const
{
	Entity* entity_to_look = FindChild(entity_name);
	if (entity_to_look != NULL) entity_to_look->Look();
	else cout << endl << "I cant look this object" << endl << endl;

}

void Entity::Look() const
{
	//cout << "--- Entity::Look " << endl;
	cout << endl;
	cout << B_RED_ << name << RESET_ << endl;
	cout << description << endl;
	cout << endl;

}

Entity* Entity::FindChild(string entity_name) const {
	for (const auto& entity : container) {
		if (entity->name == entity_name) return entity;
	}
	return NULL;
}

void Entity::Examine(string entity_name) const {
	//cout << "--- Entity::Examine " << endl;
	//
	//cout << "Name: " << name << endl;
	//cout << "Size of container: " << container.size() << endl;

	//for (const auto& entity : container) {
	//	//cout << "--- Entity_container::Examine " << endl;
	//	if (entity->name == entity_name) entity->Look();
	//}

	Entity* entity_to_examine = FindChild(entity_name);
	if (entity_to_examine != NULL) entity_to_examine->Examine();
	else cout << endl << "I cant examine this object" << endl << endl;
}

void Entity::Examine() const {
	cout << endl;
	cout << "This " << B_BLUE_ << name << RESET_ << " contains: ";

	list<string> visibleItems;
	for (auto& entity : container) {
		if (entity->visible) {
			visibleItems.push_back(entity->name);
		}
	}

	if (visibleItems.empty()) {
		cout << B_RED_ << "nothing." << RESET_ << endl;
	}
	else {
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