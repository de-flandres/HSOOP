#pragma once

#include "C_MyPlayer.h"
#include "C_Enemy.h"
#include "C_Cheat.h"

//-------GLOWHACK VARS----------------------------------------------------------------------------------

/*

client.dll+46ABE - CC                    - int 3
client.dll+46ABF - CC                    - int 3
client.dll+46AC0 - 8B 81 BC000000        - mov eax,[ecx+000000BC]
client.dll+46AC6 - 50                    - push eax
client.dll+46AC7 - E8 A41E0500           - call client.dll+98970
client.dll+46ACC - 83 C4 04              - add esp,04 { 4 }
client.dll+46ACF - C3                    - ret
client.dll+46AD0 - 8B 81 BC000000        - mov eax,[ecx+000000BC]	<< HERE
client.dll+46AD6 - C3                    - ret
client.dll+46AD7 - CC                    - int 3
client.dll+46AD8 - CC                    - int 3


client.dll+200EF6 - D8D1                  - fcom st(0),st(1)
client.dll+200EF8 - DFE0                  - fnstsw ax
client.dll+200EFA - F6 C4 05              - test ah,05 { 5 }
client.dll+200EFD - 7A 04                 - jp client.dll+200F03
client.dll+200EFF - DDD9                  - fstp st(1)
client.dll+200F01 - EB 02                 - jmp client.dll+200F05
client.dll+200F03 - DDD8                  - fstp st(0)				<< HERE
client.dll+200F05 - D8 55 00              - fcom dword ptr [ebp+00]
client.dll+200F08 - DFE0                  - fnstsw ax
client.dll+200F0A - F6 C4 05              - test ah,05 { 5 }
client.dll+200F0D - 7A 67                 - jp client.dll+200F76

*/

const DWORD GLOWHACK_ShiftAddress						=		{ 0x46AD0 }; // dwordClient // 0x46C00 for nosteam // 0x46AD0 for steam
const BYTE GLOWHACK_SPEC[]								=		{ 0xB8,0x01,0x00,0x00,0x00,0x90 };
const BYTE GLOWHACK_SURV[]								=		{ 0xB8,0x02,0x00,0x00,0x00,0x90 };
const BYTE GLOWHACK_INFECT[]							=		{ 0xB8,0x03,0x00,0x00,0x00,0x90 };
const BYTE GLOWHACK_OFF[]								=		{ 0x8B,0x81,0xBC,0x00,0x00,0x00 };

const DWORD GLOWHACKDISTANCE_ShiftAddress				=		{ 0x200F03 }; // dwordClient // 0x200E73 for nosteam // 0x200F03 for steam
const BYTE GLOWHACKDISTANCE_ON[]						=		{ 0xDD,0xD9 };
const BYTE GLOWHACKDISTANCE_OFF[]						=		{ 0xDD,0xD8 };

class C_CH_GlowHack : public C_Cheat
{
public:
	C_CH_GlowHack(int UniqueCheatID);
	~C_CH_GlowHack();

	void perform();
	void LoadConfiguration();

private:
	C_MyPlayer* Player;
	C_Enemy* EnemyList[MAX_PLAYERS];
};