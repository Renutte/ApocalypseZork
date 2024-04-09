#include <iostream>
#include "exit.h"

Exit::Exit(Direction direction, Entity* obstruction_object, Room* destination, const char* title, const char* description, Room* room) :
    Entity(title, description, (Entity*)room, false),
    direction(direction),
    obstruction_object(obstruction_object),
    destination(destination)
{
}

// Removes the obstruction
void Exit::RemoveObstruction() {
	obstruction_object = NULL;
}