#include <Windows.h>
#include <cstdio>
#include "Main.h"

#define PIPE_NAME "\\\\.\\pipe\\SkyrimPipe"

DWORD WINAPI PipeServerThread(LPVOID lpParam) {
    HANDLE hPipe = CreateNamedPipe(
        PIPE_NAME,
        PIPE_ACCESS_DUPLEX,  // Bidirectional pipe
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  // Message type pipe
        1,  // Max instances
        1024 * 16,  // Output buffer size
        1024 * 16,  // Input buffer size
        0,  // Default timeout
        NULL  // Security attributes
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        return 1;
    }

    // Connect to the client (WPF application)
    if (ConnectNamedPipe(hPipe, NULL) != FALSE) {
        char buffer[1024];
        DWORD bytesRead;

        while (true) {
            // Read data from the pipe
            if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) != FALSE) {
                buffer[bytesRead] = '\0';

                // Extract itemID and spawnAmount from the received message
                int itemID = 0, spawnAmount = 0;
                sscanf_s(buffer, "%d %d", &itemID, &spawnAmount);

                // Call the Testcall function
                SpawnItemToInventory(itemID, spawnAmount);
            }
        }
    }

    CloseHandle(hPipe);
    return 0;
}

