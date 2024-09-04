#ifndef GAMEFUNCCALLER_H
#define GAMEFUNCCALLER_H

#include <Windows.h>

class GameFuncCaller {
public:
    static GameFuncCaller& GetInstance();
    void SpawnItemToInventory(int itemID, int spawnAmount);
    void Initialize();

    DWORD64 getLookupItemIDMemAddr() const;
    DWORD64 getItemSpawnAddress() const;
    void setLookupItemIDMemAddr(DWORD64 value);
    void setItemSpawnAddress(DWORD64 value);

private:
    GameFuncCaller() {}
    DWORD64 GetItemIDMemAddr(int itemID);
    void SpawnItem(DWORD64 playerBase, DWORD64 itemIDMemAddr, int spawnAmount);

    DWORD64 LookupItemIDMemAddress = 0;
    DWORD64 itemSpawnAddress = 0;
};

#endif
