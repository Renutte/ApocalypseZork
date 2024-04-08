# Welcome to Apocalypse Zork!

Hey! This is a small text-based adventure game project inspired by the original game [Zork](https://en.wikipedia.org/wiki/Zork). 
It runs in the terminal, you must input instructions that the game can process. 
Use your imagination!😊

> **Languaje:** C++
> **IDE:** Microsoft Visual Studio Community 2019 Versión 16.11.34
> [Github repository](https://github.com/Renutte/ApocalypseZork/tree/main)
> [VS Solution](https://github.com/Renutte/ApocalypseZork/blob/main/Zork/Zork.sln)
 
Author: *Daniel Zimmermann García*

# Guide
## Execution

To start the game, simply download the release and run the ".exe" file.
Alternatively, you can download the source code and compile it using Visual Studio (VS).

## History context
You are wandering through a wasteland, thirsty and with low oxygen levels...
Your objective is to find a source of water.
In the distance, you spot a cave and decide to enter.
Inside the cave, you discover an abandoned settlement.
You decide to explore and see if you find anything interesting.
> **Note:** You can't move too much! The oxygen depletes each time you move.

## Color guide
The game uses colors to distinguish elements, you can see these colors represented on the map too.

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

## Map
Try to solve it without looking at the map! 😡
![Ejemplo de imagen](https://raw.githubusercontent.com/Renutte/ApocalypseZork/main/MapIdea.png)

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