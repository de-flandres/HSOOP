#pragma once

#include <Windows.h>

#include "C_Cheat_KeyUsing.h"

//-------BUNNYHOP VARS---------------------------------------------------------------------------------

const DWORD dw_IsOnFloor						=		0x590810; // 0x590810, 0x5907C4 /// 1-0(floor,jump)

class C_CH_BunnyHop : public C_Cheat_KeyUsing
{
public:
	C_CH_BunnyHop(int UniqueCheatID);

	void  perform();
	void LoadConfiguration();

private:

	int iIsPlayerOnFloor;
};