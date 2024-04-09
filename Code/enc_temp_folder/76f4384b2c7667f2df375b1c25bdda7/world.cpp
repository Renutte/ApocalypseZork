#include <iostream>
#include "globals.h"
#include "entity.h"
#include "item.h"
#include "exit.h"
#include "room.h"
#include "player.h"
#include "world.h"

World::World()
{

	// === ROOMS
		Room* entrance = new Room("Entrance", "A place filled with dust, it seems like no one has been here for a long time.\nVegetation is invading this space.");
		Room* main_room = new Room("Main room", "The main linving room, smells bad. \nThere is blood on the walls, it seems that there has been a massacre.");
		Room* oxygen_store = new Room("Oxygen Store", "The room feels small and cramped. \nFull of different kinds of equipment, most of them deteriorated.");
		Room* switch_room = new Room("Switch room", "A room with a lot of cables and electric things. \nIt seems that this location supplies electricity to the rooms.");
		Room* vault_entrance = new Room("Vault entrance", "A site with nothing but a large round " B_RED_ "Red Door" RESET_ " that appears to be the entrance to a vault.");
		Room* vault = new Room("Vault", "Finally, a source of drinkable water.");
		finishRoom = vault;

	// === ENTITYS
		// == Entrance
		Entity* rock = new Entity("Rock", "The " B_RED_ "Rock" RESET_ " looks heavy, but unstable. \nIt's sitting against a cracked part of the wall, maybe you can push it and find a new way.", entrance, true);
		rock->SetPushable(true, "You push the " B_RED_ "Rock" RESET_ ", causing it to shift slightly. \nPushing it a second time, you throw your entire body into it to make it budge, and the rock falls over. \nRevealing an opening in the wall.");
		// == Main Room
		Entity* corpse = new Entity("Corpse", "The rotting " B_RED_ "Corpse" RESET_ " is difficult to look at. \nThe smell is nauseating. \nMaybe if you examine it closer you can find something of use...", main_room, true);
		Entity* note = new Item("Note", "The " B_RED_ "Note" RESET_ " is torn and discolored. \nIt's obviously been here for some time. \nMaybe if you read it you can get some interesting information.", corpse);
		note->SetReadable(true, "The " B_RED_ "Note" RESET_ " says: \n\nAlexsei, they finally came. \nIt had to happen eventually, the " STRIKETHROUGH_ "*REDACTED*" NO_STRIKETHROUGH_ " came over and " STRIKETHROUGH_ "*REDACTED*" NO_STRIKETHROUGH_ " Olga and Sofia. \nAll I could do was watch, I am so sorry. \nIf you're somehow alive, the Password for the " B_RED_ "Locker" RESET_ " is 1980.");
		Item* blue_key = new Item("Blue Key", "A " B_RED_ "Blue Key" RESET_ ", maybe you could use it to open some door.", corpse);
		// == Oxygen Store
		Entity* shelf = new Entity("Shelf", "A large shelf with multiple objects.", oxygen_store, true);
		Item* oxygen_tank = new Item("Oxygen Tank", "A with 50% of Oxygen.", shelf);
		oxygen_tank->SetOxygenProvided(50);
		Item* orange_key = new Item("Orange Key", "A " B_RED_ "Orange Key" RESET_ ", maybe you could use it to open some door.", shelf);
		// == Switch Room
		Entity* generator = new Entity("Generator", "A " B_RED_ "Generator" RESET_ " with a switch you can activate, seems important to light all on.", switch_room, true);
		generator->SetActivateable(true, false);
		powerSource = generator;
		Entity* locker = new Entity("Locker", "A locked " B_RED_ "Locker" RESET_ ", you need a number combination to unlock it.", switch_room, true);
		locker->SetUnlockable(true, true, "1980");
		Item* red_key = new Item("Red Key", "A " B_RED_ "Red Key" RESET_ ", maybe you could use it to open some door.", locker);
		// == Vault Entrance


		// == Doors
		Entity* blue_door = new Entity("Blue Door", "A closed " B_RED_ "Blue Door" RESET_ " with a small window, leading to what appears to be a storage area. \nPerhaps you can open it with a key.", entrance, true, blue_key);
		Entity* orange_door = new Entity("Orange Door", "Another closed " B_RED_ "Orange Door" RESET_ " with a small window, you'll need a new key... \nIt looks like this door leads to a place filled with cables.", main_room, true, orange_key);
		Entity* red_door = new Entity("Red Door", "This " B_RED_ "Red Door" RESET_ " is different from the others, larger and stronger. \nYou can't see what's on the other side, but it looks interesting.", vault_entrance, true, red_key);

	// === EXITS
		// == Entrance
		entrance->SetExit(EAST, rock, main_room, "Rock entrance", "Seems an entrance.");
		entrance->SetExit(SOUTH, blue_door, oxygen_store, "Blue door entrance", "Seems an entrance.");
		// == Main Room
		main_room->SetExit(WEST, NULL, entrance, "Rock hole", "Seems an entrance.");
		main_room->SetExit(EAST, orange_door, switch_room, "Orange door entrance", "Seems an entrance.");
		main_room->SetExit(NORTH, NULL, vault_entrance, "Opened entrance", "Seems an entrance.");
		// == Oxygen Store
		oxygen_store->SetExit(NORTH, NULL, entrance, "Blue door entrance", "Seems an entrance.");
		// == Switch Room
		switch_room->SetExit(WEST, NULL, main_room, "Orange door entrance", "Seems an entrance.");
		// == Vault Entrance
		vault_entrance->SetExit(SOUTH, NULL, main_room, "Opened entrance", "Seems an entrance.");
		vault_entrance->SetExit(EAST, red_door, vault, "Giant vault doot", "Seems an entrance.");

	// === PLAYER
		player = new Player("Explorer", "You are an explorer searching for water, your oxygen level is decreasing.", entrance);
		player->SetRemainingOxygen(40);
		player->SetOxygenLoosedPerMovement(10);
}

void World::ProcessInput(vector<string>& args)
{
	// == Remove empty slots from arguments
	for (unsigned int i = 1; i < args.size(); ++i) {
		if (args.at(i) == "") {
			args.erase(args.begin() + i);
			--i;
		}
	}

	// == Process inputs
	
	// == >> 
	if (Same(args[0], "examine")) player->parent->Examine(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "open"))player->Open(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "unlock")) player->Unlock(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "push")) player->Push(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "use")) player->Use(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "activate")) player->Activate(combineValues(args, args[0], ""));
	else if ((Same(args[0], "turn") || Same(args[0], "switch")) && Same(args[1], "on")) player->Activate(combineValues(args, args[1], ""));
	
	// == >> 
	else if (Same(args[0], "go") || Same(args[0], "move")) player->Go(combineValues(args, args[0], ""));
	
	// == >> 
	else if (Same(args[0], "look") /* || Same(args[0], "check") */ ) {
		if (args.size() == 1) player->Look(); // Without arguments
		else player->parent->Look(combineValues(args, args[0], "")); // With arguments
	}

	// == >> 
	else if (Same(args[0], "directions")) {
		// Maybe "Check directions" ??
		if (args.size() == 1) player->Directions(); // Without arguments
		else cout << endl << "I gather that you want to know about directions to go, but I don't understand you." << endl << endl; // With arguments
	}

	// == >> 
	else if (Same(args[0], "explore")) {
		if (args.size() == 1) player->Examine(); // Without arguments
		else if (args.size() == 2 && Same(args[1], "room")) player->Examine(); // Without arguments
		else cout << endl << "I gather that you want to explore this place, but I don't understand you." << endl << endl; // With arguments
	}

	// == >> 
	else if (Same(args[0], "inventory")) {
		// Maybe "Check inventory" ??
		if (args.size() == 1) player->Inventory(); // Without arguments
		else cout << endl << "I gather that you want to see your inventory, but I don't understand you." << endl << endl; // With arguments
	}

	// == >> 
	else if (Same(args[0], "read")) {
		if (args.size() == 1) player->Read(""); // Without arguments
		else player->Read(combineValues(args, args[0], "")); // With arguments
	}

	// == >> 
	else if (Same(args[0], "drop")) {
		if (args.size() == 1) player->Drop(""); // Without arguments
		else player->Drop(combineValues(args, args[0], "")); // With arguments
	}

	// == >> 
	else if (Same(args[0], "oxygen")) {
		// Maybe "Check oxygen" ??
		if (args.size() == 1) player->Oxygen(); // Without arguments
		else cout << endl << "I gather that you want to know your oxygen levels, but I don't understand you." << endl << endl; // With arguments
	}

	// == >> 
	else if (Same(args[0], "take") || Same(args[0], "get")) {
		if (args.size() > 1) {
			string object_name = combineValues(args, args[0], "from");
			if (object_name == "") object_name = combineValues(args, "take", "");
			string from_name = combineValues(args, "from", "");
			if (from_name != "") player->Take(object_name, from_name);
			else player->Take(object_name);
		}
		else {
			cout << endl << "I gather that you want to take something, but I don't understand you." << endl << endl; // With arguments
		}
	}

	// == >> 
	else cout << endl << "I don't understand you, what do you want to do?" << endl << endl;
}

Player* World::GetMainPlayer() {
	return player;
}

bool World::PlayerWin() {
	if (player->room == finishRoom) {
		if (powerSource->activated) { 
			cout << "You can breath without any tank of oxygen, the " B_RED_ "Generator" RESET_ " is purifying the air of the " B_BLUE_ "Vault" RESET_ "." << endl << endl;
			return true;
		}
		else cout << "You forgot to activate the " B_RED_ "Generator" RESET_ " that provides the purified oxygen to the " B_BLUE_ "Vault" RESET_ "." << endl << endl;
	}
	return false;
}
