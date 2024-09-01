#include "Globals.h"

// Definition der globalen Variablen
static DWORD64 localplayer = 0;
static DWORD64 LookupItemIDMemAddress = 0;
static DWORD64 itemSpawnAddress = 0;
static DWORD64 transformID = 0;
static DWORD64 itemHash = 0;
static DWORD64 localplayerAddress = 0;
static DWORD64 jmpBack_localplayerAddress = 0;
static int spawnamount = 1;

// Getter-Funktionen
DWORD64 getLocalPlayer() { return localplayer; }
DWORD64 getLookupItemIDMemAddr() { return LookupItemIDMemAddress; }
DWORD64 getItemSpawnAddress() { return itemSpawnAddress; }
DWORD64 getTransformID() { return transformID; }
DWORD64 getItemHash() { return itemHash; }
DWORD64 getLocalPlayerAddress() { return localplayerAddress; }
DWORD64 getJmpBackLocalPlayerAddress() { return jmpBack_localplayerAddress; }
int getSpawnAmount() { return spawnamount; }

// Setter-Funktionen
void setLocalPlayer(DWORD64 value) { localplayer = value; }
void setLookupItemIDMemAddr(DWORD64 value) { LookupItemIDMemAddress = value; }
void setItemSpawnAddress(DWORD64 value) { itemSpawnAddress = value; }
void setTransformID(DWORD64 value) { transformID = value; }
void setItemHash(DWORD64 value) { itemHash = value; }
void setLocalPlayerAddress(DWORD64 value) { localplayerAddress = value; }
void setJmpBackLocalPlayerAddress(DWORD64 value) { jmpBack_localplayerAddress = value; }
void setSpawnAmount(int value) { spawnamount = value; }
