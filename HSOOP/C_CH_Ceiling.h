#pragma once

#include "C_MyPlayer.h"
#include "C_Cheat_KeyUsing.h"

//-------SEILING VARS----------------------------------------------------------------------------------

const BYTE MOUSEON[]							=		{	0xD9,0x80,0xA4,0x4A,0x00,0x00,		// fld dword ptr[eax+00004AA4]
															0x8B,0x4C,0x24,0x08,				// mov ecx,[esp+08]
															0x05,0xA4,0x4A,0x00,0x00,			// add eax,00004AA4
															0xD9,0x19							// fstp dword ptr [exc]
														};
const BYTE MOUSEOFF[]							=		{	0x8B,0x4C,0x24,0x08,				// mov ecx,[esp+08]
															0x05,0xA4,0x4A,0x00,0x00,			// add eax,00004AA4
															0xD9,0xEB,							// fldpi
															0xD8,0xC0,							// fadd st(0),st(0)
															0xD8,0xC0,							// fadd st(0),st(0)
															0xD9,0x19,							// fstp dword ptr[ecx]
														};
const DWORD MOUSE_ASSEMBLER						=		0xAE4D0 + 0x250D7;						// engine.F + 0x250D7

class C_CH_Ceiling : public C_Cheat_KeyUsing
{
public:
	C_CH_Ceiling(int UniqueCheatID);
	~C_CH_Ceiling();

	void perform();
	void LoadConfiguration();

private:
	C_MyPlayer* Player;

	bool IsCeilingNow;
	int OneClickTIMER;
	int ClickPauseInMS;
};