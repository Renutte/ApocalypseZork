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
		Room* entrance = new Room("Entrance", "A place plenty of dust, seems like no one's been here for a long time.");
		Room* main_room = new Room("Main room", "The main linving room, smells bad.");
		Room* oxygen_store = new Room("Oxygen store", "The room feels small and cramped. \nFull of different kinds of equipment and contraptions, bits and pieces, pipes and leaks. \nIn the center of the room is a big table. \nThere is so much clutter on it you can barely make out any of it. \nYou have never seen some of this equipment before in your life. \nSome of it looks homemade, some of it looks military in nature.");
		Room* switch_room = new Room("Switch room", "A room with a lot of cables and electric things.");
		Room* vault_entrance = new Room("Vault entrance", "There is a giant vault entrance.");
		Room* vault = new Room("Vault", "Finally, a source of drinkable water.");
		finishRoom = vault;

	// === ENTITYS
		// == Entrance
		Entity* rock = new Entity("Rock", "The " B_RED_ "Rock" RESET_ " looks heavy, but unstable. \nIt's sitting against a cracked part of the wall, maybe I can push it and find a new way.", entrance, true);
		rock->SetPushable(true, "You push the " B_RED_ "Rock" RESET_ ", making it move a little. \nYou push it a second time, throwing your entire body towards it to make it budge, and the rock falls over. \nRevealing an opening in the wall.");
		// == Main Room
		Entity* corpse = new Entity("Corpse", "The rotting " B_RED_ "Corpse" RESET_ " is difficult to look at. \nYou have never seen this many shades of green and grey. \nThe smell is nauseating. \nMaybe if you examine it closer you can find something of use...", main_room, true);
		Entity* note = new Item("Note", "The " B_RED_ "Note" RESET_ " is torn and discolored. \nIt's obviously been here for some time. \nMaybe if you read it you can get some interesting information.", corpse);
		note->SetReadable(true, "The " B_RED_ "Note" RESET_ " says: \n\nAlexsei, they finally came. \nIt had to happen eventually, the *REDACTED* came over and *REDACTED* Olga and Sofia. \nAll i could do was watch, I am so sorry. \nIf you're somehow alive, the Password for the " B_RED_ "Locker" RESET_ " is 1027.");
		Item* blue_key = new Item("Blue Key", "Blue Key.", corpse);
		// == Oxygen Store
		Entity* shelf = new Entity("Shelf", "A large shelf with multiple objects, one of them is a Oxygen Tank, one of them is a Orange Key.", oxygen_store, true);
		Item* oxygen_tank = new Item("Oxygen Tank", "A with 50% of Oxygen.", shelf);
		oxygen_tank->SetOxygenProvided(50);
		Item* orange_key = new Item("Orange Key", "Orange key.", shelf);
		// == Switch Room
		Entity* generator = new Entity("Generator", "A " B_RED_ "Generator" RESET_ " with a switch i can activate, seems important to light all on.", switch_room, true);
		generator->SetActivateable(true, false);
		powerSource = generator;
		Entity* locker = new Entity("Locker", "A locked locker, i need a number combination. \nI see through the glass a Red Key.", switch_room, true);
		locker->SetUnlockable(true, true, "1027");
		Item* red_key = new Item("Red Key", "Red Key.", locker);
		// == Vault Entrance

		Entity* blue_door = new Entity("Blue Door", "It's a locked door. With some kind of blue lock.", entrance, true, blue_key);
		Entity* orange_door = new Entity("Orange Door", "A door with a orange lock, seems i can open it with a key.", main_room, true, orange_key);
		Entity* red_door = new Entity("Red Door", "A door with a red lock, seems i can open it with a key.", vault_entrance, true, red_key);

	// === EXITS
		// == Entrance
		entrance->SetExit(EAST, rock, main_room, "Rock entrance", "Seems a entrance to a switch room.");
		entrance->SetExit(SOUTH, blue_door, oxygen_store, "Blue door entrance", "Seems a entrance to a oxygen room.");
		// == Main Room
		main_room->SetExit(WEST, NULL, entrance, "Rock hole", "Seems a entrance to the entrance.");
		main_room->SetExit(EAST, orange_door, switch_room, "Orange door entrance", "Seems a entrance to the switch room.");
		main_room->SetExit(NORTH, NULL, vault_entrance, "Opened entrance", "Seems a entrance to the vault entrance room.");
		// == Oxygen Store
		oxygen_store->SetExit(NORTH, NULL, entrance, "Blue door entrance", "Seems a entrance to the entrance.");
		// == Switch Room
		switch_room->SetExit(WEST, NULL, main_room, "Orange door entrance", "Seems a entrance to the main room.");
		// == Vault Entrance
		vault_entrance->SetExit(SOUTH, NULL, main_room, "Opened entrance", "Seems a entrance to the main room.");
		vault_entrance->SetExit(EAST, red_door, vault, "Giant vault doot", "The entrance to de vault, good things be there.");

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
	else cout << endl << "I don't understand you, what do you want me to do?" << endl << endl;
}

Player* World::GetMainPlayer() {
	return player;
}

bool World::PlayerWin() {
	if (player->room == finishRoom) {
		if (powerSource->activated) { 
			cout << "I can breath without any tank of oxygen, the generator is purifying the air of this room." << endl << endl;
			return true;
		}
		else cout << "You forgot to activate the generator that provides the oxygen purifier." << endl << endl;
	}
	return false;
}
