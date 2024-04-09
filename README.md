# Welcome to Apocalypse Zork!

Hey! This is a small text-based adventure game project inspired by the original game [Zork](https://en.wikipedia.org/wiki/Zork). 
It runs in the terminal, you must input instructions that the game can process. 
Use your imagination!😊

> **Languaje:** C++<br>
> **IDE:** Microsoft Visual Studio Community 2019 Versión 16.11.34<br>
> [Github repository](https://github.com/Renutte/ApocalypseZork/tree/main)<br>
 
Author: *Daniel Zimmermann García*

# Guide
## Download and execution

To start the game, simply download [here](https://github.com/Renutte/ApocalypseZork/releases/tag/ApocalypseZork) the release and run the ".exe" file. <br>
Alternatively, you can download the [source code](https://github.com/Renutte/ApocalypseZork/releases/tag/ApocalypseZork) and compile it using Visual Studio (VS).

## History context

It is the year 2023. After a nuclear and biological war, the air has become unbreathable.<br>
You find yourself wandering through a desolate wasteland, thirsty and with your oxygen tank running low.<br>
Your objective is to find a source of water.<br>
In the distance, you spot a cave and decide to venture inside.<br>
As you explore, you discover an abandoned settlement and decide to check it out, hoping to find water.<br>

⚠️WARNING: Movement consumes oxygen, don't waste it by exploring unnecessarily.<br>
> **Note:** You can't move too much! The oxygen depletes each time you move.

## Color guide
The game uses colors in the responses to differentiate between elements.

|                |Reference to:                 |
|----------------|------------------------------|
|🔵 Blue         |Rooms                          |
|🔴 Red          |Objects                        |
|🟢 Green        |Directions                     |
|🟡 Yellow       |Oxygen levels                  |

## Inputs

The following list outlines the inputs that the game can recognize:

| Command                                                          | Action                                              | Parameter              |
|------------------------------------------------------------------|-----------------------------------------------------|------------------------|
| `look`                                                           | Provide detailed description of the current room    | -                      |
| `look [Object]`                                                  | Provide detailed description of the specified object| Object name            |
| `explore`<br>`explore room`                                      | List all objects in the current room                | -                      |
| `directions`                                                     | Display available directions                        | -                      |
| `inventory`                                                      | Describe the item you are holding                   | -                      |
| `read`                                                           | Read the item you are holding                       | -                      |
| `read [Item]`                                                    | Read the specified item                             | Note                   |
| `oxygen`                                                         | Show the player oxygen levels                       | -                      |
| `examine [Object]`                                               | Check contents of the specified object              | Object name            |
| `open [Object]`                                                  | Attempt to open the specified object                | Door name              |
| `unlock [Object]`                                                | Attempt to unlock the specified object              | Locker                 |
| `push [Object]`                                                  | Push the specified object                           | Rock                   |
| `use [Item]`                                                     | Refill the player's oxygen tank                     | Oxygen Tank            |
| `activate [Object]`<br>`turn on [Object]`<br>`switch on [Object]`| Try to turn on the specified object                 | Generator              |
| `go [Direction]`<br>`move [Direction]`                           | Move in the specified direction                     | North/South/East/West  |
| `drop`                                                           | Drop the item you are holding                       | -                      |
| `drop [Item]`                                                    | Drop the specified item you are holding             | Item name              |
| `take [Item] from [Object]`<br>`get [Item] from [Object]`        | Take a specific item from an object                 | Item name, Object name |
| `place [Item] in [Object]`<br>`put [Item] in [Object]`           | Place a specific item into an object                | Item name, Object name |

## Map
Try to solve it without looking at the map! 😡
![Ejemplo de imagen](https://github.com/Renutte/ApocalypseZork/blob/d953f1a98be9a5a316869cf57b46a294130ab339/Map.png)

## Input Scenarios
Look at these different input scenarios if you want a guide:
<details>
<summary>🏆 WIN (Arrived at vault with generator activated)</summary>
<br>directions
<br>look
<br>explore
<br>examine rock
<br>examine blue door
<br>look rock
<br>look blue door
<br>open blue door
<br>push rock
<br>directions
<br>go east
<br>look
<br>explore
<br>look corpse
<br>look orange door
<br>open orange door
<br>open corpse
<br>examine orange door
<br>examine corpse
<br>take note
<br>take note from corpse
<br>read note
<br>take key from corpse
<br>drop
<br>take key from corpse
<br>take blue key from corpse
<br>explore
<br>examine note
<br>look note
<br>direcrtions
<br>directions
<br>go west
<br>explore
<br>look blue door
<br>open blue door with bloue key
<br>open blue door
<br>look
<br>explore
<br>directions
<br>go south
<br>explore
<br>look
<br>look shelf
<br>examine shelf
<br>take oxygen tank
<br>drop
<br>take oxygen tank
<br>take oxygen tank from shelf
<br>use
<br>use oxygen tank
<br>take orange key from shelf
<br>drop
<br>take orange key from shelf
<br>explore
<br>look blue key
<br>look empty oxygen tank
<br>directions
<br>go north
<br>directions
<br>go east
<br>directions
<br>go east
<br>open orange door
<br>directions
<br>go east
<br>explore
<br>look generator
<br>look locker
<br>unlock
<br>locker
<br>unlock locker
<br>1980
<br>turn on generator
<br>explore
<br>look
<br>directions
<br>explore
<br>inventory
<br>drop
<br>take red key from locker
<br>directions
<br>go west
<br>explore
<br>directions
<br>go north
<br>explore
<br>look
<br>examine red door
<br>look red door
<br>drop
<br>open red door
<br>take red key
<br>open red door
<br>directions
<br>go east
</details>
<details>
<summary>💀 LOSE (Arrived at vault without generator activated)</summary>
<br>directions
<br>look
<br>explore
<br>examine rock
<br>examine blue door
<br>look rock
<br>look blue door
<br>open blue door
<br>push rock
<br>directions
<br>go east
<br>look
<br>explore
<br>look corpse
<br>look orange door
<br>open orange door
<br>open corpse
<br>examine orange door
<br>examine corpse
<br>take note
<br>take note from corpse
<br>read note
<br>take key from corpse
<br>drop
<br>take key from corpse
<br>take blue key from corpse
<br>explore
<br>examine note
<br>look note
<br>direcrtions
<br>directions
<br>go west
<br>explore
<br>look blue door
<br>open blue door with bloue key
<br>open blue door
<br>look
<br>explore
<br>directions
<br>go south
<br>explore
<br>look
<br>look shelf
<br>examine shelf
<br>take oxygen tank
<br>drop
<br>take oxygen tank
<br>take oxygen tank from shelf
<br>use
<br>use oxygen tank
<br>take orange key from shelf
<br>drop
<br>take orange key from shelf
<br>explore
<br>look blue key
<br>look empty oxygen tank
<br>directions
<br>go north
<br>directions
<br>go east
<br>directions
<br>go east
<br>open orange door
<br>directions
<br>go east
<br>explore
<br>look generator
<br>look locker
<br>unlock
<br>locker
<br>unlock locker
<br>1980
<br>explore
<br>look
<br>directions
<br>explore
<br>inventory
<br>drop
<br>take red key from locker
<br>directions
<br>go west
<br>explore
<br>directions
<br>go north
<br>explore
<br>look
<br>examine red door
<br>look red door
<br>drop
<br>open red door
<br>take red key
<br>open red door
<br>directions
<br>go east
</details>
<details>
<summary>💀 LOSE (Ran out of oxygen before reaching the vault)</summary>
<br>push rock
<br>go east
<br>go west
<br>go east
<br>go west
</details>

# MIT License

Copyright (c) 2024 Daniel Zimmermann García

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.