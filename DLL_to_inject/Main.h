#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

extern DWORD64 localplayer;
extern DWORD64 transformItemIDtoHashAddress;
extern DWORD64 itemSpawnAddress;
extern DWORD64 transformID;
extern DWORD64 itemHash;
extern DWORD64 localplayerAddress;
extern DWORD64 jmpBack_localplayerAddress;
extern int spawnamount;

DWORD WINAPI ItemSpawnThread(LPVOID param);
DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature);
bool Hook(void* toHook, void* hk_func, int len);

#endif