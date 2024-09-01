#ifndef GLOBALS_H
#define GLOBALS_H

#include <Windows.h>

DWORD64 getLocalPlayer();
DWORD64 getLookupItemIDMemAddr();
DWORD64 getItemSpawnAddress();
DWORD64 getTransformID();
DWORD64 getItemHash();
DWORD64 getLocalPlayerAddress();
DWORD64 getJmpBackLocalPlayerAddress();
int getSpawnAmount();

void setLocalPlayer(DWORD64 value);
void setLookupItemIDMemAddr(DWORD64 value);
void setItemSpawnAddress(DWORD64 value);
void setTransformID(DWORD64 value);
void setItemHash(DWORD64 value);
void setLocalPlayerAddress(DWORD64 value);
void setJmpBackLocalPlayerAddress(DWORD64 value);
void setSpawnAmount(int value);

#endif
