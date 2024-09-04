#ifndef GLOBALS_H
#define GLOBALS_H

#include <Windows.h>

extern DWORD64 jmpBack;
extern DWORD64 localplayer;
extern DWORD64 localplayerAddr;

DWORD_PTR ArrayOfBytes(const char* szModule, const char* szSignature);

#endif
