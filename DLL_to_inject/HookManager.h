#ifndef HOOKMANAGER_H
#define HOOKMANAGER_H

#include <Windows.h>

class HookManager {
public:
    static HookManager& GetInstance();

    bool Hook(void* toHook, void* hk_func, int len);
    void Initialize();

    static DWORD64 jmpBack;
    static DWORD64 localplayer;
    DWORD64 localplayerAddr;

private:
    HookManager() : localplayerAddr(0) {}
    HookManager(const HookManager&) = delete;
    HookManager& operator=(const HookManager&) = delete;
};

extern "C" __declspec(naked) void localplayerHook();

#endif
