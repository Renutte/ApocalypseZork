#include <iostream>
#include "globals.h"
#include "item.h"
#include "room.h"

Room::Room(const char* title, const char* description) :
	Entity(title, description, NULL, false),
	north_exit(NULL),
	south_exit(NULL),
	east_exit(NULL),
	west_exit(NULL)
{
}

// Return the exit specified by the direction
Exit* Room::GetExit(Direction direction) const {
	if (direction == SOUTH) return south_exit;
	else if (direction == EAST) return east_exit;
	else if (direction == WEST) return west_exit;
	else if (direction == NORTH) return north_exit;
	return NULL;
}

// Set a new exit specifying the direction , the object that is obstructing (if it have), the destination room, the name of the exit and his descritpion
void Room::SetExit(Direction direction, Entity* obstruction_object, Room* destination, const char* name, const char* description) {
	Exit* exitPtr = new Exit(direction, obstruction_object, destination, name, description, this);
	if (direction == NORTH) north_exit = exitPtr;
	else if (direction == SOUTH) south_exit = exitPtr;
	else if (direction == EAST) east_exit = exitPtr;
	else if (direction == WEST) west_exit = exitPtr;
}

// Updates the exits, removing the obstruction object (opening the way)
void Room::UnlockExit(Entity* obstruction_object) const{
	if (north_exit != NULL && north_exit->obstruction_object == obstruction_object) north_exit->obstruction_object = NULL;
	if (south_exit != NULL && south_exit->obstruction_object == obstruction_object) south_exit->obstruction_object = NULL;
	if (east_exit != NULL && east_exit->obstruction_object == obstruction_object) east_exit->obstruction_object = NULL;
	if (west_exit != NULL && west_exit->obstruction_object == obstruction_object) west_exit->obstruction_object = NULL;
}

// Removes the obstruction from the specified direction
void Room::RemoveObstruction(Direction direction) const{
	Exit* aux_exit = GetExit(direction);
	aux_exit->RemoveObstruction();
}

// Prints information about where you can go in this aux_exit
void LookExit(Exit* aux_exit) {
	if (aux_exit != NULL)
		if (aux_exit->obstruction_object == NULL) { 
			if (aux_exit->destination != NULL && aux_exit->destination->visited) cout << "Seems you can go to the " << B_GREEN_ << directionToString(aux_exit->direction) << RESET_ << ", to the " << B_BLUE_ << aux_exit->destination->name << RESET_ << "." << endl;
			else cout << "Seems you can go to the " << B_GREEN_ << directionToString(aux_exit->direction) << RESET_ << "."<< endl;
		}
		else cout << "Seems you can go to the " << B_GREEN_ << directionToString(aux_exit->direction) << RESET_ << ", but its obstructed by " << B_RED_ << aux_exit->obstruction_object->name << RESET_ <<"." << endl;
}

// Prints information about the actual room
void Room::Look() const
{
	cout << "You are now in the " << B_BLUE_ << name << RESET_ << "." << endl;
	cout << description << endl;
}

// Check the room as visited (For better LookExit() information -> If its checked appears the destination name)
void Room::SetVisited()
{
	visited = true;
}

// Prints all information about where player can go from this room
void Room::Directions() const {
	cout << endl;
	LookExit(south_exit);
	LookExit(north_exit);
	LookExit(east_exit);
	LookExit(west_exit);
	cout << endl;
}