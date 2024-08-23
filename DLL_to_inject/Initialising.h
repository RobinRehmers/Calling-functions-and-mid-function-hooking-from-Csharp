#ifndef INITIALISING_H
#define INITIALISING_H

#include <Windows.h>


DWORD64 transformItemIDtoHashAddress = 0;
DWORD64 itemSpawnAddress = 0;

DWORD64 itemHash = 0;
DWORD64 localplayerAddress;
DWORD64 jmpBack_localplayerAddress = 0;
int spawnamount = 1;

DWORD WINAPI Initialising(LPVOID lpParam)
{
	//i locate and hook the baseaddress of the localplayer since its a function argument for the spawnfunction we want to call later
	localplayerAddress = ArrayOfBytesScan("SkyrimSE.exe", "0F 85 FF 01 00 00 F3 0F 10 4B 5C F3 0F 5C 4F 5C F3 0F 10 43 58 F3 0F 5C 47 58 F3 0F 10 73 54 F3 0F 5C 77 54 F3 0F 59 F6");
	localplayerAddress = localplayerAddress + 6;
	jmpBack_localplayerAddress = localplayerAddress + 15;
	Hook((void*)localplayerAddress, localplayerHook, 15);

	//we cant just spawn the item with the Item ID which is online available. the game itself uses an itemhash to spawn items, it is different each time we start the game. 
	//It uses a function to transform the Item ID to the hash. this one we will call before.
	transformItemIDtoHashAddress = ArrayOfBytesScan("SkyrimSE.exe", "40 57 48 83 EC 30 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 40 48 89 74 24 58 8B F9");
	
	// this is the address to teh actual spawnfunction we will call after we received the item hash.
	itemSpawnAddress = ArrayOfBytesScan("SkyrimSE.exe", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 4C 8B 51");

	SpawnItemToInventory(itemSpawnAddress);
	//CreateThread(0, 0, ItemSpawnThread, 0, 0, 0);

	return NULL;
}

#endif