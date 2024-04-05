#pragma once

#ifndef __Item__
#define __Item__

#include <string>
#include <list>
#include <vector>
#include <time.h>

#include "entity.h"
#include "globals.h"


using namespace std;

class Item : public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent);
	void Opens(Entity* entity_that_opens);

public:
	Entity* opens;
};

#endif