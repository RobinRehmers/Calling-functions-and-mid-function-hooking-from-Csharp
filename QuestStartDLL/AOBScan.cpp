#include "ModuleMgr.h"
#include <Psapi.h>

#define INRANGE(x,a,b)   (x >= a && x <= b)
#define GET_BYTE( x )    (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS( x ) (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))

DWORD_PTR ArrayOfBytesScan(const char* szModule, const char* szSignature)
{

    MODULEINFO modInfo;
    GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
    DWORD_PTR startAddress = (DWORD_PTR)GetModuleHandleA(szModule);
    DWORD_PTR endAddress = (startAddress + (DWORD_PTR)modInfo.SizeOfImage);
    const char* pat = szSignature;
    DWORD_PTR firstMatch = 0;
    for (DWORD_PTR pCur = startAddress; pCur < endAddress; pCur++) {
        if (!*pat) return firstMatch;
        if (*(PBYTE)pat == ('\?') || *(BYTE*)pCur == GET_BYTE(pat)) {
            if (!firstMatch) firstMatch = pCur;
            if (!pat[2]) return firstMatch;
            if (*(PWORD)pat == ('\?\?') || *(PBYTE)pat != ('\?')) pat += 3;
            else pat += 2;
        }
        else {
            pat = szSignature;
            firstMatch = 0;
        }
    }
    return NULL;
}
