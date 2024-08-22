#ifndef CALLING
#define CALLING_H

bool firstspawncall = false;
DWORD64 transformID = 0x0;
DWORD64 localplayer = 0x0;

void TransformItemIDtoHash(DWORD64 addressToCall)
{
	if (firstspawncall)
	{
		typedef void(__fastcall* TransformItemIDtoHash)(__int64 a);
		TransformItemIDtoHash GetInteralID = (TransformItemIDtoHash)transformItemIDtoHashAddress;
		GetInteralID(0x0);
		__asm mov itemHash, rax

		DWORD64 playerbase = (DWORD64)localplayer;
		typedef void(__fastcall* _pFunc)(__int64 a, __int64 b, int c, int d, __int64 e);
		_pFunc tarnung = (_pFunc)itemSpawnAddress;
		tarnung(playerbase, itemHash, 0, spawnamount, 0);
		firstspawncall = false;
	}
}

#endif