#ifndef HOOKS_H
#define HOOKS_H

#include <Windows.h>

void localplayerHook();

bool Hook(void* toHook, void* hk_func, int len);

#endif
