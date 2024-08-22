#ifndef CALLING
#define CALLING_H

void QuestCall(DWORD64 addressToCall)
{
	/*typedef void(__fastcall* InternalIDfunc)(__int64 a);
	//	InternalIDfunc GetInteralID = (InternalIDfunc)InternalIDspawncalladdy;
	//	GetInteralID(0x4E50D);

	//	__asm
	//	mov[questptr], rax

	//	firstspawncall = true;*/

	typedef void(__fastcall* _pFunc)(__int64 a, __int64 b);
	_pFunc tarnung = (_pFunc)addressToCall;
	//DWORD64 test = (DWORD64)&questptr->questhashptr->questhash;
	tarnung(0x246CFCB2430, 0x2F96);
}

#endif