#include "Globals.h"
#include "GameFuncCaller.h"
#include "Calling.h"

DWORD64 GetItemIDMemAddr(int itemID)
{
    typedef DWORD64(__fastcall* LookupItemIDMemAddr)(__int64 a);
    LookupItemIDMemAddr LookupID = (LookupItemIDMemAddr)GameFuncCaller::GetInstance().getLookupItemIDMemAddr();
    return LookupID(itemID);
}

void SpawnItem(DWORD64 playerBase, DWORD64 itemIDMemAddr, int spawnAmount)
{
    typedef void(__fastcall* SpawnItem)(__int64 a, __int64 b, int c, int d, __int64 e);
    SpawnItem Spawn = (SpawnItem)GameFuncCaller::GetInstance().getItemSpawnAddress();
    Spawn(playerBase, itemIDMemAddr, 0, spawnAmount, 0);
}

void SpawnItemToInventory(int itemID, int spawnAmount)
{
    if (localplayer != 0)
    {
        DWORD64 itemIDMemAddr = GetItemIDMemAddr(itemID);
        SpawnItem(localplayer, itemIDMemAddr, spawnAmount);
    }
}