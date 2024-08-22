#include <Windows.h>

bool Hook(void* toHook, void* hk_func, int len) {
	if (len < 13) {                                           
		return false;                                         
	}

	DWORD curProtection;
	VirtualProtect(toHook, len, PAGE_EXECUTE_READWRITE, &curProtection);

	//filling with nops our future jmp
	//push rax
	//mov rax,hook_func
	//jmp rax
	//i will pop rax at the beginnijng of the hook otherwise the stack is messed up
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