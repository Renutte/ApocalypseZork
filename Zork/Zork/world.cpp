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
		Room* entrance = new Room("Entrance", "A small entrance with nothing interesting... ");
		Room* main_room = new Room("Main room", "The main linving room, smells bad.");
		Room* oxygen_store = new Room("Oxygen store", "A room plenty of different equipments.");
		Room* switch_room = new Room("Switch room", "A room with a lot of cables and electric things.");
		Room* vault_entrance = new Room("Vault entrance", "There is a giant vault entrance.");
		Room* vault = new Room("Vault", "Finally a room where i can breath and drink water.");

	// === ENTITYS
		// == Entrance
		Entity* rock = new Entity("Rock", "A huge rock, seems i can push it.", entrance, true);
		Entity* plant_test = new Item("plant_test", "plant_test description.", entrance);
		// == Main Room
		Entity* corpse = new Entity("Corpse", "This corpse holds a Note and a Blue Key.", main_room, true);
		Entity* note = new Item("Note", "Password: 2 + 2", corpse);
		Item* blue_key = new Item("BKey", "Blue Key.", corpse);
		// == Oxygen Store
		Entity* shelf = new Entity("Shelf", "A large shelf with multiple objects, one of them is a Oxygen Tank, one of them is a Orange Key.", oxygen_store, true);
		Entity* oxygen_tank = new Item("Oxygen", "A tank full of Oxygen.", shelf);
		Item* orange_key = new Item("OKey", "Orange key.", shelf);
		// == Switch Room
		Entity* generator = new Entity("Generator", "A generator with a switch i can activate, seems important to light all on.", switch_room, true);
		Entity* locker = new Entity("Locker", "A locked locker, i need a number combination. I see through the glass a Red Key.", switch_room, true);
		Item* red_key = new Item("RKey", "Red Key.", locker);
		// == Vault Entrance

		Entity* blue_door = new Entity("Door", "A door with a blue lock, seems i can open it with a key.", entrance, true, blue_key);
		Entity* orange_door = new Entity("Door", "A door with a orange lock, seems i can open it with a key.", main_room, true, orange_key);
		Entity* red_door = new Entity("Door", "A door with a red lock, seems i can open it with a key.", vault_entrance, true, red_key);

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
}

bool World::Tick(vector<string>& args)
{
	bool ret = true;
	if (args.size() > 0 && args[0].length() > 0) ret = ParseCommand(args);
	return ret;
}

bool World::ParseCommand(vector<string>& args)
{

	/*cout << "--- World::ParseCommand" << endl;
	cout << "Args size: " << args.size() << endl;*/
	//for (const string& arg : args) {
	//	cout << arg << endl;
	//}

	bool ret = true;

	switch (args.size())
	{
	case 1: // 1 Argument
	{
		if (Same(args[0], "look")) player->Look();
		else if (Same(args[0], "directions")) player->Directions();
		else if (Same(args[0], "explore")) player->Examine();
		else if (Same(args[0], "inventory")) player->Inventory();
		else if (Same(args[0], "drop")) player->Drop();
		else ret = false;
		break;
	}
	case 2: // 2 Argument
	{
		if (Same(args[0], "examine")) player->parent->Examine(args[1]);
		else if (Same(args[0], "look") ) player->parent->Look(args[1]);
		else if (Same(args[0], "take")) player->Take(args[1]);
		else if (Same(args[0], "open")) player->Open(args[1]);
	//	else if (Same(args[0], "leave")) player->Leave(args);
	//	else if (Same(args[0], "read")) player->Read(args);
	//	else if (Same(args[0], "push")) player->Push(args);
	//	else if (Same(args[0], "use")) player->Use(args);
	//	else if (Same(args[0], "activate")) player->Activate(args);
		else if (Same(args[0], "go")) player->Go(args[1]);
	//	else ret = false;
		break;
	}
	case 3: // 3 Argument
	{
		break;
	}
	case 4: // 4 Argument
	{
		if (Same(args[0], "take") and Same(args[2], "from")) player->Take(args[1], args[3]);
	//	else ret = false;
		break;
	}
	default:
		ret = false;
	}

	return ret;
}



//// === ROOMS
//Room* entrance = new Room("Entrance", "A small entrance with nothing interesting... ");
//Room* main_room = new Room("Main room", "The main linving room, smells bad.");
//Room* oxygen_store = new Room("Oxygen store", "A room plenty of different equipments.");
//Room* switch_room = new Room("Switch room", "A room with a lot of cables and electric things.");
//Room* vault_entrance = new Room("Vault entrance", "There is a giant vault entrance.");
//Room* vault = new Room("Vault", "Finally a room where i can breath and drink water.");
//
//// === ENTITYS
//	// == Entrance
//Entity* rock = new Entity("Rock", "A huge rock, seems i can push it.", entrance, true);
//Entity* blue_door = new Entity("Door", "A door with a blue lock, seems i can open it with a key.", entrance, true);
//Entity* plant_test = new Entity("plant_test", "plant_test description.", entrance, true);
//// == Main Room
//Entity* corpse = new Entity("Corpse", "This corpse holds a Note and a Blue Key.", main_room, true);
//Entity* note = new Entity("Note", "Password: 2 + 2", corpse, true);
////Entity* note_test = new Item("NoteTest", "Password: 2 + 2", main_room);
//Entity* blue_key = new Entity("BKey", "Blue Key.", corpse, true);
//Entity* orange_door = new Entity("Door", "A door with a orange lock, seems i can open it with a key.", main_room, true);
//// == Oxygen Store
//Entity* shelf = new Entity("Shelf", "A large shelf with multiple objects, one of them is a Oxygen Tank, one of them is a Orange Key.", oxygen_store, true);
//Entity* oxygen_tank = new Entity("Oxygen", "A tank full of Oxygen.", shelf, true);
//Entity* orange_key = new Entity("OKey", "Orange key.", shelf, true);
//// == Switch Room
//Entity* generator = new Entity("Generator", "A generator with a switch i can activate, seems important to light all on.", switch_room, true);
//Entity* locker = new Entity("Locker", "A locked locker, i need a number combination. I see through the glass a Red Key.", switch_room, true);
//Entity* red_key = new Entity("RKey", "Red Key.", locker, true);
//// == Vault Entrance
//Entity* red_door = new Entity("Door", "A door with a red lock, seems i can open it with a key.", vault_entrance, true);
//
//// === EXITS
//	// == Entrance
//entrance->SetExit(EAST, rock, main_room, "Rock entrance", "Seems a entrance to a switch room.");
//entrance->SetExit(SOUTH, blue_door, oxygen_store, "Blue door entrance", "Seems a entrance to a oxygen room.");
//// == Main Room
//main_room->SetExit(WEST, NULL, entrance, "Rock hole", "Seems a entrance to the entrance.");
//main_room->SetExit(EAST, orange_door, switch_room, "Orange door entrance", "Seems a entrance to the switch room.");
//main_room->SetExit(NORTH, NULL, vault_entrance, "Opened entrance", "Seems a entrance to the vault entrance room.");
//// == Oxygen Store
//oxygen_store->SetExit(NORTH, NULL, entrance, "Blue door entrance", "Seems a entrance to the entrance.");
//// == Switch Room
//switch_room->SetExit(WEST, NULL, main_room, "Orange door entrance", "Seems a entrance to the main room.");
//// == Vault Entrance
//vault_entrance->SetExit(SOUTH, NULL, main_room, "Opened entrance", "Seems a entrance to the main room.");
//vault_entrance->SetExit(EAST, red_door, vault, "Giant vault doot", "The entrance to de vault, good things be there.");
//
//// === PLAYER
//player = new Player("Explorer", "You are an explorer searching for water, your oxygen level is decreasing.", entrance);