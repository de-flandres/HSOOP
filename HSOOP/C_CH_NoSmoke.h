#pragma once

#include <Windows.h>
#include <string>
#include "C_Cheat.h"

using namespace std;

//-------NOSMOKE VARS-----------------------------------------------------------------------------------

const DWORD NOSMOKE_ShiftAddress					=		{ 0x58FED0 };
const BYTE NOSMOKE_ON[]								=		{ 0x00,0x00,0x00,0x00 };
const BYTE NOSMOKE_OFF[]							=		{ 0x01,0x00,0x00,0x00 };

class C_CH_NoSmoke : public C_Cheat
{
public:
	C_CH_NoSmoke(int UniqueCheatID);
	~C_CH_NoSmoke();

	void perform();
	void LoadConfiguration();

};