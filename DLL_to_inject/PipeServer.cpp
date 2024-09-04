#include "PipeManager.h"
#include "GameFuncCaller.h"
#include <cstdio>

#define PIPE_NAME "\\\\.\\pipe\\SkyrimPipe"

PipeManager::PipeManager() {
    hPipe = INVALID_HANDLE_VALUE;
}

PipeManager::~PipeManager() {
    if (hPipe != INVALID_HANDLE_VALUE) {
        CloseHandle(hPipe);
    }
}

void PipeManager::StartPipeServer() {
    CreateThread(0, 0, PipeServerThread, this, 0, 0);
}

DWORD WINAPI PipeManager::PipeServerThread(LPVOID lpParam) {
    PipeManager* pipeManager = static_cast<PipeManager*>(lpParam);
    pipeManager->hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        0,
        NULL
    );

    if (pipeManager->hPipe == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if (ConnectNamedPipe(pipeManager->hPipe, NULL) != FALSE) {
        char buffer[1024];
        DWORD bytesRead;

        while (true) {
            if (ReadFile(pipeManager->hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) != FALSE) {
                buffer[bytesRead] = '\0';

                int itemID = 0, spawnAmount = 0;
                sscanf_s(buffer, "%d %d", &itemID, &spawnAmount);

                GameFuncCaller::GetInstance().SpawnItemToInventory(itemID, spawnAmount);
            }
        }
    }

    CloseHandle(pipeManager->hPipe);
    return 0;
}
