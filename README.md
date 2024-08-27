Calling functions and hooking in Csharp 

The project's goal was to reverse engineer and manipulate game memory in the RPG "The Elder Scrolls V: Skyrim". The main objective of this project is to inject a DLL into the game, which allows for spawning items directly into the player's inventory through an external WPF application.


Reverse Engineering Process

I reverse-engineered key aspects of Skyrim to locate the memory address of the localplayer and identified the functions responsible for item spawning. During the reverse engineering process with different tools, I discovered that one function in Skyrim takes an itemID as an argument, transforms it into an itemHash, and another function utilizes this itemHash to spawn the item into the game world. 
I was able to write a custom DLL that interacts with these functions and effectively spawns items.


Project Overview

The project involves three main components:

Custom DLL: The DLL is automatic injected into Skyrim's process. It hook a relevant function and performs a series of "Array of bytes"-Scans in order to identify certain functions in the game's memory. It includes a named pipe server to establish communication between the injected DLL and an external application.
Injection Library: The C# library contains the DLL-Injector and a SpawnRequest function communicating with the pipeserver.
External WPF Application: This application allows the user to select items and specify the quantity to spawn in Skyrim. It communicates with the injected DLL using inter-process communication to call functions.


Key Features

Reverse Engineering: Identified and utilized game memory addresses and functions responsible for item spawning.
DLL Injection: Injected a custom DLL into the game to manipulate its memory and behavior.
Item Spawning: Implemented item spawning functionality by interacting directly with the game's internal functions.
Inter-process Communication (IPC): Used Named Pipes for communication between the external WPF application and the injected DLL.
WPF Application: Interface to select items and spawn them in-game.


Technologies Used

C++: For writing the DLL and performing memory manipulation, such as hooking and calling functions directly.
C# (WPF): For developing the external application that interacts with the game.
Reverse Engineering Tools: Used tools like IDA Pro and x64dbg to analyze the executable and memory structure.
Windows API: Utilized for DLL injection and IPC.
