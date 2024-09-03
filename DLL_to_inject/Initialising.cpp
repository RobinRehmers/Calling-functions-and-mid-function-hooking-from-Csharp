#include "Initialising.h"
#include "Globals.h"
#include "Hooks.h"
#include "Main.h"


DWORD WINAPI Initialising(LPVOID lpParam)
{
    DWORD64 localplayerAddr = ArrayOfBytesScan("SkyrimSE.exe", "0F 85 FF 01 00 00 F3 0F 10 4B 5C F3 0F 5C 4F 5C F3 0F 10 43 58 F3 0F 5C 47 58 F3 0F 10 73 54 F3 0F 5C 77 54 F3 0F 59 F6");
	localplayerAddr += 6;
    jmpBack = localplayerAddr + 15;
    Hook((void*)localplayerAddr, localplayerHook, 15);

    setLookupItemIDMemAddr(ArrayOfBytesScan("SkyrimSE.exe", "40 57 48 83 EC 30 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 40 48 89 74 24 58 8B F9"));
    setItemSpawnAddress(ArrayOfBytesScan("SkyrimSE.exe", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 4C 8B 51"));

    return NULL;
}
