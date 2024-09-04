#include "HookManager.h"
#include "MemoryReader.h"

DWORD64 HookManager::localplayer = 0;
DWORD64 HookManager::jmpBack = 0;

HookManager& HookManager::GetInstance() {
    static HookManager instance;
    return instance;
}

bool HookManager::Hook(void* toHook, void* hk_func, int len) {
    if (len < 13) {
        return false;
    }

    DWORD curProtection;
    VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

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

void HookManager::Initialize() {
    HookManager& instance = HookManager::GetInstance();
    instance.localplayerAddr = MemoryReader::GetInstance().ArrayOfBytesScan("SkyrimSE.exe", "0F 85 FF 01 00 00 F3 0F 10 4B 5C F3 0F 5C 4F 5C F3 0F 10 43 58 F3 0F 5C 47 58 F3 0F 10 73 54 F3 0F 5C 77 54 F3 0F 59 F6");
    instance.localplayerAddr += 6;
    instance.jmpBack = localplayerAddr + 15;
    instance.Hook((void*)localplayerAddr, localplayerHook, 15);
}

__declspec(naked) void localplayerHook() {	
    __asm {
        pop rax

        movss xmm1, [rbx + 0x5C]
        subss xmm1, [rdi + 0x5C]
        movss xmm0, [rbx + 0x58]

        mov HookManager::localplayer, rdi
    }

    __asm {
        mov rax, HookManager::jmpBack
        jmp rax
    }
}

