#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>

extern DWORD64 questCallAddress;
DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature);

#endif