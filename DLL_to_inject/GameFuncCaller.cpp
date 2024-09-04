#include "GameFuncCaller.h"
#include "MemoryReader.h"
#include "HookManager.h"

GameFuncCaller& GameFuncCaller::GetInstance() {
    static GameFuncCaller instance;
    return instance;
}

DWORD64 GameFuncCaller::GetItemIDMemAddr(int itemID) {
    typedef DWORD64(__fastcall* LookupItemIDMemAddr)(__int64 a);
    LookupItemIDMemAddr LookupID = (LookupItemIDMemAddr)getLookupItemIDMemAddr();
    return LookupID(itemID);
}

void GameFuncCaller::SpawnItem(DWORD64 playerBase, DWORD64 itemIDMemAddr, int spawnAmount) {
    typedef void(__fastcall* SpawnItem)(__int64 a, __int64 b, int c, int d, __int64 e);
    SpawnItem Spawn = (SpawnItem)getItemSpawnAddress();
    Spawn(playerBase, itemIDMemAddr, 0, spawnAmount, 0);
}

void GameFuncCaller::SpawnItemToInventory(int itemID, int spawnAmount) {
    if (HookManager::localplayer != 0) {
        DWORD64 itemIDMemAddr = GetItemIDMemAddr(itemID);
        SpawnItem(HookManager::localplayer, itemIDMemAddr, spawnAmount);
    }
}

void GameFuncCaller::Initialize() {
    setLookupItemIDMemAddr(MemoryReader::GetInstance().ArrayOfBytesScan("SkyrimSE.exe", "40 57 48 83 EC 30 48 C7 44 24 20 FE FF FF FF 48 89 5C 24 40 48 89 74 24 58 8B F9"));
    setItemSpawnAddress(MemoryReader::GetInstance().ArrayOfBytesScan("SkyrimSE.exe", "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 30 4C 8B 51"));
}

DWORD64 GameFuncCaller::getLookupItemIDMemAddr() const {
    return LookupItemIDMemAddress;
}

DWORD64 GameFuncCaller::getItemSpawnAddress() const {
    return itemSpawnAddress;
}

void GameFuncCaller::setLookupItemIDMemAddr(DWORD64 value) {
    LookupItemIDMemAddress = value;
}

void GameFuncCaller::setItemSpawnAddress(DWORD64 value) {
    itemSpawnAddress = value;
}
