#include <iostream>
#include <string>
#include <vector>
#include <conio.h>

#include "globals.h"
#include "room.h"
#include "exit.h"
#include "item.h"
#include "player.h"

Player::Player(const char* title, const char* description, Room* roomToSet) :
	Entity(title, description, (Entity*)roomToSet, false)
{
	room = roomToSet;
	dead = false;
}

// ----------------------------------------------------
void Player::Look() const
{
	cout << endl;
	room->Look();	
	cout << endl;
}

void Player::Directions() const
{
	room->Directions();
}

void Player::Examine() const
{
	room->Examine();
}

void Player::SetRemainingOxygen(int new_oxygen) {
	oxygen_remaining = new_oxygen;
}
void Player::SetOxygenLoosedPerMovement(int new_oxygen) {
	oxygen_loosed_per_movement = new_oxygen;
}

void Player::Oxygen() {
	cout << endl;
	if (oxygen_remaining > 0) cout << "My oxygen levels are at " << B_YELLOW_ << oxygen_remaining << "%" << RESET_ << endl;
	else {
		cout << "There is no more oxygen in tank" << endl;
		dead = true;
	}
	cout << endl;
}

bool Player::IsDead() {
	return dead;
}

void Player::Use(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to use?" << endl;
	else {
		if (item_in_hands == NULL || !Same(object_name, item_in_hands->name)) cout << "You are not holding something i can use" << endl;
		else {
			if (item_in_hands->GetItemProperties() != NULL && item_in_hands->GetItemProperties()->oxygen_provided > 0) {
				cout << "I refilled my oxygen with this " << B_RED_ << item_in_hands->name << RESET_ << endl;
				SetRemainingOxygen(item_in_hands->GetItemProperties()->oxygen_provided + oxygen_remaining);
				Oxygen();
				item_in_hands->GetItemProperties()->oxygen_provided = 0;
				item_in_hands->ChangeNameTo("Empty" + item_in_hands->name);
				item_in_hands->ChangeDescriptionTo("A tank with 0% of Oxygen.");
				return;
			}
			else {
				cout << "I cant use this " << B_RED_ << item_in_hands->name << RESET_ << endl;
			}
		}
	}
	cout << endl;
}

void Player::Go(string direction_name) {
	if (direction_name == "") cout << endl << "Where you want to go?" << endl << endl;
	else {
		if (stringToDirection(direction_name) == ERROR_DIRECTION) cout << endl << "Cant recognize this direction " << endl << endl;
		else {
			Exit* exit = room->GetExit(stringToDirection(direction_name));
			if (exit == NULL) {
				cout << endl << "Cant go to this direction " << endl << endl;
			}
			else if (exit->obstruction_object != NULL) {
				cout << endl << "Cant go to this direction, is obstructed by " << B_RED_ << exit->obstruction_object->name << RESET_ << endl << endl;
			}
			else {
				room = exit->destination;
				ChangeParentTo(exit->destination);
				cout << endl;
				room->Look();
				SetRemainingOxygen(oxygen_remaining - oxygen_loosed_per_movement);
				Oxygen();
			}
		}
	}
}

void Player::Open(string object_name) {
	cout << endl;
	if (object_name == "") cout <<  "What you want to open?" << endl;
	else {
		Entity* entity_to_open = room->FindChild(object_name);
		if (entity_to_open == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " near me" << endl;
		else {
			Item* item_that_opens = entity_to_open->opens;
			if (item_that_opens != NULL) {
				if (item_in_hands != NULL) {
					if (item_in_hands == item_that_opens) {
						room->UnlockExit(entity_to_open);
						entity_to_open->ChangeParentTo(NULL);
						cout << "The " << B_RED_ << entity_to_open->name << RESET_ << " has been opened. I have a new way now." << endl;
						delete entity_to_open;
					}
					else cout << "The " << B_RED_ << entity_to_open->name << RESET_ << " dosent open with " << B_RED_ << item_in_hands->name << RESET_ << endl;
				}
				else {
					cout << "I need something to open this" << endl;
				}
			}
			else {
				cout << "It is not a thing that i can open" << endl;
			}
		}
	}
	cout << endl;
}

void Player::Activate(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to activate?" << endl;
	else {
		Entity* entity_to_activate = room->FindChild(object_name);
		if (entity_to_activate == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " near me" << endl;
		else if (entity_to_activate->can_activate == false) cout << "I cant activate the " << entity_to_activate->name << endl;
		else {
			if (entity_to_activate->activated) cout << entity_to_activate->name << RESET_ << " already activated." << endl;
			else {
				entity_to_activate->SetActiveTo(true);
				cout << "You turned " << B_RED_ << entity_to_activate->name << RESET_ << " ON" << endl;
			}
		}
	}
	cout << endl;
}

void Player::Read(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to read?" << endl;
	else {
		Entity* entity_to_read = room->FindChild(object_name);
		if (item_in_hands != NULL && item_in_hands->can_read && (object_name == "" || Same(item_in_hands->name, object_name))) entity_to_read = item_in_hands;
		if (entity_to_read == NULL) cout << "This object have not text i can read." << endl;
		else cout << entity_to_read->read_description << endl;
	}
	cout << endl;
}

void Player::Unlock(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to unlock?" << endl;
	else {
		Entity* entity_to_unlock = room->FindChild(object_name);
		if (entity_to_unlock == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " near me" << endl;
		else {
			if (entity_to_unlock->can_unlock) {
				if (entity_to_unlock->locked) {
					cout << "Type code: ";
					string player_input;
					getline(cin, player_input);
					if (Same(player_input, entity_to_unlock->password)) {
						entity_to_unlock->SetLockedTo(false);
						cout << "The password is correct! " << B_RED_ << entity_to_unlock->name << RESET_ << " is now unlocked." << endl;
					}
					else cout << "The password is not correct... Maybe if i try with other i can unlock it" << endl;
				} else cout << B_RED_ << entity_to_unlock->name << RESET_ << " already unlocked" << endl;
			}
			else cout << B_RED_ << entity_to_unlock->name << RESET_ << " is not unclockable" << endl;
		}
		cout << endl;
	}
}

void Player::Push(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to push?" << endl;
	else {
		Entity* entity_to_push = room->FindChild(object_name);
		if (entity_to_push == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " near me" << endl;
		else {
			bool can_push_entity = entity_to_push->can_push;
			if (entity_to_push != NULL && can_push_entity) {
				if (item_in_hands == NULL) {
					room->UnlockExit(entity_to_push);
					entity_to_push->ChangeParentTo(NULL);
					cout << "The " << B_RED_ << entity_to_push->name << RESET_ << " has been pushed. I have a new way now." << endl;
					delete entity_to_push;
				}
				else cout << "I cant push with objects in hands. " << endl;
			}
			else {
				cout << "I cant push this object. " << endl;
			}
		}
	}
	cout <<endl;
}

void Player::Take(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What you want to take?" << endl;
	else {
		if (item_in_hands != NULL) cout << "You are already holding: " << B_RED_ << item_in_hands->name << RESET_ << endl;
		else {
			Entity* object_to_take = room->FindChild(object_name);
			if (object_to_take == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " near me" << endl;
			else if (object_to_take->opens == NULL) cout << "You cant pick this up." << endl;
			else {
				item_in_hands = object_to_take;
				item_in_hands->ChangeParentTo(this);
				cout << "You picked up: " << B_RED_ << item_in_hands->name << RESET_ << endl;
			}
		}
	}
	cout << endl;
}

void Player::Take(string object_name, string from_object_name) {
	cout << endl;
	if (item_in_hands != NULL) cout << "You are already holding: " << B_RED_ << item_in_hands->name << RESET_ << endl;
	else {
		Entity* from_object = room->FindChild(from_object_name);
		if (from_object == NULL) cout << "I dont see any " << B_RED_ << from_object_name << RESET_ << " near me" << endl;
		else {
			if (from_object->can_unlock && from_object->locked) cout << B_RED_ << from_object->name << RESET_ << " is locked, you cant pick anything inside." << endl;
			else {
				Entity* object_to_take = from_object->FindChild(object_name);
				if (object_to_take == NULL) cout << "I dont see any " << B_RED_ << object_name << RESET_ << " in " << B_RED_ << from_object->name << RESET_ << endl;
				else {
					item_in_hands = object_to_take;
					item_in_hands->ChangeParentTo(this);
					cout << "You picked up: " << B_RED_ << item_in_hands->name << RESET_ << endl;
				}
			}
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