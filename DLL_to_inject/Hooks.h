#include <Windows.h>

__declspec(naked) void localplayerHook()
{
	__asm {
		pop rax

		movss xmm1, [rbx + 0x5C]
		subss xmm1, [rdi + 0x5C]
		movss xmm0, [rbx + 0x58]
		mov[localplayer], rdi
	
		jmp[jmpBack_localplayerAddress]
	}
}