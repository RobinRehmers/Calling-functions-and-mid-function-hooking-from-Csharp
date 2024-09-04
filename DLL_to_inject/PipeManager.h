#ifndef PIPEMANAGER_H
#define PIPEMANAGER_H

#include <Windows.h>

class PipeManager {
public:
    PipeManager();
    ~PipeManager();
    void StartPipeServer();
private:
    static DWORD WINAPI PipeServerThread(LPVOID lpParam);
    HANDLE hPipe;
};

#endif
