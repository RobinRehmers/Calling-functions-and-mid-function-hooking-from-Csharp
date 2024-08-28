#ifndef CALLING
#define CALLING_H

#include <iostream>
#include <string>

bool firstspawncall = false;
DWORD64 transformID = 0x0;
DWORD64 localplayer = 0x0;

void SpawnItemToInventory(int itemID, int spawnAmount)
{
	if (localplayer != 0)
	{
		typedef void(__fastcall* TransformItemIDtoHash)(__int64 a);
		TransformItemIDtoHash GetInteralID = (TransformItemIDtoHash)transformItemIDtoHashAddress;
		GetInteralID(itemID);
		__asm mov itemHash, rax

		DWORD64 playerbase = (DWORD64)localplayer;
		typedef void(__fastcall* _pFunc)(__int64 a, __int64 b, int c, int d, __int64 e);
		_pFunc tarnung = (_pFunc)itemSpawnAddress;
		tarnung(playerbase, itemHash, 0, spawnAmount, 0);
	}
}

#endif