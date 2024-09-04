#ifndef MEMORYREADER_H
#define MEMORYREADER_H

#include <Windows.h>
#include <Psapi.h>

class MemoryReader {
public:
    static MemoryReader& GetInstance();
    MODULEINFO GetModuleInfo(const char* szModule);
    DWORD64 ArrayOfBytesScan(const char* szModule, const char* szSignature);
private:
    MemoryReader() {}
};

#endif
