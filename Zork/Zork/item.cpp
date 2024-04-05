#include <iostream>
#include "item.h"

Item::Item(const char* title, const char* description, Entity* parent) :
	Entity(title, description, parent, true, this) {

}

void Item::Opens(Entity* entity_that_opens) {
	opens = entity_that_opens;
}