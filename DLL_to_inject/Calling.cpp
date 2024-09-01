#include "Calling.h"
#include "Globals.h"

DWORD64 GetItemIDMemAddr(int itemID)
{
    typedef DWORD64(__fastcall* LookupItemIDMemAddr)(__int64 a);
    LookupItemIDMemAddr LookupID = (LookupItemIDMemAddr)getLookupItemIDMemAddr();
    return LookupID(itemID);
}

void SpawnItemInInventory(DWORD64 playerBase, DWORD64 itemIDMemAddr, int spawnAmount)
{
    typedef void(__fastcall* SpawnItem)(__int64 a, __int64 b, int c, int d, __int64 e);
    SpawnItem Spawn = (SpawnItem)getItemSpawnAddress();
    Spawn(playerBase, itemIDMemAddr, 0, spawnAmount, 0);
}

void SpawnItemToInventory(int itemID, int spawnAmount)
{
    if (getLocalPlayer() != 0)
    {
        DWORD64 itemIDMemAddr = GetItemIDMemAddr(itemID);
        DWORD64 playerBase = getLocalPlayer();
        SpawnItemInInventory(playerBase, itemIDMemAddr, spawnAmount);
    }
}