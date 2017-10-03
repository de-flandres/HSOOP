#pragma once

#include <Windows.h>
#include "C_Cheat.h"
#include "C_CH_Aimbot.h"

//-------INCAPNORECOIL VARS------------------------------------------------------------------------------

const DWORD INCAPNORECOIL1_ShiftAddress			=		{ 0x5BE22C };
const BYTE INCAPNORECOIL1_ON[]					=		{ 0x00,0x00,0x00,0x00 };
const BYTE INCAPNORECOIL1_OFF[]					=		{ 0xCD,0xCC,0xCC,0x3E };

const DWORD INCAPNORECOIL2_ShiftAddress			=		{ 0x5BE304 };
const BYTE INCAPNORECOIL2_ON[]					=		{ 0x00,0x00,0x00,0x00 };
const BYTE INCAPNORECOIL2_OFF[]					=		{ 0x00,0x00,0x20,0x40 };

const DWORD INCAPNORECOIL3_ShiftAddress			=		{ 0x5BE34C };
const BYTE INCAPNORECOIL3_ON[]					=		{ 0x00,0x00,0x00,0x00 };
const BYTE INCAPNORECOIL3_OFF[]					=		{ 0x00,0x00,0x00,0x40 };

class C_CH_IncapNoRecoil : public C_Cheat
{
public:
	C_CH_IncapNoRecoil(int UniqueCheatID, C_CH_Aimbot*);
	~C_CH_IncapNoRecoil();

	void perform();
	void LoadConfiguration();

private:
	C_CH_Aimbot* Aimbot;

};