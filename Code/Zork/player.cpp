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

// Prints information about the actual room and mark as visited (for input "directions" infromation)
void Player::Look() const
{
	cout << endl;
	room->Look();
	room->SetVisited();
	cout << endl;
}

// Prints information about the actual room and mark as visited (for input "directions" infromation) and prints actual oxygen levels
void Player::PrintOxygenAndRoomInfo() {
	cout << endl;
	room->SetVisited();
	room->Look();
	Oxygen();
}

// Prints the directions where player can go in the actual room
void Player::Directions() const
{
	room->Directions();
}

// Prints a list of the objects inside the actual room
void Player::Examine() const
{
	cout << endl;
	room->Examine();
	cout << endl;
}

// Change the oxygen levels of the player
void Player::SetRemainingOxygen(int new_oxygen) {
	oxygen_remaining = new_oxygen;
}

// Set the ammout of oxygen loosed by each movement
void Player::SetOxygenLoosedPerMovement(int new_oxygen) {
	oxygen_loosed_per_movement = new_oxygen;
}

// Prints the actual oxygen levels
void Player::Oxygen() {
	cout << endl;
	if (oxygen_remaining > 0) cout << "The oxygen levels in tank are at " << B_YELLOW_ << oxygen_remaining << "%" << RESET_ << "." << endl;
	else {
		cout << "There is no more oxygen in tank." << endl;
		dead = true;
	}
	cout << endl;
}

// Return true if the player has dead (dont have more oxygen)
bool Player::IsDead() const {
	return dead;
}

// Manage the use of the item in hands (In the actual game: Only "Oxygen Tank")
void Player::Use(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What do you want to use?" << endl;
	else {
		if (item_in_hands == NULL || !Same(object_name, item_in_hands->name)) cout << "You are not holding something you can use." << endl;
		else {
			if (item_in_hands->GetItemProperties() != NULL && item_in_hands->GetItemProperties()->oxygen_provided > 0) {
				cout << "You refilled your oxygen with this " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
				SetRemainingOxygen(item_in_hands->GetItemProperties()->oxygen_provided + oxygen_remaining);
				Oxygen();
				item_in_hands->GetItemProperties()->oxygen_provided = 0;
				item_in_hands->ChangeNameTo("Empty " + item_in_hands->name);
				item_in_hands->ChangeDescriptionTo("A tank with " B_YELLOW_ "0%" RESET_ " of Oxygen.");
				return;
			}
			else {
				cout << "You can't use this " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
			}
		}
	}
	cout << endl;
}

// Manage the movement of the player between rooms
void Player::Go(string direction_name) {
	if (direction_name == "") cout << endl << "Where do you want to go?" << endl << endl;
	else {
		if (stringToDirection(direction_name) == ERROR_DIRECTION) cout << endl << "Cant recognize this direction. " << endl << endl;
		else {
			Exit* exit = room->GetExit(stringToDirection(direction_name));
			if (exit == NULL) {
				cout << endl << "Cant go to this direction. " << endl << endl;
			}
			else if (exit->obstruction_object != NULL) {
				cout << endl << "Cant go to this direction, is obstructed by " << B_RED_ << exit->obstruction_object->name << RESET_ << "." << endl << endl;
			}
			else {
				room = exit->destination;
				ChangeParentTo(exit->destination);
				cout << endl;
				room->Look();
				room->SetVisited();
				SetRemainingOxygen(oxygen_remaining - oxygen_loosed_per_movement);
				Oxygen();
			}
		}
	}
}

// Manage the opening of objects (In the actual game: Doors)
// Player can just open a door if the item in hands is the correct one
void Player::Open(string object_name) const {
	cout << endl;
	if (object_name == "") cout <<  "What do you want to open?" << endl;
	else {
		Entity* entity_to_open = room->FindChild(object_name);
		if (entity_to_open == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " near You." << endl;
		else {
			Item* item_that_opens = entity_to_open->opens;
			if (item_that_opens != NULL) {
				if (item_in_hands != NULL) {
					if (item_in_hands == item_that_opens) {
						room->UnlockExit(entity_to_open);
						entity_to_open->ChangeParentTo(NULL);
						cout << "The " << B_RED_ << entity_to_open->name << RESET_ << " has been opened. You have a new way now." << endl;
						delete entity_to_open;
					}
					else cout << "The " << B_RED_ << entity_to_open->name << RESET_ << " dosent open with " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
				}
				else {
					cout << "You need something to open this " << B_RED_  << entity_to_open->name << RESET_ << "." << endl;
				}
			}
			else {
				cout << "It is not a thing that you can open." << endl;
			}
		}
	}
	cout << endl;
}

// Manage the activation of the object (In the actual game: Only "Generator")
void Player::Activate(string object_name) const {
	cout << endl;
	if (object_name == "") cout << "What do you want to activate?" << endl;
	else {
		Entity* entity_to_activate = room->FindChild(object_name);
		if (entity_to_activate == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " near you." << endl;
		else if (entity_to_activate->can_activate == false) cout << "You cant activate the " << entity_to_activate->name << "." << endl;
		else {
			if (entity_to_activate->activated) cout << entity_to_activate->name << RESET_ << " already activated." << endl;
			else {
				entity_to_activate->SetActiveTo(true);
				cout << "You turned " << B_RED_ << entity_to_activate->name << RESET_ << " ON." << endl;
			}
		}
	}
	cout << endl;
}

// Prints the Read information of a readable item
void Player::Read(string object_name) const {
	cout << endl;
	Entity* entity_to_read = room->FindChild(object_name);
	if (item_in_hands != nullptr && (object_name.empty() || Same(item_in_hands->name, object_name))) entity_to_read = item_in_hands;
	if (entity_to_read == nullptr) {
		if (object_name.empty()) cout << "What do you want to read?" << endl;
		else cout << "You don't have any readable " << B_RED_ << object_name << RESET_ << " near you." << endl;
	}
	else {
		if (!entity_to_read->can_read) cout << "This " << B_RED_ << entity_to_read->name << RESET_ << " does not have readable text." << endl;
		else cout << entity_to_read->read_description << endl;
	}

	cout << endl;
}

// Manage the unlock a locked object (In the actual game: Only "Locker")
void Player::Unlock(string object_name) const {
	cout << endl;
	if (object_name == "") cout << "What do you want to unlock?" << endl;
	else {
		Entity* entity_to_unlock = room->FindChild(object_name);
		if (entity_to_unlock == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " near you." << endl;
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
					else cout << "The password is not correct... Maybe if you try with other you can unlock it." << endl;
				} else cout << B_RED_ << entity_to_unlock->name << RESET_ << " already unlocked." << endl;
			}
			else cout << B_RED_ << entity_to_unlock->name << RESET_ << " is not unclockable." << endl;
		}
	}
	cout << endl;
}

// Manage the push of an object (In the actual game: Only "Rock")
void Player::Push(string object_name) const {
	cout << endl;
	if (object_name == "") cout << "What do you want to push?" << endl;
	else {
		Entity* entity_to_push = room->FindChild(object_name);
		if (entity_to_push == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " near you." << endl;
		else {
			bool can_push_entity = entity_to_push->can_push;
			if (entity_to_push != NULL && can_push_entity) {
				if (item_in_hands == NULL) {
					room->UnlockExit(entity_to_push);
					entity_to_push->ChangeParentTo(NULL);
					cout << entity_to_push->text_when_pushed << endl;
					delete entity_to_push;
				}
				else cout << "You cant push with objects in hands. " << endl;
			}
			else {
				cout << "You cant push this object. " << endl;
			}
		}
	}
	cout <<endl;
}

// Manage the take of an object
void Player::Take(string object_name) {
	cout << endl;
	if (object_name == "") cout << "What do you want to take?" << endl;
	else {
		if (item_in_hands != NULL) cout << "Your hands are already as full as they can be, already holding a " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
		else {
			Entity* object_to_take = room->FindChild(object_name);
			if (object_to_take == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " near you." << endl;
			else if (object_to_take->opens == NULL) cout << "You cant pick this up." << endl;
			else {
				item_in_hands = object_to_take;
				item_in_hands->ChangeParentTo(this);
				cout << "You picked up the " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
			}
		}
	}
	cout << endl;
}

// Manage the take of the object_name (item has to be in hands) from from_object_name
void Player::Take(string object_name, string from_object_name) {
	cout << endl;
	if (item_in_hands != NULL) cout << "Your hands are already as full as they can be, already holding a " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
	else {
		Entity* from_object = room->FindChild(from_object_name);
		if (from_object == NULL) cout << "You dont see any " << B_RED_ << from_object_name << RESET_ << " near you." << endl;
		else {
			if (from_object->can_unlock && from_object->locked) cout << B_RED_ << from_object->name << RESET_ << " is locked, you can't pick anything inside." << endl;
			else {
				Entity* object_to_take = from_object->FindChild(object_name);
				if (object_to_take == NULL) cout << "You dont see any " << B_RED_ << object_name << RESET_ << " in " << B_RED_ << from_object->name << RESET_ << "." << endl;
				else {
					item_in_hands = object_to_take;
					item_in_hands->ChangeParentTo(this);
					cout << "You picked up the " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
				}
			}
		}
	}
	cout << endl;
}

// Manage the place of the object_name (item has to be in hands) into from_object_name
void Player::Place(string object_name, string into_object_name) {
	cout << endl;
	if (item_in_hands == NULL) cout << "You are not holding anything." << endl;
	else {
		Entity* from_object = room->FindChild(into_object_name);
		if (from_object == NULL) cout << "You dont see any " << B_RED_ << into_object_name << RESET_ << " near you." << endl;
		else {
			if (from_object->can_unlock && from_object->locked) cout << B_RED_ << from_object->name << RESET_ << " is locked, you can't place anything inside." << endl;
			else if (from_object->can_store == false) cout << "You can't place anything inside this " << B_RED_ << from_object->name << RESET_ << "." << endl;
			else {
				if (Same(object_name, item_in_hands->name) || object_name == "") {
					item_in_hands->ChangeParentTo(from_object);
					cout << "You placed the " << B_RED_ << item_in_hands->name << RESET_ << " in " << B_RED_ << from_object->name << RESET_ << "." << endl;
					item_in_hands = NULL;
				}
				else {
					cout << "You are not holding any " << B_RED_ << object_name << RESET_ << "." << endl;
				}
			}
		}
	}
	cout << endl;
}

// Manage the drop of the item in hands
void Player::Drop(string object_name) {
	cout << endl;
	if (item_in_hands == NULL) cout << "You are not holding anything." << endl;
	else {
		if (object_name == "" || Same(object_name, item_in_hands->name)) {
			cout << "You dropped the " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
			item_in_hands->ChangeParentTo(room);
			item_in_hands = NULL;
		}
		else cout << "You are not holding any " << B_RED_ << object_name << RESET_ << "." << endl;
	}
	cout << endl;
}

// Prints information about what player is holding in hands
void Player::Inventory() const {
	cout << endl;
	if (item_in_hands == NULL) cout << "You are not holding anything." << endl;
	else {
		cout << "You are holding a " << B_RED_ << item_in_hands->name << RESET_ << "." << endl;
		cout << item_in_hands->description << endl;
	}
	cout << endl;
}