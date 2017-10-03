#pragma once

#include <Windows.h>
#include <string>

#include "C_Cheat.h"

const DWORD FULLBRIGHT_ShiftAddress					=		{ 0xEF668 };
const BYTE FULLBRIGHT_ON[]							=		{ 0x1,0x0,0x0,0x0 };
const BYTE FULLBRIGHT_OFF[]							=		{ 0x0,0x0,0x0,0x0 };

class C_CH_Fullbright : public C_Cheat
{
public:
	C_CH_Fullbright(int UniqueCheatID);
	~C_CH_Fullbright();

	void perform();
	void LoadConfiguration();

};