#include <Windows.h>
#include <cstdio>
#include "Main.h"
#include "Globals.h"

#define PIPE_NAME "\\\\.\\pipe\\SkyrimPipe"

DWORD WINAPI PipeServer(LPVOID lpParam) {
    HANDLE hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        0,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if (ConnectNamedPipe(hPipe, NULL) != FALSE) {
        char buffer[1024];
        DWORD bytesRead;

        while (true) {
            if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) != FALSE) {
                buffer[bytesRead] = '\0';

                int itemID = 0, spawnAmount = 0;
                sscanf_s(buffer, "%d %d", &itemID, &spawnAmount);

                SpawnItemToInventory(itemID, spawnAmount);
            }
        }
    }

    CloseHandle(hPipe);
    return 0;
}
