#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

extern DWORD64 localplayer;
extern DWORD64 transformItemIDtoHashAddress;
extern DWORD64 itemSpawnAddress;
extern DWORD64 transformID;
extern DWORD64 itemHash;
extern DWORD64 localplayerAddress;
extern DWORD64 jmpBack;

extern int spawnamount;

DWORD WINAPI PipeServer(LPVOID lpParam);
DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature);
void SpawnItemToInventory(int itemID, int spawnAmount);
bool Hook(void* toHook, void* hk_func, int len);

#endif