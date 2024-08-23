#include <Windows.h>
#include <cstdio>
#include "Main.h"

DWORD WINAPI PipeServer(LPVOID lpParam) {
    HANDLE hPipe = CreateNamedPipe(
        "\\\\.\\pipe\\MyNamedPipe",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        return 1;
    }

    if (ConnectNamedPipe(hPipe, NULL) != FALSE) {
        char buffer[1024];
        DWORD dwRead;
        while (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE) {
            buffer[dwRead] = '\0';
            int itemID = 0;
            int spawnAmount = 0;
            sscanf_s(buffer, "%d %d", &itemID, &spawnAmount);
            SpawnItemToInventory(itemID, spawnAmount);
        }
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 0;
}