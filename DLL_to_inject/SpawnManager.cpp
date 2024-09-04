#include "SpawnManager.h"

SpawnManager& SpawnManager::GetInstance() {
    static SpawnManager instance;
    return instance;
}

void SpawnManager::Initialize() {
    pipeManager.StartPipeServer();
    gameFuncCaller.Initialize();
    hookManager.Initialize();
}
