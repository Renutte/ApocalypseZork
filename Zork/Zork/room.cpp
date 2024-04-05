#include <iostream>
#include "globals.h"
#include "item.h"
#include "room.h"

// ----------------------------------------------------
Room::Room(const char* title, const char* description) :
	Entity(title, description, nullptr, false),
	north_exit(nullptr),
	south_exit(nullptr),
	east_exit(nullptr),
	west_exit(nullptr)
{
}


Exit* Room::GetExit(Direction direction) {
	if (direction == SOUTH) return south_exit;
	else if (direction == EAST) return east_exit;
	else if (direction == WEST) return west_exit;
	else if (direction == NORTH) return north_exit;
}

//Exit Room::GetExitInfo(Direction direction) {
//	if (direction == SOUTH) return south_exit;
//	else if (direction == EAST) return east_exit;
//	else if (direction == WEST) return west_exit;
//	else if (direction == NORTH) return north_exit;
//}

void Room::SetExit(Direction direction, Entity* obstruction_object, Room* destination, const char* name, const char* description) {
	// Obtener el puntero de salida correspondiente
	Exit* exitPtr = new Exit(direction, obstruction_object, destination, name, description, this);
	if (direction == NORTH) north_exit = exitPtr;
	else if (direction == SOUTH) south_exit = exitPtr;
	else if (direction == EAST) east_exit = exitPtr;
	else if (direction == WEST) west_exit = exitPtr;
}


void Room::RemoveObstruction(Direction direction) {
	Exit* aux_exit = GetExit(direction);
	aux_exit->RemoveObstruction();
}

void LookExit(Exit* aux_exit) {
	if (aux_exit != nullptr)
		if (aux_exit->obstruction_object == nullptr) cout << "Seems i can go to the " << B_GREEN_ << directionToString(aux_exit->direction) << RESET_ << endl;
		else cout << "Seems i can go to the " << B_GREEN_ << directionToString(aux_exit->direction) << RESET_ << ", but its obstructed by " << B_RED_ << aux_exit->obstruction_object->name << RESET_ << endl;
}

void Room::Look() const
{
	//cout << "--- Room::Look " << endl;

	cout << endl;
	cout << "You are now in the " << B_BLUE_ << name << RESET_ << endl;
	cout << description << endl;
	cout << endl;

	//Directions();

	//// List exits --
	//for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	//{
	//	if ((*it)->type == EXIT)
	//	{
	//		Exit* ex = (Exit*)*it;
	//		cout << "\nDirection (" << ex->GetNameFrom(this) << ") you see " << ex->GetDestinationFrom(this)->name;
	//	}
	//}

	//// List items --
	//for (list<Entity*>::const_iterator it = container.begin(); it != container.cend(); ++it)
	//{
	//	if ((*it)->type == ITEM)
	//	{
	//		Item* item = (Item*)*it;
	//		cout << "\nThere is an item here: " << item->name;
	//	}
	//}

}

void Room::Directions() const {
	cout << endl;
	LookExit(south_exit);
	LookExit(north_exit);
	LookExit(east_exit);
	LookExit(west_exit);
	cout << endl;
}