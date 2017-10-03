#include "C_CH_GlowHack.h"

C_CH_GlowHack::C_CH_GlowHack(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	Player = new C_MyPlayer();
	for (int i = 0; i < MAX_PLAYERS; i++) EnemyList[i] = new C_Enemy(i);

	LoadConfiguration();
}

C_CH_GlowHack::~C_CH_GlowHack()	// destructor
{
	perform();
	delete Player;
	for (int i = 0; i < MAX_PLAYERS; i++) delete EnemyList[i];
}

void C_CH_GlowHack::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_GLOWHACK_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();

	//perform();
}

void C_CH_GlowHack::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(GLOWHACK_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}

	if (bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		Player->Update();
		if (Player->getTeam(true) == TEAM_SURV)
		{
			WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACK_ShiftAddress), &GLOWHACK_SURV, sizeof(GLOWHACK_SURV), NULL);
		}
		else if (Player->getTeam(false) == TEAM_SPEC)
		{
			WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACK_ShiftAddress), &GLOWHACK_INFECT, sizeof(GLOWHACK_INFECT), NULL);
		}
		else if (Player->getTeam(false) == TEAM_INFECT)
		{
			WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACK_ShiftAddress), &GLOWHACK_OFF, sizeof(GLOWHACK_OFF), NULL);
		}
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACKDISTANCE_ShiftAddress), &GLOWHACKDISTANCE_ON, sizeof(GLOWHACKDISTANCE_ON), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACK_ShiftAddress), &GLOWHACK_OFF, sizeof(GLOWHACK_OFF), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + GLOWHACKDISTANCE_ShiftAddress), &GLOWHACKDISTANCE_OFF, sizeof(GLOWHACKDISTANCE_OFF), NULL);
	}
}