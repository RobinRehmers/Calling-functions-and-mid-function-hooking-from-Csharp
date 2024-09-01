#include "Hooks.h"
#include "Globals.h"

bool Hook(void* toHook, void* hk_func, int len) {
    if (len < 13) {
        return false;
    }

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

    // Filling with NOPs our future jmp
    unsigned char patch[] = {
        0x50, 0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0xFF, 0xE0
    };
    *(DWORD64*)&patch[3] = (DWORD64)hk_func;
    memcpy((void*)toHook, patch, sizeof(patch));
    DWORD temp;
    VirtualProtect(toHook, len, curProtection, &temp);
    return true;
}

DWORD64 jmpBack;
__declspec(naked) void localplayerHook()
{
    __asm {
        pop rax

        movss xmm1, [rbx + 0x5C]
        subss xmm1, [rdi + 0x5C]
        movss xmm0, [rbx + 0x58]
        //mov getLocalPlayerAddress(), rdi
        jmp[jmpBack]
    }
}
