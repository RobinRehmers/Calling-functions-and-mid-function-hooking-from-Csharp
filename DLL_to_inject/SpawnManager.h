#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "PipeManager.h"
#include "GameFuncCaller.h"
#include "HookManager.h"

class SpawnManager {
public:
    static SpawnManager& GetInstance();
    void Initialize();
private:
    SpawnManager() {}
    PipeManager pipeManager;
    HookManager& hookManager = HookManager::GetInstance();
    GameFuncCaller& gameFuncCaller = GameFuncCaller::GetInstance();
};

#endif
