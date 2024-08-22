#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

extern DWORD64 transformItemIDtoHashAddress;
extern DWORD64 itemSpawnAddress;
DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature);

#endif