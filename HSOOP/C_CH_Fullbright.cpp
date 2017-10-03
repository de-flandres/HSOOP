#include "C_CH_Fullbright.h"
#include "CFG_MAIN.h"

C_CH_Fullbright::C_CH_Fullbright(int UniqueCheatID) : C_Cheat(UniqueCheatID)
{
	LoadConfiguration();
}
C_CH_Fullbright::~C_CH_Fullbright()
{
	perform();
}

void C_CH_Fullbright::LoadConfiguration()
{
	Process->ConfigLoader->Open(ios::in);
	bCheat_Status = Process->ConfigLoader->Load(CONFIG_FILE[eLOADER_FULLBRIGHT_ENABLED].strParam) == 0 ? false : true;
	Process->ConfigLoader->Close();

	//perform();
}

void C_CH_Fullbright::perform()
{
	if (!bAccessed && GetCurrentThreadId() != C_HackProcess::MAIN_THREAD_ID) return;//ExitThread(0);

	if (clock() - Process->OnePressTIMER > PRESS_TIMER)
	{
		if (Process->IsGameAvail())
		{
			if (GetAsyncKeyState(FULLBRIGHT_BUTTON))
			{
				changeStatusOfCurrentCheat();
				Process->UpdateInfoPanel(true, true, clock());
			}
		}
	}

	if (bCheat_Status && Process->IsCheatEnabled() && bAccessed)
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordMaterialSys + FULLBRIGHT_ShiftAddress), &FULLBRIGHT_ON, sizeof(FULLBRIGHT_ON), NULL);
	}
	else
	{
		WriteProcessMemory(Process->GetHandle(), (PBYTE*)(Process->dwordMaterialSys + FULLBRIGHT_ShiftAddress), &FULLBRIGHT_OFF, sizeof(FULLBRIGHT_OFF), NULL);
	}
}