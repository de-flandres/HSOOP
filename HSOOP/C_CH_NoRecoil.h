#pragma once

#include "C_Cheat.h"

//-------RECOIL VARS----------------------------------------------------------------------------------

const BYTE RECOILON[]							=		{	0xD9,0x1F	};		// fstp dword ptr [edi]
const BYTE RECOILOFF[]							=		{	0x90,				// nop
															0x90				// nop
														};
const DWORD RECOIL_ASSEMBLER					=		0x1E4BA;				// client.dll + 0x1E4BA

class C_CH_NoRecoil : public C_Cheat
{
public:
	C_CH_NoRecoil(int UniqueCheatID);
	~C_CH_NoRecoil();

	void perform();
	void LoadConfiguration();

private:

};