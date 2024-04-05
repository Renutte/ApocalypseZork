#include <iostream>
#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const char* title, const char* description, Room* roomToSet) :
	Entity(title, description, (Entity*)roomToSet, false)
{
	room = roomToSet;
}

// ----------------------------------------------------
void Player::Look() const
{
	//cout << "--- Player::Look " << endl;
	//parent->Look();
	room->Look();
}

void Player::Directions() const
{
	room->Directions();
}

void Player::Examine() const
{
	/*cout << "--- Player::Examine " << endl;
	cout << "--- Player::Examine room: " << room->name << endl;
	room->parent->Examine();*/
	room->Examine();
}

void Player::Go(string direction_name) {
	Exit* exit = room->GetExit(stringToDirection(direction_name));
	if (exit == NULL) {
		cout << endl;
		cout << " Cant go to this direction " << endl;
		cout << endl;
		return;
	} else if (exit->obstruction_object != NULL) {
		cout << endl;
		cout << " Cant go to this direction, is obstructed by " << B_RED_ << exit->obstruction_object->name << RESET_ << endl;
		cout << endl;
		return;
	}
	room = exit->destination;
	ChangeParentTo(exit->destination);
	Look();
}

void Player::Open(string object_name) {
	cout << endl;
	Entity* entity_to_open = room->FindChild(object_name);
	Item* item_that_opens = entity_to_open->opens;

	if (item_in_hands != NULL) cout << item_in_hands << endl;
	if (entity_to_open != NULL) cout << entity_to_open << endl;
	if (item_that_opens != NULL) cout << item_that_opens << endl;

	if (item_in_hands != NULL && entity_to_open != NULL && item_that_opens != NULL) {
		if (item_in_hands == item_that_opens) {
			room->UnlockExit(entity_to_open);
			entity_to_open->ChangeParentTo(NULL);
			delete entity_to_open;
			cout << "The " << B_RED_ << object_name << RESET_ << " has been opened. I have a new way now." << endl;
		}
		else cout << "The " << B_RED_ << object_name << RESET_ << " dosent open with " << B_RED_ << item_in_hands->name << RESET_ << endl;
	}
	//else {
	//	item_in_hands = room->FindChild(object_name);
	//	if (item_in_hands == NULL/* || item_in_hands->GetItem() == NULL*/) cout << "You cant pick this up." << endl;
	//	else {
	//		item_in_hands->ChangeParentTo(this);
	//		cout << "You picked up: " << B_RED_ << item_in_hands->name << RESET_ << endl;
	//	}
	//}
	//cout << endl;
}

void Player::Push(string object_name) {
	cout << endl;
	Entity* entity_to_push = room->FindChild(object_name);
	bool can_push_entity = entity_to_push->can_push;

	if (entity_to_push != NULL && can_push_entity) {
		if (item_in_hands == NULL) {
			room->UnlockExit(entity_to_push);
			entity_to_push->ChangeParentTo(NULL);
			delete entity_to_push;
			cout << "The " << B_RED_ << object_name << RESET_ << " has been pushed. I have a new way now." << endl;
		}
		else cout << "I cant push with objects in hands. " << endl;
	}
	else {
		cout << "I cant push this object. " << endl;
	}
	cout <<endl;
}

void Player::Take(string object_name) {
	cout << endl;
	if (item_in_hands != NULL) cout << "You are already holding: " << B_RED_ << item_in_hands->name << RESET_ << endl;
	else {
		Entity* object_to_take = room->FindChild(object_name);
		if (object_to_take == NULL || object_to_take->opens == NULL) cout << "You cant pick this up." << endl;
		else {
			item_in_hands = object_to_take;
			item_in_hands->ChangeParentTo(this);
			cout << "You picked up: " << B_RED_ << item_in_hands->name << RESET_ << endl;
		}
	}
	cout << endl;
}

void Player::Take(string object_name, string from_object_name) {
	cout << endl;
	if (item_in_hands != NULL) cout << "You are already holding: " << B_RED_ << item_in_hands->name << RESET_ << endl;
	else {
		Entity* from_object = room->FindChild(from_object_name);
		item_in_hands = from_object->FindChild(object_name);
		if (item_in_hands == NULL) cout << "You cant pick this up." << endl;
		else {
			item_in_hands->ChangeParentTo(this);
			cout << "You picked up: " << B_RED_ << item_in_hands->name << RESET_ << endl;
		}
	}
	cout << endl;
}


void Player::Drop() {
	cout << endl;
	if (item_in_hands == NULL) cout << "You are not holding anything." << endl;
	else {
		cout << "You dropped: " << B_RED_ << item_in_hands->name << RESET_ << endl;
		item_in_hands->ChangeParentTo(room);
		item_in_hands = NULL;
	}
	cout << endl;
}

void Player::Inventory() {
	cout << endl;
	if (item_in_hands == NULL) cout << "You are not holding anything." << endl;
	else {
		cout << "You are holding: " << B_RED_ << item_in_hands->name << RESET_ << endl;
		cout << item_in_hands->description << endl;
	}
	cout << endl;
}