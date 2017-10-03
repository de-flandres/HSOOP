#include "C_CH_NoFog.h"
#include "CFG_MAIN.h"

C_CH_NoFog::C_CH_NoFog(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	LoadConfiguration();
}
C_CH_NoFog::~C_CH_NoFog()
{
	perform();
}

void C_CH_NoFog::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_NOFOG_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();

	//perform();
}

void C_CH_NoFog::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(NOFOG_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}


	if (bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOFOG1_ShiftAddress), &NOFOG1_ON, sizeof(NOFOG1_ON), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOFOG2_ShiftAddress), &NOFOG2_ON, sizeof(NOFOG2_ON), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOFOG1_ShiftAddress), &NOFOG1_OFF, sizeof(NOFOG1_OFF), NULL);
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOFOG2_ShiftAddress), &NOFOG2_OFF, sizeof(NOFOG2_OFF), NULL);
	}
}