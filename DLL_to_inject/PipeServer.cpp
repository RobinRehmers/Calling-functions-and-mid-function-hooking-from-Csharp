#include <Windows.h>
#include <cstdio>
#include "Main.h"

DWORD WINAPI PipeServer(LPVOID lpParam) {
    HANDLE hPipe;
    char buffer[1024];
    DWORD dwRead;

    hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\SpawnPipe"),
        PIPE_ACCESS_DUPLEX, // Ermöglicht sowohl Lesen als auch Schreiben
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        1024 * 16,
        1024 * 16,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        OutputDebugStringA("Failed to create named pipe.");
        return 1;
    }

    if (ConnectNamedPipe(hPipe, NULL) != FALSE) {
        while (true) {
            if (ReadFile(hPipe, buffer, sizeof(buffer) - 1, &dwRead, NULL) != FALSE) {
                buffer[dwRead] = '\0';
                int itemID = 0;
                int spawnAmount = 0;
                if (sscanf_s(buffer, "%d %d", &itemID, &spawnAmount) == 2) {
                    char debugMessage[1024];
                    sprintf_s(debugMessage, "Received itemID: %x, spawnAmount: %d\n", itemID, spawnAmount);
                    OutputDebugStringA(debugMessage);

                    SpawnItemToInventory(itemID, spawnAmount);
                }
                else {
                    OutputDebugStringA("Failed to parse the received data.");
                }
            }
            else {
                OutputDebugStringA("Failed to read from named pipe.");
                break; // Beenden der Schleife bei Lese-Fehler
            }
        }
    }
    else {
        OutputDebugStringA("Failed to connect to named pipe.");
    }

    // Named Pipe trennen und schließen, wenn der Server beendet wird
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);

    return 0;
}

