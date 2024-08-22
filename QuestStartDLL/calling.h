#ifndef CALLING
#define CALLING_H

bool firstspawncall = false;

void TransformItemIDtoHash(DWORD64 addressToCall)
{
	if (firstspawncall)
	{
		typedef void(__fastcall* TransformItemIDtoHash)(__int64 a);
		TransformItemIDtoHash GetInteralID = (TransformItemIDtoHash)transformItemIDtoHashAddress;
		GetInteralID(transformID);
		__asm
		mov transformIDstore, rax
			DWORD64 playerbase2 = (DWORD64)localplayer;
		typedef void(__fastcall* _pFunc)(__int64 a, __int64 b, int c, int d, __int64 e);
		_pFunc tarnung = (_pFunc)spawncalladdy;
		tarnung(playerbase2, transformIDstore, 0, spawnamount, 0);
		firstspawncall = false;
	}
}

#endif