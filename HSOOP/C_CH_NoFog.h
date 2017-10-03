#pragma once

#include <Windows.h>
#include "C_Cheat.h"

//-------NOFOG VARS-------------------------------------------------------------------------------------

const DWORD NOFOG1_ShiftAddress						=		{ 0x597268 };
const BYTE NOFOG1_ON[]								=		{ 0x2,0x0,0x0,0x0 };
const BYTE NOFOG1_OFF[]								=		{ 0x0,0x0,0x0,0x0 };

const DWORD NOFOG2_ShiftAddress						=		{ 0x597388 };
const BYTE NOFOG2_ON[]								=		{ 0x0,0x0,0x0,0x0 };
const BYTE NOFOG2_OFF[]								=		{ 0x1,0x0,0x0,0x0 };

class C_CH_NoFog : public C_Cheat
{
public:
	C_CH_NoFog(int UniqueCheatID);
	~C_CH_NoFog();

	void perform();
	void LoadConfiguration();

};