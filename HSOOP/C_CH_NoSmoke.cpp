#include "C_CH_NoSmoke.h"
#include "CFG_MAIN.h"

C_CH_NoSmoke::C_CH_NoSmoke(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	LoadConfiguration();

	thread(perform);
}
C_CH_NoSmoke::~C_CH_NoSmoke()
{
	perform();
}

void C_CH_NoSmoke::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_NOSMOKE_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();

	//perform();
}

void C_CH_NoSmoke::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);
	
	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(NOSMOKE_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}

	if (bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOSMOKE_ShiftAddress), &NOSMOKE_ON, sizeof(NOSMOKE_ON), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordClient + NOSMOKE_ShiftAddress), &NOSMOKE_OFF, sizeof(NOSMOKE_OFF), NULL);
	}
}