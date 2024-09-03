#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

DWORD WINAPI PipeServer(LPVOID lpParam);
DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature);
void SpawnItemToInventory(int itemID, int spawnAmount);
bool Hook(void* toHook, void* hk_func, int len);

#endif