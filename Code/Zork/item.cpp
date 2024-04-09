#include <iostream>
#include "item.h"

Item::Item(const char* title, const char* description, Entity* parent) :
	Entity(title, description, parent, true, this) {

}

// Set the entity that can open
void Item::Opens(Entity* entity_that_opens) {
	opens = entity_that_opens;
}

// Set the oxygen that provides when used
void Item::SetOxygenProvided(int ammount_to_fill) {
	oxygen_provided = ammount_to_fill; 
}

